#include "cmd_parser.h"

void parse_cmd(char *cmd, char **args_1, int *op_code, char **args_2)
{
    printf("Start");
    memset(args_1, 0, CMD_LENGTH);
    memset(args_2, 0, CMD_LENGTH);

    char* args[CMD_LENGTH];
    memset(args, 0, CMD_LENGTH);

    int countArgs = 0;
    const char* delimiters  = {" "};
    char* token = strtok(cmd, delimiters);
    //ls -l -t &
    //ls -l -t > input.txt
    while (token != NULL) {
        args[countArgs++] = token;
        token = strtok(NULL, delimiters);
    }

    int i;
    int countArgs1 = 0;
    int countArgs2 = 0;
    bool flagAppendArgs1 = true;

    for (i = 0; i < countArgs; ++i) {
        if (strcmp(args[i], "&") == 0) {
            *op_code = OP_CODE_RUN_BG;
            flagAppendArgs1 = false;
        } else if(strcmp(args[i], ">") == 0) {
            *op_code = OP_CODE_RE_TO_FILE;
            flagAppendArgs1 = false;
        } else if (strcmp(args[i], "<") == 0) {
            *op_code = OP_CODE_RE_FROM_FILE;
            flagAppendArgs1 = false;
        } else if (strcmp(args[i], "|") == 0) {
            *op_code = OP_CODE_PIPE;
            flagAppendArgs1 = false;
        } else {
            if (flagAppendArgs1) {
                args_1[countArgs1++] = args[i];
            } else {
                args_2[countArgs2++] = args[i];
            }
        }
    }

    if (*op_code != NO_OP_CODE && countArgs2 == 0) {
        *op_code = OP_CODE_UNKNOWN;
    } else {
        //Do Nothing
    }

    args_1[countArgs1] = 0;
    args_2[countArgs2] = 0;
}