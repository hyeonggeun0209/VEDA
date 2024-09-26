#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>

#define SW      5   /* GPIO24 */
#define CDS     0   /* GPIO17 */
#define LED     1   /* GPIO18 */
#define BUZZER  6   /* GPIO23 */ /* 부저 연결 핀 번호 */

void *switchThread(void *arg);
void *cdThread(void *arg);

int main()
{
    wiringPiSetup();

    pinMode(SW, INPUT);       /* 스위치 입력 설정 */
    pinMode(CDS, INPUT);      /* 조도 센서 입력 설정 */
    pinMode(LED, OUTPUT);     /* LED 출력 설정 */
    pinMode(BUZZER, OUTPUT);  /* 부저 출력 설정 */

    pthread_t swThread, cdsThread;

    /* 스레드 생성 */
    pthread_create(&swThread, NULL, switchThread, NULL);
    pthread_create(&cdsThread, NULL, cdThread, NULL);

    /* 메인 스레드는 다른 스레드가 종료될 때까지 대기 */
    pthread_join(swThread, NULL);
    pthread_join(cdsThread, NULL);

    return 0;
}

/* 스위치 입력을 처리하는 스레드 */
void *switchThread(void *arg)
{
    for (;;)
    {
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
void *cdThread(void *arg)
{
    for (;;)
    {
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
