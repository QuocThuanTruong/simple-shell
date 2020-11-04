#include "cmd_parser.h"

void parse_cmd(char *cmd, char **args_1, int *op_code, char **args_2)
{
    memset(args_1, 0, CMD_LENGTH);
    memset(args_2, 0, CMD_LENGTH);

    char* args[CMD_LENGTH];
    memset(args, 0, CMD_LENGTH + 1);

    int count_args = 0;
    const char* delimiters  = {" "};
    char* token = strtok(cmd, delimiters);
    //ls -l -t &
    //ls -l -t > input.txt
    while (token != NULL) {
        args[count_args++] = token;
        token = strtok(NULL, delimiters);
    }

    int i;
    int count_args_1 = 0;
    int count_args_2 = 0;
    bool flag_append_args1 = true;

    for (i = 0; i < count_args; ++i) {
        if (strcmp(args[i], "&") == 0) {

            *op_code = OP_CODE_RUN_BG;
            flag_append_args1 = false;

        } else if(strcmp(args[i], ">") == 0) {

            *op_code = OP_CODE_RE_TO_FILE;
            flag_append_args1 = false;

        } else if (strcmp(args[i], "<") == 0) {

            *op_code = OP_CODE_RE_FROM_FILE;
            flag_append_args1 = false;

        } else if (strcmp(args[i], "|") == 0) {

            *op_code = OP_CODE_PIPE;
            flag_append_args1 = false;

        } else {
            if (flag_append_args1) {

                args_1[count_args_1++] = args[i];

            } else {

                args_2[count_args_2++] = args[i];
                
            }
        }
    }

    if (*op_code != NO_OP_CODE && *op_code != OP_CODE_RUN_BG && count_args_2 == 0) {
        *op_code = OP_CODE_UNKNOWN;
    } else {
        //Do Nothing
    }

    args_1[count_args_1] = 0;
    args_2[count_args_2] = 0;
}