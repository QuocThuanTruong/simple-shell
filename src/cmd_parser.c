#include "cmd_parser.h"

void parse_cmd(char *cmd, char **args_1, int *op_code, char **args_2)
{
    memset(args_1, 0, CMD_LENGTH + 1);
    memset(args_2, 0, CMD_LENGTH + 1);

    int i;
    int len_cmd = strlen(cmd);

    for (i = 0; i < len_cmd; ++i) {
        if (cmd[i] == '&') {

            *op_code = OP_CODE_RUN_BG;
            break;

            printf("%s", cmd);

        } else if(cmd[i] == '>') {

            *op_code = OP_CODE_RE_TO_FILE;
            break;

        } else if (cmd[i] == '<') {

            *op_code = OP_CODE_RE_FROM_FILE;
            break;
       
        } else if (cmd[i] == '|') {

            *op_code = OP_CODE_PIPE;
            break;

        }
    }

    char* args[CMD_LENGTH];
    memset(args, 0, CMD_LENGTH + 1);

    int count_args = 0;
    const char* delimiters  = {" &><|"};

    char* token = strtok(cmd, delimiters);
    while (token != NULL) {
        args[count_args++] = token;
        token = strtok(NULL, delimiters);
    }

    int count_args_1 = 0;
    int count_args_2 = 0;
   
    if (args[0] != NULL) {
        args_1[count_args_1++] = args[0];
    }
    
    for (i = 1; i < count_args; ++i) {
        if (args[i][0] != '-') {
            break;
        } else {
            args_1[count_args_1++] = args[i];
        }
    }

    for (; i < count_args; ++i) {
        args_2[count_args_2++] = args[i];
    }

    if (*op_code != NO_OP_CODE && *op_code != OP_CODE_RUN_BG && count_args_2 == 0) {
        *op_code = OP_CODE_UNKNOWN;
    } else {
        //Do Nothing
    }

    args_1[count_args_1] = 0;
    args_2[count_args_2] = 0;
}