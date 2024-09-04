#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>

#define TCP_PORT 5100

int main(int argc, char **argv)
{
    int ssock;
    struct sockaddr_in servaddr;
    fd_set readfds;
    char mesg[BUFSIZ];

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

    do {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        FD_SET(ssock, &readfds);

        select(ssock+1, &readfds, NULL, NULL, NULL);

        if(FD_ISSET(0, &readfds)) {
            int size = read(0, mesg, BUFSIZ);
            write(ssock, mesg, size);
        }
        else if(FD_ISSET(ssock, &readfds)) {
            int size = read(ssock, mesg, BUFSIZ);
            if(size == 0) break;
            write(1, mesg, size);
        }
    } while(strncmp(mesg, "q", 1));

    close(ssock);

    return 0;
}