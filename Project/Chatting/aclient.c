#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#define TCP_PORT 5200
#define MAX_ID_LEN 20
#define MAX_MSG_LEN 256
#define BUFSIZ 1024

int ssock;
char user_id[MAX_ID_LEN];
char user_pwd[MAX_ID_LEN];
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
    printf("5. 종료\n");
    printf("선택: ");
}

int main(int argc, char **argv)
{
    struct sockaddr_in servaddr;
    pid_t pid; 
    int n;

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("소켓 생성 실패");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    /* 문자열을 네트워크 주소로 변경 */
    inet_pton(AF_INET, argv[1], &(servaddr.sin_addr.s_addr));
    servaddr.sin_port = htons(TCP_PORT);

    if (connect(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("서버 연결 실패");
        return 1;
    }

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
                    printf("엔터를 눌러주세요.\n");
                    getchar();
                    break;
                }
                printf("사용자 ID 입력: ");
                fgets(user_id, MAX_ID_LEN, stdin);
                user_id[strcspn(user_id, "\n")] = 0; // 개행 문자 제거
                sprintf(mesg, "LOGIN:%s", user_id);
                send(ssock, mesg, strlen(mesg), 0);
                printf("사용자 PASSWORD 입력: ");
                fgets(user_pwd, MAX_ID_LEN, stdin);

                // 서버로부터 응답 받기
                memset(mesg, 0, BUFSIZ);
                if (recv(ssock, mesg, BUFSIZ, 0) > 0) {
                    printf("%s\n", mesg);
                }
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
                    printf("메시지 입력 (q로 종료)\n");
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
                getchar();
                break;;
            case 3: // 로그아웃
                if (strlen(user_id) == 0) {
                    printf("로그인 상태가 아닙니다.\n");
                    getchar();
                    break;
                }
                sprintf(mesg, "LOGOUT:%s", user_id);
                send(ssock, mesg, strlen(mesg), 0);
                memset(user_id, 0, MAX_ID_LEN);
                printf("로그아웃되었습니다.\n");

                // 서버로부터 응답 받기
                memset(mesg, 0, BUFSIZ);
                if (recv(ssock, mesg, BUFSIZ, 0) > 0) {
                    printf("%s\n", mesg);
                }
                getchar();
                break;
            case 4: // 종료
                if (strlen(user_id) == 0) {
                    printf("로그인 상태가 아닙니다.\n");
                    getchar();
                    break;
                }
                printf("검색하려는 메시지를 입력해주세요.\n");
                while(1) {
                    char temp[MAX_MSG_LEN];
                    fgets(temp, MAX_MSG_LEN, stdin);
                    temp[strcspn(temp, "\n")] = 0; // 개행 문자 제거
                    if (strcmp(temp, "q") == 0) {
                        getchar();
                        break;
                    }
                    sprintf(mesg, "FIND: %s", temp);
                    send(ssock, mesg, strlen(mesg), 0);

                    memset(mesg, 0, BUFSIZ);
                    if (recv(ssock, mesg, BUFSIZ, 0) > 0) {
                        printf("%s\n", mesg);
                    }
                    getchar();
                }
                break;
            case 5: // 종료
                sprintf(mesg, "quit");
                send(ssock, mesg, strlen(mesg), 0);
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