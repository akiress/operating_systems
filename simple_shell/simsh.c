#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LINE 80

void process_args(char *[], int);

int main(void)
{
    char *prompt;
    char *args[MAX_LINE / 2 + 1];

    int bytes_read;
    int should_run = 1;
    int i;

    size_t nbytes = 100;

    // char copy[MAX_LINE];
    // char *exit = "exit";

    while (should_run)
    {
        int num_args;
        i = 0;

        printf("osh> ");
        fflush(stdout);

        prompt = (char *) malloc (nbytes + 1);
        bytes_read = getline(&prompt, &nbytes, stdin);

        if (bytes_read == -1)
        {
            printf("Read error");
        }
        else
        {
            char *tok;

            printf("%s\n", prompt);

            tok = strtok(prompt, " ");
            while (tok != NULL)
            {
                args[i++] = tok;
                printf("%s\n", tok);
                tok = strtok(NULL, " ");
            }

            fflush(stdin);

            num_args = i;

            printf("%d\n", i);
        }

        for (i = 0; i < num_args; i++)
        {
            printf("%s\n", args[num_args]);
        }

        if (num_args > 0)
        {
            printf("Got at least 1 argument.\n");
            // process_args(args, num_args);
        }


        free(prompt);


        // if (strcmp(args[0], exit) == 0)
        // {
        //     printf("EXITING\n");
        //     should_run = 0;
        // }
        // else if (args[1] != NULL)
        // {
        //     printf("Got arguments\n");
        //     int i = 0;
        //     for (i = 0; i < (int)sizeof(args) / 8; i++)
        //     {
        //         printf("%d\n", i);

        //         if (args[i] != NULL)
        //         {
        //             printf("%s\n", args[i]);
        //         } else if (args[i] == NULL) {
        //             printf("GOT NULL\n");
        //         } else {
        //             printf("GOT SHIT\n");
        //         }
        //     }
        // }
        // else
        // {
        //     printf("NOT EXITING\n");
        // }

        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will invoke wait()
         */
    }

    return 0;
}

void process_args(char *args[], int num_args)
{
    int i = 0;
    for (i = 0; i < num_args; i++)
    {
        printf("%s\n", args[num_args]);
    }
}