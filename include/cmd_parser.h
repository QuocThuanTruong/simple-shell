#ifndef _CMD_PARSER_H
#define _CMD_PARSER_H

#include "global_includes.h"

void parse_cmd(char *cmd, char **args_1, int *op_code, char **args_2);

#endif // !_CMD_PARSER_H