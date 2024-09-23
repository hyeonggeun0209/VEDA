#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define TCP_PORT 5200
#define MAX_CLIENTS 5
#define BUFSIZ 1024

typedef struct client_sock {
    char ip[BUFSIZ];
    int s_id;
    int csfd;
    char user_id[20];
} c_sock;

static int g_noc = 0;
int pipefd[2];
c_sock* cs[MAX_CLIENTS];

void sigchld_handler(int signo) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < g_noc; i++) {
            if (cs[i]->s_id == pid) {
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

void broadcast_message(char *message, int sender_pid) {
    for (int i = 0; i < g_noc; i++) {
        if (cs[i]->s_id != sender_pid) {
            write(cs[i]->csfd, message, strlen(message));
        }
    }
}

void sigusr1_handler(int signo) {
    char broadcast_msg[BUFSIZ];
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

        if (strncmp(mesg, "LOGIN:", 6) == 0) {
            strncpy(cs[client_index]->user_id, mesg + 6, 20);
            printf("Client %s logged in as %s\n", cs[client_index]->ip, cs[client_index]->user_id);
            sprintf(mesg, "로그인 성공: %s", cs[client_index]->user_id);
        } else if (strncmp(mesg, "LOGOUT:", 7) == 0) {
            printf("Client %s logged out\n", cs[client_index]->ip);
            memset(cs[client_index]->user_id, 0, 20);
            sprintf(mesg, "로그아웃 성공");
        } else if (strncmp(mesg, "MSG:", 4) == 0) {
            char *user_id = strtok(mesg + 4, ":");
            char *msg = strtok(NULL, "");
            printf("(%s) %s: %s\n", cs[client_index]->ip, user_id, msg);
            sprintf(mesg, "%s: %s", user_id, msg);
            write(pipefd[1], &pid, sizeof(int));
            write(pipefd[1], mesg, strlen(mesg) + 1);
            kill(getppid(), SIGUSR1);
        } else {
            printf("Unknown command from %s: %s\n", cs[client_index]->ip, mesg);
            sprintf(mesg, "알 수 없는 명령어");
        }

        write(cs[client_index]->csfd, mesg, strlen(mesg));
    }

    close(cs[client_index]->csfd);
    exit(0);
}

int main(int argc, char **argv) {
    int ssock, csock;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clen;
    pid_t pid;

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

    printf("채팅 서버가 시작되었습니다.\n");

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

        printf("클라이언트가 연결되었습니다: %s\n", cs[g_noc]->ip);

        if ((pid = fork()) < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            close(ssock);
            cs[g_noc]->s_id = getpid();
            handle_client(g_noc);
        } else {
            cs[g_noc]->s_id = pid;
            g_noc++;
        }
    }

    close(ssock);
    return 0;
}