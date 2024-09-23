#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TCP_PORT 5200
#define MAX_CLIENTS 1024
#define MAX_MESSAGES 1024

typedef struct client_sock {
    char ip[BUFSIZ];
    char name[BUFSIZ];
    int id;
    int csfd;
} c_sock;

static int g_noc = 0;
int pipefd[2];
c_sock* cs[MAX_CLIENTS];
char messages[MAX_MESSAGES][BUFSIZ];
int message_count = 0;

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

void broadcast_message(char *message, int sender_pid) {
    if(strncmp(message, "LOGIN:", 6) != 0 && strncmp(message, "LOGOUT:", 7) != 0 && 
       strcmp(message, "q") != 0 && strncmp(message, "SEARCH:", 7) != 0) {
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
        } else {
            if (cs[i]->id != sender_pid) {
                write(cs[i]->csfd, message, strlen(message));
            }
        }
    }
}

void sigusr1_handler(int signo) {
    char broadcast_msg[BUFSIZ + 50];
    int sender_pid;
    
    read(pipefd[0], &sender_pid, sizeof(int));
    read(pipefd[0], broadcast_msg, sizeof(broadcast_msg));
    
    broadcast_message(broadcast_msg, sender_pid);
}

void handle_client(int client_index) {
    char mesg[BUFSIZ];
    int n;
    pid_t pid = getpid();

    while (1) {
        memset(mesg, 0, BUFSIZ);
        if ((n = read(cs[client_index]->csfd, mesg, BUFSIZ)) <= 0) {
            break;
        }

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

void init_daemon() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);
    chdir("/");

    for (int x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
        close(x);
    }

    openlog("chat_server", LOG_PID, LOG_DAEMON);
}

int main(int argc, char **argv) {
    int ssock, csock;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clen;
    pid_t pid;

    init_daemon();

    syslog(LOG_NOTICE, "채팅 서버 데몬이 시작되었습니다.");

    if (pipe(pipefd) < 0) {
        syslog(LOG_ERR, "파이프 생성 실패: %m");
        exit(1);
    }

    signal(SIGCHLD, sigchld_handler);
    signal(SIGUSR1, sigusr1_handler);

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        syslog(LOG_ERR, "소켓 생성 실패: %m");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(TCP_PORT);

    if (bind(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        syslog(LOG_ERR, "바인드 실패: %m");
        exit(1);
    }

    if (listen(ssock, 8) < 0) {
        syslog(LOG_ERR, "리슨 실패: %m");
        exit(1);
    }

    while (1) {
        clen = sizeof(cliaddr);
        if ((csock = accept(ssock, (struct sockaddr *)&cliaddr, &clen)) < 0) {
            syslog(LOG_ERR, "클라이언트 연결 수락 실패: %m");
            continue;
        }

        if (g_noc >= MAX_CLIENTS) {
            syslog(LOG_WARNING, "최대 클라이언트 수에 도달했습니다. 연결을 거부합니다.");
            close(csock);
            continue;
        }

        cs[g_noc] = (c_sock*)malloc(sizeof(c_sock));
        inet_ntop(AF_INET, &cliaddr.sin_addr, cs[g_noc]->ip, BUFSIZ);
        cs[g_noc]->csfd = csock;

        if ((pid = fork()) < 0) {
            syslog(LOG_ERR, "fork 실패: %m");
            exit(1);
        } else if (pid == 0) {
            close(ssock);
            cs[g_noc]->id = getpid();
            handle_client(g_noc);
        } else {
            cs[g_noc]->id = pid;
            g_noc++;
            syslog(LOG_NOTICE, "새 클라이언트 연결: %s", cs[g_noc-1]->ip);
        }
    }

    close(ssock);
    closelog();
    return 0;
}