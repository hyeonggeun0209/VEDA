#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define SERVER_FIFO_NAME "s_fifo"
#define CLIENT_FIFO_NAME "c_%d_fifo"

#define BUF_SIZE 1023

typedef struct DATA {
    pid_t c_pid;
    char data[BUF_SIZE + 1];
} data_t;

void make_fifo(const char* file_name);
int open_fifo(const char* file_name, int mode);