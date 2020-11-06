#include "cmd_parser.h"

void copy_cmd(char* dest, char* src, int start, int count) {
    int i;
    for (i = 0; i < count; ++i) {
        dest[i] = src[start + i];
    }
}

void parse_cmd(char *cmd, char **args_1, int *op_code, char **args_2)
{
    memset(args_1, 0, CMD_LENGTH + 1);
    memset(args_2, 0, CMD_LENGTH + 1);

    const char* delimiters  = {" \"\'\\"};

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

    char args_1_cmd[CMD_LENGTH];
    memset(args_1_cmd, 0, CMD_LENGTH + 1);
    copy_cmd(args_1_cmd, cmd, 0, i);

    int count_args_1 = 0;
    char* token_1 = strtok(args_1_cmd, delimiters);
    while (token_1 != NULL) {
        args_1[count_args_1++] = token_1;
        token_1 = strtok(NULL, delimiters);
    }

    char args_2_cmd[CMD_LENGTH]; 
    memset(args_2_cmd, 0, CMD_LENGTH + 1);
    copy_cmd(args_2_cmd, cmd, i + 1, len_cmd - i - 1);

    int count_args_2 = 0;
    char* token_2 = strtok(args_2_cmd, delimiters);
    while (token_2 != NULL) {
        args_2[count_args_2++] = token_2;
        token_2 = strtok(NULL, delimiters);
    }

    if (*op_code != NO_OP_CODE && *op_code != OP_CODE_RUN_BG && count_args_2 == 0) {
        *op_code = OP_CODE_UNKNOWN;
    } else {
        //Do Nothing
    }

    args_1[count_args_1] = 0;
    args_2[count_args_2] = 0;
}
