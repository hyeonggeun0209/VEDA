#include <stdio.h>
#include <stdlib.h>

typedef struct train {
int seats;
Train *next;
} Train;

int main() {
    Train *Head, *Tail;
    Head = Tail = NULL;
    for (int i = 0; i < 5; i++) {
        if(Head == NULL) {
            Head = Tail = malloc(sizeof(Train));
        } else {
            Tail->next = malloc(sizeof(Train));
            Tail = Tail->next;
        }
        Head->next
    }

    return 0;
}