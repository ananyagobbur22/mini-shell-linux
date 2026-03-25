#include "header.h"

struct job jobs[10];
int job_count = 0;
char prompt[50] = "minishell$ ";

int main()
{
    signal(SIGINT, signal_handler); // Shell handles Ctrl+C 
    signal(SIGTSTP, signal_handler); //Shell handles Ctrl+Z

    scan_input();
    return 0;
}