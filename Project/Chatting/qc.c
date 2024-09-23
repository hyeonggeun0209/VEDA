#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TCP_PORT 5200
#define MAX_USR_LEN 20
#define MAX_MSG_LEN 1024

int ssock;
char user_id[MAX_USR_LEN];
char user_pwd[MAX_USR_LEN];
char mesg[BUFSIZ];

void cleanup() {
    close(ssock);
    exit(0);
}

void handle_signal(int sig) {
    cleanup();
}

void display_menu() {
    printf("\n===== 채팅 클라이언트 =====\n");
    printf("1. 로그인\n");
    printf("2. 채팅하기\n");
    printf("3. 로그아웃\n");
    printf("4. 메시지 검색\n");
    printf("5. 파일 업로드\n");
    printf("6. 파일 다운로드\n");
    printf("7. 종료\n");
    printf("선택: ");
}

// 파일 업로드 함수
void upload_file(int sock, const char* filename) {
    int file_fd = open(filename, O_RDONLY);
    if (file_fd < 0) {
        perror("파일 열기 실패");
        return;
    }

    char buffer[BUFSIZ];
    sprintf(buffer, "UPLOAD:%s", filename);
    send(sock, buffer, strlen(buffer), 0);

    ssize_t bytes_read;
    while ((bytes_read = read(file_fd, buffer, BUFSIZ)) > 0) {
        if (send(sock, buffer, bytes_read, 0) != bytes_read) {
            perror("파일 전송 실패");
            break;
        }
    }

    close(file_fd);
    printf("파일 업로드 완료: %s\n", filename);
}

// 파일 다운로드 함수
void download_file(int sock, const char* filename) {
    char buffer[BUFSIZ];
    int file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0) {
        perror("파일 열기 실패");
        return;
    }

    ssize_t bytes_received;
    while ((bytes_received = recv(sock, buffer, BUFSIZ, 0)) > 0) {
        if (write(file_fd, buffer, bytes_received) != bytes_received) {
            perror("파일 쓰기 실패");
            break;
        }
        if (bytes_received < BUFSIZ) break;
    }

    close(file_fd);
    printf("파일 다운로드 완료: %s\n", filename);
}

int main(int argc, char **argv)
{
    struct sockaddr_in servaddr;
    pid_t pid; 

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("소켓 생성 실패");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(servaddr.sin_addr.s_addr));
    servaddr.sin_port = htons(TCP_PORT);

    if (connect(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("서버 연결 실패");
        return 1;
    }
    
    system("clear");
    printf("서버에 연결되었습니다.\n");
    printf("엔터를 눌러 접속하세요.\n");
    getchar();
    signal(SIGINT, handle_signal);

    while (1) {
        system("clear");
        display_menu();
        int choice;
        scanf("%d", &choice);
        getchar(); // 버퍼 비우기

        switch (choice) {
            case 1: // 로그인
                if(strlen(user_id) != 0) {
                    printf("로그인 상태입니다. ID : %s\n", user_id);
                    printf("엔터를 눌러 계속하세요...\n");
                    getchar();
                    break;
                }
                printf("사용자 ID 입력: ");
                fgets(user_id, MAX_USR_LEN, stdin);
                user_id[strcspn(user_id, "\n")] = 0; // 개행 문자 제거
                sprintf(mesg, "LOGIN:%s", user_id);
                send(ssock, mesg, strlen(mesg), 0);

                printf("사용자 PASSWORD 입력: ");
                fgets(user_pwd, MAX_USR_LEN, stdin);
                user_pwd[strcspn(user_pwd, "\n")] = 0;

                // 서버로부터 응답 받기
                memset(mesg, 0, BUFSIZ);
                if (recv(ssock, mesg, BUFSIZ, 0) > 0) {
                    printf("%s\n", mesg);
                }
                printf("엔터를 눌러 계속하세요...\n");
                getchar();
                break;
            case 2: // 채팅하기
                if (strlen(user_id) == 0) {
                    printf("로그인 상태가 아닙니다.\n");
                    getchar();
                    break;
                }
                pid = fork();
                if (pid < 0) {
                    perror("Error");
                } else if (pid == 0) {
                    // 자식 프로세스: 메시지 전송
                    printf("메시지 입력 (q 로 종료)\n");
                    while(1) {
                        char temp[MAX_MSG_LEN];
                        fgets(temp, MAX_MSG_LEN, stdin);
                        temp[strcspn(temp, "\n")] = 0; // 개행 문자 제거
                        if (strcmp(temp, "q") == 0) {
                            send(ssock, "q", 1, 0);
                            exit(0);
                        }
                        sprintf(mesg, "%s : %s", user_id, temp);
                        send(ssock, mesg, strlen(mesg), 0);
                    }
                } else {
                    // 부모 프로세스: 메시지 수신
                    while(1) {
                        memset(mesg, 0, BUFSIZ);
                        if(recv(ssock, mesg, BUFSIZ, 0) <= 0) {
                            perror("recv()");
                            kill(pid, SIGTERM);
                            break;
                        } else if(strcmp(mesg, "q") == 0) {
                            printf("채팅 종료\n");
                            break;
                        } else {
                            printf("%s\n", mesg);
                            fflush(stdout); 
                        }
                    }
                    waitpid(pid, NULL, 0);
                }
                printf("엔터를 눌러 계속하세요...\n");
                getchar();
                break;
            case 3: // 로그아웃
                if (strlen(user_id) == 0) {
                    printf("로그인 상태가 아닙니다.\n");
                    getchar();
                    break;
                }
                sprintf(mesg, "LOGOUT:%s", user_id);
                send(ssock, mesg, strlen(mesg), 0);
                memset(user_id, 0, MAX_USR_LEN);
                printf("로그아웃되었습니다.\n");

                // 서버로부터 응답 받기
                memset(mesg, 0, BUFSIZ);
                if (recv(ssock, mesg, BUFSIZ, 0) > 0) {
                    printf("%s\n", mesg);
                }
                printf("엔터를 눌러 계속하세요...\n");
                getchar();
                break;
            case 4: // 메시지 검색
                if (strlen(user_id) == 0) {
                    printf("로그인 상태가 아닙니다.\n");
                    getchar();
                    break;
                }
                while(1) {
                    printf("검색할 키워드를 입력하세요 (q 로 종료) : ");
                    char keyword[MAX_MSG_LEN];
                    fgets(keyword, MAX_MSG_LEN, stdin);
                    keyword[strcspn(keyword, "\n")] = 0; // 개행 문자 제거
                    if (strcmp(keyword, "q") == 0) {
                        printf("검색 종료\n");
                        break;
                    }                    
                    sprintf(mesg, "SEARCH:%s", keyword);
                    send(ssock, mesg, strlen(mesg), 0);

                    memset(mesg, 0, BUFSIZ);
                    if (recv(ssock, mesg, BUFSIZ, 0) > 0) {
                        printf("검색 결과:\n%s\n", mesg);
                    }
                    continue;
                    // printf("엔터를 눌러 계속하세요...\n");
                    // getchar();
                }
                getchar();
                break;
            case 5: // 파일 업로드
                if (strlen(user_id) == 0) {
                    printf("로그인 상태가 아닙니다.\n");
                    getchar();
                    break;
                }
                printf("업로드할 파일 경로를 입력하세요: ");
                char filepath[256];
                fgets(filepath, sizeof(filepath), stdin);
                filepath[strcspn(filepath, "\n")] = 0; // 개행 문자 제거
                upload_file(ssock, filepath);
                printf("엔터를 눌러 계속하세요...\n");
                getchar();
                break;
            case 6: // 파일 다운로드
                if (strlen(user_id) == 0) {
                    printf("로그인 상태가 아닙니다.\n");
                    getchar();
                    break;
                }
                send(ssock, "GET_FILE_LIST", 13, 0);
                memset(mesg, 0, BUFSIZ);
                int bytes_received = 0;
                char file_list[BUFSIZ * 10] = {0};  // 더 큰 버퍼 사용
                char *file_list_ptr = file_list;
                int total_received = 0;

                // 파일 목록 전체를 수신할 때까지 반복
                while ((bytes_received = recv(ssock, mesg, BUFSIZ, 0)) > 0) {
                    if(strcmp(mesg, "업로드된 파일이 없습니다.\n\n") == 0 ) {
                        printf("다운로드 가능한 파일이 없습니다.\n");
                        break;
                    }
                    if(strncmp(mesg, "L",1) == 0) continue;
                    memcpy(file_list_ptr, mesg, bytes_received);
                    file_list_ptr += bytes_received;
                    total_received += bytes_received;
                    if (total_received >= BUFSIZ * 10 || strstr(file_list, "\n\n") != NULL) {
                        break;  // 충분히 받았거나 목록의 끝을 발견하면 중단
                    }
                    memset(mesg, 0, BUFSIZ);
                }

                if (total_received > 0) {
                    file_list[total_received] = '\0';  // 문자열 끝을 명시적으로 지정
                    printf("업로드된 파일 목록:\n%s\n", file_list);
                    if (strstr(file_list, "업로드된 파일이 없습니다.") != NULL) {
                        printf("다운로드 가능한 파일이 없습니다. 메뉴로 돌아갑니다.\n");
                        printf("엔터를 눌러 계속하세요...\n");
                        getchar();
                        break;
                    }
                    printf("다운로드할 파일 번호를 선택하세요 (0을 입력하면 메뉴로 돌아갑니다): ");
                    int file_index;
                    scanf("%d", &file_index);
                    getchar(); // 버퍼 비우기
                    if (file_index == 0) {
                        printf("메뉴로 돌아갑니다.\n");
                        break;
                    }
                    sprintf(mesg, "DOWNLOAD:%d", file_index);
                    send(ssock, mesg, strlen(mesg), 0);
                    printf("다운로드할 파일명을 입력하세요: ");
                    char download_filename[256];
                    fgets(download_filename, sizeof(download_filename), stdin);
                    download_filename[strcspn(download_filename, "\n")] = 0; // 개행 문자 제거
                    download_file(ssock, download_filename);
                } else {
                    printf("파일 목록을 받아오는데 실패했습니다.\n");
                }
                printf("엔터를 눌러 계속하세요...\n");
                getchar();
                break;
            case 7: // 종료
                sprintf(mesg, "quit");
                send(ssock, mesg, strlen(mesg), 0);
                printf("프로그램 종료\n");
                cleanup();
                break;
            default:
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
                getchar();
                break;
        }
    }

    return 0;
}
                