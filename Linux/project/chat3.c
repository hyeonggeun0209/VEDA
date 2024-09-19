#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TCP_PORT 5200 				/* 서버의 포트 번호 */

typedef struct client_sock {
  char ip[BUFSIZ];
  int s_id;
  int csfd;
} c_sock;

static int g_noc = 0;
int p[2], f[2];
char mesg[BUFSIZ];
c_sock* cs[5];

void sigfunc(int no) 
{
    printf("Signal : %d\n", no);
    if(--g_noc == 0) exit(0);
}

void sigusr1(int no) 
{
    int num;
    read(f[0], &num, sizeof(int));
    g_noc = num;
    // char buf[BUFSIZ];
    // int fd = 0;
    // memset(buf, 0, BUFSIZ);
    
    // // 파이프에서 메시지 읽기
    // if (read(p[0], buf, BUFSIZ) > 0) {
    //   printf("num : %d\n", g_noc);

    //     // 모든 클라이언트에게 전송
    //     for (int i = 0; i < g_noc; i++) {
    //         if (write(cs[i]->csfd, buf, strlen(buf)) <= 0)
    //             perror("write() to client");
    //     }
    // }
}

void broadcast_message(const char *message, int sender_fd) {
    for (int i = 0; i < g_noc; i++) {
        if (cs[i]->csfd != sender_fd) {  // 보낸 클라이언트에게는 다시 보내지 않음
            if (write(cs[i]->csfd, message, strlen(message)) <= 0) {
                perror("write()");
            }
        }
    }
}

int main(int argc, char **argv)
{
    pipe(p);
    pipe(f);
    int ssock, portno, n;                   /* 소켓 디스크립트 정의 */
    struct sockaddr_in servaddr, cliaddr; 	/* 주소 구조체 정의 */
    socklen_t clen;
    pid_t pid;                              /* fork( ) 함수를 위한 PID */

    portno = (argc == 2)?atoi(argv[1]):TCP_PORT;

    signal(SIGCHLD, sigfunc);
    signal(SIGUSR1, sigusr1);

    /* 서버 소켓 생성 */
    if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return -1;
    }

    /* 주소 구조체에 주소 지정 */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(portno); 	/* 사용할 포트 지정 */

    /* bind 함수를 사용하여 서버 소켓의 주소 설정 */
    if(bind(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind()");
        return -1;
    }

    /* 동시에 접속하는 클라이언트의 처리를 위한 대기 큐를 설정 */
    if(listen(ssock, 8) < 0) {
        perror("listen()");
        return -1;
    }

    clen = sizeof(cliaddr);
    int i;
    do {
        /* 클라이언트가 접속하면 접속을 허용하고 클라이언트 소켓 생성 */
        int csock = accept(ssock, (struct sockaddr *)&cliaddr, &clen);

        /* 네트워크 주소를 문자열로 변경 */
        inet_ntop(AF_INET, &cliaddr.sin_addr, mesg, BUFSIZ);
        printf("Client is connected : %s\n", mesg);

        cs[g_noc] = (c_sock*)malloc(sizeof(c_sock));
        strcpy(cs[g_noc]->ip,mesg);
        cs[g_noc]->csfd = csock;
        cs[g_noc]->s_id = g_noc;
        g_noc++;
        i = g_noc;

        write(f[1], &i, sizeof(int));
        kill(getpid(), SIGUSR1);
        /* 연결되는 클라이언트와의 통신을 위한 자식 프로세스 생성 */
        if((pid = fork()) < 0) {  
          perror("Error");
        } else if(pid == 0) {
          do {
            memset(mesg, 0, BUFSIZ);
            if((n = read(csock, mesg, BUFSIZ)) <= 0)
              perror("read()");
            printf("(%s) Received data : %s", cs[g_noc-1]->ip,mesg);
            // write(p[1], mesg, sizeof(mesg));
            // kill(getpid(), SIGUSR1);
            broadcast_message(mesg, csock);
          } while(strncmp(mesg, "q", 1));
        }
        close(csock); 			/* 클라이언트 소켓을 닫음 */
    } while(strncmp(mesg, "q", 1));

    close(ssock); 			/* 서버 소켓을 닫음 */

    return 0;
}