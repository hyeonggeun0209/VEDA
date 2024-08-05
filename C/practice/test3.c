#include <stdio.h>
#include <string.h>

typedef struct student {
char name[20];
int c;
int cxx;
int qt;
int rank;
double avg;
} Student;


int main() {
    Student arr[30];
    for(int i = 0; i < 30; i++) {
	    scanf("%s %d %d %d",arr[i].name,&arr[i].c, &arr[i].cxx, &arr[i].qt);
        arr[i].rank = 1;
        arr[i].avg = (double)( arr[i].c + arr[i].cxx + arr[i].qt)/3;
    }
    for(int i = 0; i < 30; i++) {
	    for(int j = 0; j < 30; j++) {
            if(arr[i].avg < arr[j].avg) arr[i].rank++;
        }
    }
    for (int i = 0; i < 30; i++) {
        printf("%s %.3f %d\n", arr[i].name, arr[i].avg, arr[i].rank);
    }
    return 0;
}