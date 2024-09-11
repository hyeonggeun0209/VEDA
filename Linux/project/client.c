#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TCP_PORT 5200

int main(int argc, char **argv)
{
    int ssock;
    struct sockaddr_in servaddr;
    char mesg[BUFSIZ];
    pid_t pid;                              /* fork( ) 함수를 위한 PID */

    if(argc < 2) {
        printf("Usage : %s IP_ADRESS\n", argv[0]);
        return -1;
    }

    /* 소켓을 생성 */
    if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return -1;
    }

    /* 소켓이 접속할 주소 지정 */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;

    /* 문자열을 네트워크 주소로 변경 */
    inet_pton(AF_INET, argv[1], &(servaddr.sin_addr.s_addr));
    servaddr.sin_port = htons(TCP_PORT);

    /* 지정한 주소로 접속 */
    if(connect(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect()");
        return -1;
    }

    if((pid = fork()) < 0) {
        perror("Error");
    } else if(pid == 0) {
        do {
            fgets(mesg, BUFSIZ, stdin);
            if(strncmp(mesg, "q", 1) == 0) break;
            if(send(ssock, mesg, strlen(mesg), 0) <= 0) { 	/* 데이터를 소켓에 쓴다. */
                perror("send()");
                return -1;
            }
        } while(strncmp(mesg, "q", 1));
    } else {
        do {
            memset(mesg, 0, BUFSIZ);
            if(recv(ssock, mesg, BUFSIZ, 0) <= 0) { 		/* 데이터를 소켓으로부터 읽는다. */
                perror("recv()");
                return -1;
            } else {
                printf("Received data : %s", mesg); 		/* 받아온 문자열을 화면에 출력 */ 
            }
        } while(strncmp(mesg, "q", 1));
    }

    close(ssock); 					/* 소켓을 닫는다. */ 

    return 0;
}