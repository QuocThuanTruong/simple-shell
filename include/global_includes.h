#ifndef _GLOBAL_INCLUDES_
#define _GLOBAL_INCLUDES_

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>

#define OP_CODE_RUN_BG                  1
#define OP_CODE_RE_TO_FILE              2
#define OP_CODE_RE_FROM_FILE            3
#define OP_CODE_RE_APPEND_TO_FILE       4
#define OP_CODE_RE_APPEND_FROM_FILE     5

#define HISTORY_SIZE                    100
#define CMD_LENGTH                      200
#define SHELL_NAME                      "osh> "

#define CMD_EXIT                        "exit"

#endif // !_GLOBAL_INCLUDES_
