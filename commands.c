#include "header.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void signal_handler(int sig)
{
    if (sig == SIGINT) //For Ctrl+C
        printf("\n");

    if (sig == SIGTSTP) // For Ctrl+Z
        printf("\n");
}

void execute_command(char *input)
{
    char *args[10];
    int i = 0;
    int background = 0;

    if (input[0] == '\0')
        return;

    // Built-in echo commands
    if (strcmp(input, "echo $$") == 0)
    {
        printf("%d\n", getpid());
        return;
    }
    if (strcmp(input, "echo $?") == 0)
    {
        printf("0\n");
        return;
    }
    if (strcmp(input, "echo $SHELL") == 0)
    {
        printf("/bin/bash\n");
        return;
    }

    // Tokenize input
    args[i] = strtok(input, " ");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }

    if (args[0] == NULL)
        return;

    // Built-in cd
    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            chdir(getenv("HOME")); // will go to home if no argument
        }
        else
        {
            if (chdir(args[1]) != 0)
                perror("cd");
        }
        return;
    }

    // Check background (&)
    int len = strlen(input);
    if (input[len - 1] == '&')
        background = 1;

    // jobs
    if (strcmp(args[0], "jobs") == 0)
    {
        for (i = 0; i < job_count; i++)
            printf("[%d] %s\n", jobs[i].pid, jobs[i].cmd);
        return;
    }

    // fg
    if (strcmp(args[0], "fg") == 0)
    {
        if (job_count == 0)
        {
            printf("fg: no jobs\n");
            return;
        }
        int pid = jobs[job_count - 1].pid;
        printf("Bringing job [%d] to foreground\n", pid);
        waitpid(pid, NULL, 0); // wait until finished
        job_count--;
        return;
    }

    // bg
    if (strcmp(args[0], "bg") == 0)
    {
        if (job_count == 0)
        {
            printf("bg: no jobs\n");
            return;
        }
        int pid = jobs[job_count - 1].pid;
        printf("Job [%d] running in background\n", pid);
        return;
    }

    // External command
    pid_t pid = fork();

    if (pid == 0) // child
    {
        execvp(args[0], args);
        perror("exec");
        exit(1);
    }
    else // parent
    {
        if (background) // background job
        {
            if (job_count < 10)
            {
                jobs[job_count].pid = pid;
                strcpy(jobs[job_count].cmd, input);
                job_count++;
                printf("[%d] running in background\n", pid);
            }
        }
        else // foreground job
        {
            int status;
            waitpid(pid, &status, WUNTRACED); // allow Ctrl+Z

            // if Ctrl+Z pressed, store in jobs
            if (WIFSTOPPED(status))
            {
                if (job_count < 10)
                {
                    jobs[job_count].pid = pid;
                    strcpy(jobs[job_count].cmd, input);
                    job_count++;
                    printf("[%d]+  Stopped                 %s\n", pid, input);
                }
            }
        }
    }
}
