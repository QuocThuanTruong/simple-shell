#include "global_includes.h"

int main()
{
    int should_run = 1; //Flag to determine when to exit program: 0 - exit, 1 - run
    int wait = 0;       //Flag parent process wait for child process
    int op_code = -1;
    char input_cmd[CMD_LENGTH];
    char *args_1[CMD_LENGTH];
    char *args_2[CMD_LENGTH];
    char **history_list = (char**) malloc(HISTORY_SIZE * sizeof(char*));

    while (should_run)
    {
        printf("%s", SHELL_NAME);
        fflush(stdout);

        while (fgets(input_cmd, CMD_LENGTH, stdin) == NULL) 
        {
            perror("Invalid input!");
            fflush(stdin);
        }

        //Replace end char to '\0'
        input_cmd[strcspn(input_cmd, "\n")] = '\0';
        if (input_cmd[0] == '\0')
        {
            continue;
        }

        if (strcmp(input_cmd, CMD_EXIT) == 0)
        {
            should_run = 0;
            continue;
        }

        //TODO: Pare input cmd here
    }

    return 0;
}