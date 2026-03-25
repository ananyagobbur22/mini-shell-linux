#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

struct job
{
    int pid;
    char cmd[50];
};

extern struct job jobs[10];
extern int job_count;
extern char prompt[50];

void scan_input(void);
void execute_command(char *input);
void signal_handler(int sig);

#endif