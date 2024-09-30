#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int fndControl(int num)
{
    int i;
    int gpiopins[7] = {1, 2, 4, 7, 8, 15, 16}; 	/* A, B, C, D : 23 18 15 14 */
    for (i = 0; i < 7; i++) {
        pinMode(gpiopins[i], OUTPUT); 	/* 모든 Pin의 출력 설정 */
    }

    for(int i = 0; i < 7; i++) { 	/* FND 초기화 */
        digitalWrite(gpiopins[i], LOW);
    }
    // digitalWrite(gpiopins[2], LOW);
    // digitalWrite(gpiopins[3], LOW);

    getchar( ); 			/* 숫자 표시 대기 */

    for(int i = 0; i < 7; i++) { 	/* FND 초기화 */
        digitalWrite(gpiopins[i], HIGH);
    }

    return 0;
}

int main(int argc, char **argv)
{
    int no;
    if(argc < 2) {
        printf("Usage : %s NO\n", argv[0]);
        return -1;
    }

    no = atoi(argv[1]);
    wiringPiSetup( ); 			/* wiringPi 초기화 */
    fndControl(no);

    return 0;
}