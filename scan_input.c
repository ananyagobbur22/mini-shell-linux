#include "header.h"

void scan_input(void)
{
    char input[100];

    while (1)
    {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
            continue;

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
            exit(0);

        // This will change prompt
        if (strncmp(input, "PS1=", 4) == 0)
        {
            strcpy(prompt, input + 4);
            strcat(prompt, " ");
            continue;
        }

        execute_command(input);
    }
}