#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SW      5   /* GPIO24 */
#define CDS     0   /* GPIO17 */
#define LED     1   /* GPIO18 */
#define BUZZER  6   /* GPIO23 */ /* 부저 연결 핀 번호 */

void *webserverFunction(void *arg);
void *switchThread(void *arg);
void *cdThread(void *arg);
static void *clnt_connection(void *arg);
int sendData(FILE* fp, char *ct, char *filename);
void sendOk(FILE* fp);
void sendError(FILE* fp);

int main() {
    wiringPiSetup();

    pinMode(SW, INPUT);       /* 스위치 입력 설정 */
    pinMode(CDS, INPUT);      /* 조도 센서 입력 설정 */
    pinMode(LED, OUTPUT);     /* LED 출력 설정 */
    pinMode(BUZZER, OUTPUT);  /* 부저 출력 설정 */

    pthread_t swThread, cdsThread, webserverThread;

    /* 스레드 생성 */
    pthread_create(&swThread, NULL, switchThread, NULL);
    pthread_create(&cdsThread, NULL, cdThread, NULL);
    pthread_create(&webserverThread, NULL, webserverFunction, NULL);

    /* 메인 스레드는 다른 스레드가 종료될 때까지 대기 */
    pthread_join(swThread, NULL);
    pthread_join(cdsThread, NULL);

    return 0;
}

/* 스위치 입력을 처리하는 스레드 */
void *switchThread(void *arg) {
    for (;;) {
        if (digitalRead(SW) == LOW) /* 스위치가 눌렸을 때 */
        {
            /* LED 켜기 */
            // digitalWrite(LED, HIGH);
            // delay(500);
            /* LED 끄기 */
            digitalWrite(LED, LOW);
            delay(500);
        }
        delay(100); /* CPU 과부하를 방지하기 위한 딜레이 */
    }
    return NULL;
}

/* 조도 센서 입력을 처리하는 스레드 */
void *cdThread(void *arg) {
    for (;;) {
        if (digitalRead(CDS) == LOW) /* 어두울 때 */
        {
            /* 부저 울리기 */
            digitalWrite(LED, HIGH);
            delay(500);
            /* 부저 끄기 */
            // digitalWrite(LED, LOW);
        }
        delay(100); /* CPU 과부하를 방지하기 위한 딜레이 */
    }
    return NULL;
}

void *webserverFunction(void *arg) {
    int ssock;
    pthread_t thread;
    struct sockaddr_in servaddr, cliaddr;
    unsigned int len;

    int port = (int)(arg);

    // 서버를 위한 소켓을 생성한다.
    ssock = socket(AF_INET, SOCK_STREAM, 0);
    if(ssock == -1) {
        perror("socket()");
        exit(1);
    }


/* 입력받는 포트 번호를 이용해서 서비스를 운영체제에 등록한다. */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if(bind(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr))==-1) {
        perror("bind()");
        exit(1);
    }
    
    /* 최대 10대의 클라이언트의 동시 접속을 처리할 수 있도록 큐를 생성한다. */
    if(listen(ssock, 10) == -1) {
        perror("listen()");
        exit(1);
    }

    while(is_run) {
        char mesg[BUFSIZ];
        int csock;

        /* 클라이언트의 요청을 기다린다. */
        len = sizeof(cliaddr);
        csock = accept(ssock, (struct sockaddr*)&cliaddr, &len);

        /* 네트워크 주소를 문자열로 변경 */
        inet_ntop(AF_INET, &cliaddr.sin_addr, mesg, BUFSIZ);
        printf("Client IP : %s:%d\n", mesg, ntohs(cliaddr.sin_port));

        /* 클라이언트의 요청이 들어오면 스레드를 생성하고 클라이언트의 요청을 처리한다. */
        pthread_create(&thread, NULL, clnt_connection, &csock);
    //    pthread_join(thread, NULL);
    }

    return 0;
}

void *clnt_connection(void *arg)
{
    /* 스레드를 통해서 넘어온 arg를 int 형의 파일 디스크립터로 변환한다. */
    int csock = *((int*)arg);
    FILE *clnt_read, *clnt_write;
    char reg_line[BUFSIZ], reg_buf[BUFSIZ];
    char method[BUFSIZ], type[BUFSIZ];
    char filename[BUFSIZ], *ret;

    /* 파일 디스크립터를 FILE 스트림으로 변환한다. */
    clnt_read = fdopen(csock, "r");
    clnt_write = fdopen(dup(csock), "w");

    /* 한 줄의 문자열을 읽어서 reg_line 변수에 저장한다. */
    fgets(reg_line, BUFSIZ, clnt_read);
    
    /* reg_line 변수에 문자열을 화면에 출력한다. */
    fputs(reg_line, stdout);

    /* ' ' 문자로 reg_line을 구분해서 요청 라인의 내용(메소드)를 분리한다. */
    ret = strtok(reg_line, "/ ");
    strcpy(method, (ret != NULL)?ret:"");
    if(strcmp(method, "POST") == 0) { 		/* POST 메소드일 경우를 처리한다. */
        sendOk(clnt_write); 			/* 단순히 OK 메시지를 클라이언트로 보낸다. */
        goto END;
    } else if(strcmp(method, "GET") != 0) {	/* GET 메소드가 아닐 경우를 처리한다. */
        sendError(clnt_write); 			/* 에러 메시지를 클라이언트로 보낸다. */
        goto END;
    }

    ret = strtok(NULL, " "); 			/* 요청 라인에서 경로(path)를 가져온다. */
    strcpy(filename, (ret != NULL)?ret:"");
    if(filename[0] == '/') { 			/* 경로가 '/'로 시작될 경우 /를 제거한다. */
        for(int i = 0, j = 0; i < BUFSIZ; i++, j++) {
            if(filename[0] == '/') j++;
            filename[i] = filename[j];
            if(filename[j] == '\0') break;
        }
    }

    /* URL에 경로(path)이 없을 때 기본 처리 */
    if(!strlen(filename)) strcpy(filename, "index.html");

    /* 라즈베리 파이를 제어하기 위한 HTML 코드를 분석해서 처리한다. */
    if(strstr(filename, "?") != NULL) {
        char optLine[BUFSIZ];
        char optStr[32][BUFSIZ];
        char opt[BUFSIZ], var[BUFSIZ], *tok;
        int count = 0;

        ret = strtok(filename, "?");
        if(ret == NULL) goto END;
        strcpy(filename, ret);
        ret = strtok(NULL, "?");
        if(ret == NULL) goto END;
        strcpy(optLine, ret);

        /* 옵션을 분석한다. */
        tok = strtok(optLine, "&");
        while(tok != NULL) {
            strcpy(optStr[count++], tok);
            tok = strtok(NULL, "&");
        }
 
        /* 분석한 옵션을 처리한다. */
        for(int i = 0; i < count; i++) {
            strcpy(opt, strtok(optStr[i], "="));
            strcpy(var, strtok(NULL, "="));
            printf("%s = %s\n", opt, var);
            if(!strcmp(opt, "led") && !strcmp(var, "On")) { 		/* 8×8 LED 매트릭스를 켬 */
            } else if(!strcmp(opt, "led") && !strcmp(var, "Off")) { 	/* 8×8 LED 매트릭스를 끔 */
            }
        }
    }

    /* 메시지 헤더를 읽어서 화면에 출력하고 나머지는 무시한다. */
    do {
        fgets(reg_line, BUFSIZ, clnt_read);
        fputs(reg_line, stdout);
        strcpy(reg_buf, reg_line);
        char* buf = strchr(reg_buf, ':');
    } while(strncmp(reg_line, "\r\n", 2)); 	/* 요청 헤더는 ‘\r\n’으로 끝난다. */

    /* 파일의 이름을 이용해서 클라이언트로 파일의 내용을 보낸다. */
    sendData(clnt_write, type, filename);

END:
    fclose(clnt_read); 				/* 파일의 스트림을 닫는다. */
    fclose(clnt_write);
    pthread_exit(0); 				/* 스레드를 종료시킨다. */

    return (void*)NULL;
}