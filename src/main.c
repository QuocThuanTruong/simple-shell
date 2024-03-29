#include "global_includes.h"

static int get_input_cmd(char* input_cmd)
{
    int is_get_ok = 1;

    while (fgets(input_cmd, CMD_LENGTH, stdin) == NULL) 
    {
        perror(INVALID_INPUT);
        fflush(stdin);
    }

    //Replace end char to '\0'
    input_cmd[strcspn(input_cmd, "\n")] = '\0';
    if (input_cmd[0] == '\0')
    {
        is_get_ok = 0;
    }

    return is_get_ok;
}

int main()
{
    int should_run = 1;                 //Flag to determine when to exit program: 0 - exit, 1 - run
    int is_waiting = 1;                       //Flag parent process is_waiting for child process
    int op_code = NO_OP_CODE;           //Operation code get from input cmd

    char input_cmd[CMD_LENGTH];         
    char *args_1[CMD_LENGTH];
    char *args_2[CMD_LENGTH];

    char **history_list = (char**) malloc(HISTORY_SIZE * sizeof(char*));
    int history_size = 0;
    aloc_history_list(history_list);

    while (should_run)
    {
        printf("%s", SHELL_NAME);
        fflush(stdout);

        if (get_input_cmd(input_cmd) == 0)
        {
            continue;
        }

        //User enter exit
        if (strcmp(input_cmd, CMD_EXIT) == 0)
        {
            should_run = 0;
            continue;
        }

        if (input_cmd[0] == '!')
        {
            int hist_index = is_valid_history_cmd(input_cmd, history_size);
            char *cmd_in_hist = get_history_at(history_list, history_size, hist_index);
       
            if (cmd_in_hist != NULL)
            {              
                strcpy(input_cmd, cmd_in_hist);
                printf("%s%s\n", SHELL_NAME, cmd_in_hist);
                fflush(stdout);   
            } 
            else
            {
                printf("%s : Invalid Command\n", input_cmd);
                fflush(stdout);
                continue;
            }
        }

        if (history_size > 0 && strcmp(history_list[history_size - 1], "history") == 0 && strcmp(input_cmd, "history") == 0)
        {
            printf("\033[1A\033[1;\033[K");
            continue;
        }

        append_to_history_list(history_list, input_cmd, &history_size);
           
        //TODO: Parse input cmd here
        op_code = NO_OP_CODE;
        parse_cmd(input_cmd, args_1, &op_code, args_2);

        if (op_code == OP_CODE_RUN_BG) {
            is_waiting = 0;
        } 
        else if (op_code == NO_OP_CODE)
        {
            if (strcmp(input_cmd, "history") == 0)
            {
                do_history(args_1, history_list, &history_size);             
                continue;
            }
        }
        else if (op_code == OP_CODE_UNKNOWN)
        {
            perror("Invalid syntax: ");
        }

        //fork() process
        pid_t pid = fork();

        switch (pid)
        {
            case -1:    //Unable to fork
                break;
            case 0:     //Successfull to fork, and in child process
                //Check op code
                switch (op_code)
                {
                    case OP_CODE_RE_TO_FILE:
                        do_children_re_to_file(args_1, args_2[0]);
                        break;
                    case OP_CODE_RE_FROM_FILE:
                        do_children_re_from_file(args_1, args_2[0]);
                        break;
                    case OP_CODE_PIPE:
                        do_children_pipe(args_1, args_2);
                        break;
                    default:
                        //When input cmd does not have op code
                        pass_children_execution(args_1[0], args_1);
                        break;
                }

                exit(EXIT_FAILURE);
                break;
            default: //Successfull to fork, and in parent process
                //do parent
                do_parent(pid, is_waiting);
                break;
        }

        is_waiting = 1;
    }

    free_history_list(history_list);

    return 0;
}