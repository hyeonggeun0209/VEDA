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

void sigfunc(int no) 
{
    printf("Signal : %d(%d)\n", no, g_noc);
    if(--g_noc == 0) exit(0);
}

int main(int argc, char **argv)
{
  int p[2];
  pipe(p);
  c_sock* cs[5];
  int ssock, portno, n;                   /* 소켓 디스크립트 정의 */
  int status;
  struct sockaddr_in servaddr, cliaddr; 	/* 주소 구조체 정의 */
  socklen_t clen;
  pid_t pid;                              /* fork( ) 함수를 위한 PID */
  char mesg[BUFSIZ];

  portno = (argc == 2)?atoi(argv[1]):TCP_PORT;

  signal(SIGCHLD, sigfunc);

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
  int i = 0;

  if((pid = fork()) < 0) {  
    perror("Error");

  } else if (pid == 0) {
    do {
      int csock = accept(ssock, (struct sockaddr *)&cliaddr, &clen);

      /* 네트워크 주소를 문자열로 변경 */
      inet_ntop(AF_INET, &cliaddr.sin_addr, mesg, BUFSIZ);
      printf("Client is connected : %s\n", mesg);

      cs[g_noc] = (c_sock*)malloc(sizeof(c_sock));
      strcpy(cs[g_noc]->ip,mesg);
      cs[g_noc]->csfd = csock;
      cs[g_noc]->s_id = g_noc;
      g_noc++;

      if((pid = fork()) < 0) {  
        perror("Error");
      } else if(pid == 0) {
        do {
          memset(mesg, 0, BUFSIZ);
          if((n = read(csock, mesg, BUFSIZ)) <= 0)
            perror("read()");
          printf("(%s)Received data : %s", cs[g_noc - 1]->ip, mesg);
          write(p[1], mesg, sizeof(mesg));
        } while(strncmp(mesg, "q", 1));
      }
    } while(strncmp(mesg, "q", 1));
  } else {
    while(1) {
      n = read(p[0], mesg, sizeof(mesg));
      for(int i = 0; i < g_noc; i++) {
      if(write(cs[i]->csfd, mesg, n) <= 0) 
        perror("write()");
      }
    }
    wait(&status);
  }
  close(ssock);

  return 0;
}