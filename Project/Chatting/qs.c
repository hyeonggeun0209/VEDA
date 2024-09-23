#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TCP_PORT 5200
#define MAX_CLIENTS 1024
#define MAX_MESSAGES 1024
#define MAX_FILES 100

// 클라이언트 소켓 정보를 저장하는 구조체
typedef struct client_sock {
    char ip[BUFSIZ];
    char name[BUFSIZ];
    int id;
    int csfd;
} c_sock;

typedef struct file_info {
    char filename[256];
    char uploader[BUFSIZ];
} FileInfo;

// 전역 변수 선언
static int g_noc = 0;   // 현재 연결된 클라이언트 수
int pipefd[2];  // 프로세스 간 통신을 위한 파이프
c_sock* cs[MAX_CLIENTS];    // 클라이언트 소켓 정보 배열
char messages[MAX_MESSAGES][BUFSIZ];
int message_count = 0;
FileInfo uploaded_files[MAX_FILES];
int file_count = 0;

// 자식 프로세스 종료 처리 함수
void sigchld_handler(int signo) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < g_noc; i++) {
            if (cs[i]->id == pid) {
                close(cs[i]->csfd);
                free(cs[i]);
                for (int j = i; j < g_noc - 1; j++) {
                    cs[j] = cs[j+1];
                }
                g_noc--;
                break;
            }
        }
    }
}

// 파일 목록에 파일 추가
void add_file(const char* filename, const char* uploader) {
    if (file_count < MAX_FILES) {
        strncpy(uploaded_files[file_count].filename, filename, 255);
        strncpy(uploaded_files[file_count].uploader, uploader, BUFSIZ-1);
        file_count++;
    }
}

// 파일 목록 문자열 생성
char* get_file_list() {
    static char file_list[BUFSIZ * MAX_FILES];
    memset(file_list, 0, sizeof(file_list));
    char* ptr = file_list;

    if (file_count == 0) {
        strcpy(file_list, "업로드된 파일이 없습니다.\n\n");
    } else {
        for (int i = 0; i < file_count; i++) {
            int len = snprintf(ptr, BUFSIZ, "%d. %s (업로더: %s)\n", 
                               i+1, 
                               uploaded_files[i].filename, 
                               uploaded_files[i].uploader);
            ptr += len;
        }
        strcat(file_list, "\n");  // 목록의 끝을 나타내는 추가 개행
    }

    return file_list;
}

// 파일 수신 함수 수정
void receive_file(int client_socket, const char* filename, const char* uploader) {
    char buffer[BUFSIZ];
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    int file_fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0) {
        perror("파일 열기 실패");
        return;
    }

    ssize_t bytes_received;
    while ((bytes_received = recv(client_socket, buffer, BUFSIZ, 0)) > 0) {
        if (write(file_fd, buffer, bytes_received) != bytes_received) {
            perror("파일 쓰기 실패");
            break;
        }
        if (bytes_received < BUFSIZ) break;
    }

    close(file_fd);
    printf("파일 수신 완료: %s (업로더: %s)\n", filename, uploader);

    if (file_count < MAX_FILES) {
        strncpy(uploaded_files[file_count].filename, filename, 255);
        strncpy(uploaded_files[file_count].uploader, uploader, BUFSIZ-1);
        file_count++;
    }
    // add_file(filename, uploader);
}

// 메시지 검색 함수
char* search_messages(char *keyword) {
    static char result[BUFSIZ];
    memset(result, 0, BUFSIZ);
    char *ptr = result;
    int found = 0;

    for (int i = 0; i < message_count; i++) {
        if (strstr(messages[i], keyword) != NULL) {
            int len = strlen(messages[i]);
            strncpy(ptr, messages[i], len);
            ptr += len;
            *ptr++ = '\n';
            found = 1;
        }
    }

    if (!found) {
        strcpy(result, "검색 결과가 없습니다.\n");
    }

    return result;
}

// 모든 클라이언트에게 메시지 브로드캐스트 함수
void broadcast_message(char *message, int sender_pid) {
    if(strncmp(message, "LOGIN:", 6) != 0 && strncmp(message, "LOGOUT:", 7) != 0 && 
       strcmp(message, "q") != 0 && strncmp(message, "SEARCH:", 7) != 0 && 
       strncmp(message, "GET_FILE_LIST", 13) != 0 && strncmp(message, "DOWNLOAD:", 9) != 0 &&
       strncmp(message, "UPLOAD:", 7) == 0) {
        // 일반 메시지만 저장
        if (message_count < MAX_MESSAGES) {
            strncpy(messages[message_count], message, BUFSIZ);
            message_count++;
        }
    }

    for (int i = 0; i < g_noc; i++) {
        if(strncmp(message, "LOGIN:", 6) == 0 || strncmp(message, "LOGOUT:", 7) == 0 || strcmp(message, "q") == 0) {
            if (cs[i]->id == sender_pid) {
                write(cs[i]->csfd, message, strlen(message));
                break;
            }
        } else if(strncmp(message, "SEARCH:", 7) == 0) {
            if (cs[i]->id == sender_pid) {
                char *result = search_messages(message + 7);
                write(cs[i]->csfd, result, strlen(result));
                break;
            }
        } else if (strncmp(message, "UPLOAD:", 7) == 0) {
            char tmp[BUFSIZ + 50];
            char *ptr1;
            snprintf(tmp, sizeof(tmp), "%s", message);
            ptr1 = strtok(tmp, ":");
            ptr1 = strtok(NULL, " ");
            receive_file(cs[i]->csfd, ptr1, cs[i]->name);
        } else {
            if (cs[i]->id != sender_pid) {
                write(cs[i]->csfd, message, strlen(message));
            }
        }
    }
}

// SIGUSR1 시그널 핸들러 (브로드캐스트 메시지 처리)
void sigusr1_handler(int signo) {
    char broadcast_msg[BUFSIZ + 50];
    int sender_pid;
    
    read(pipefd[0], &sender_pid, sizeof(int));
    read(pipefd[0], broadcast_msg, sizeof(broadcast_msg));
    
    broadcast_message(broadcast_msg, sender_pid);
}

// 클라이언트 처리 함수
void handle_client(int client_index) {
    char mesg[BUFSIZ];
    int n;
    pid_t pid = getpid();

    while (1) {
        memset(mesg, 0, BUFSIZ);
        if ((n = read(cs[client_index]->csfd, mesg, BUFSIZ)) <= 0) {
            break;
        }
        printf("%s\n", mesg);
        char broadcast_msg[BUFSIZ + 50];

        if(strncmp(mesg, "LOGIN:", 6) == 0) {
            char tmp[BUFSIZ + 50];
            char *ptr1;
            snprintf(tmp, sizeof(tmp), "%s", mesg);
            ptr1 = strtok(tmp, ":");
            ptr1 = strtok(NULL, " ");
            strcpy(cs[client_index]->name, ptr1);
            snprintf(broadcast_msg, sizeof(broadcast_msg), "%s", mesg);
        } else if (strcmp(mesg, "quit") == 0) {
            break;
        } else if (strncmp(mesg, "UPLOAD:", 7) == 0) {
            char filename[256];
            sscanf(mesg, "UPLOAD:%s", filename);
            snprintf(broadcast_msg, sizeof(broadcast_msg), "%s", mesg);
            // receive_file(cs[client_index]->csfd, filename, cs[client_index]->name);
        } else if (strcmp(mesg, "GET_FILE_LIST") == 0) {
            char* file_list = get_file_list();
            printf("Sending file list: %s\n", file_list);  // 디버깅을 위한 로그 추가
            write(cs[client_index]->csfd, file_list, strlen(file_list));
        } else if (strncmp(mesg, "DOWNLOAD:", 9) == 0) {
            int file_index;
            sscanf(mesg, "DOWNLOAD:%d", &file_index);
            if (file_index > 0 && file_index <= file_count) {
                char filepath[512];
                snprintf(filepath, sizeof(filepath), "uploads/%s", uploaded_files[file_index-1].filename);
                int file_fd = open(filepath, O_RDONLY);
                if (file_fd < 0) {
                    write(cs[client_index]->csfd, "FILE_NOT_FOUND", 14);
                } else {
                    char buffer[BUFSIZ];
                    ssize_t bytes_read;
                    while ((bytes_read = read(file_fd, buffer, BUFSIZ)) > 0) {
                        write(cs[client_index]->csfd, buffer, bytes_read);
                    }
                    close(file_fd);
                }
            } else {
                write(cs[client_index]->csfd, "INVALID_FILE_INDEX", 18);
            }
        } else {
            snprintf(broadcast_msg, sizeof(broadcast_msg), "%s", mesg);
        }
        
        write(pipefd[1], &pid, sizeof(int));
        write(pipefd[1], broadcast_msg, strlen(broadcast_msg) + 1);
        kill(getppid(), SIGUSR1);
    }

    close(cs[client_index]->csfd);
    exit(0);
}

int main(int argc, char **argv) {
    int ssock, csock;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clen;
    pid_t pid;

    mkdir("uploads", 0777);

    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(1);
    }

    signal(SIGCHLD, sigchld_handler);
    signal(SIGUSR1, sigusr1_handler);

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(TCP_PORT);

    if (bind(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(ssock, 8) < 0) {
        perror("listen");
        exit(1);
    }

    while (1) {
        clen = sizeof(cliaddr);
        if ((csock = accept(ssock, (struct sockaddr *)&cliaddr, &clen)) < 0) {
            perror("accept");
            continue;
        }

        if (g_noc >= MAX_CLIENTS) {
            printf("최대 클라이언트 수에 도달했습니다. 연결을 거부합니다.\n");
            close(csock);
            continue;
        }

        cs[g_noc] = (c_sock*)malloc(sizeof(c_sock));
        inet_ntop(AF_INET, &cliaddr.sin_addr, cs[g_noc]->ip, BUFSIZ);
        cs[g_noc]->csfd = csock;

        printf("Client is connected: %s\n", cs[g_noc]->ip);

        if ((pid = fork()) < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            close(ssock);
            cs[g_noc]->id = getpid();
            handle_client(g_noc);
        } else {
            cs[g_noc]->id = pid;
            g_noc++;
        }
    }

    close(ssock);
    return 0;
}