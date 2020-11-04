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
#include <stddef.h>
#include <sys/stat.h>

#define NO_OP_CODE                      -1
#define OP_CODE_UNKNOWN                 0
#define OP_CODE_RUN_BG                  1
#define OP_CODE_RE_TO_FILE              2
#define OP_CODE_RE_FROM_FILE            3
#define OP_CODE_PIPE                    4

#define HISTORY_SIZE                    100
#define CMD_LENGTH                      200

#define SHELL_NAME                      "osh> "
#define CMD_EXIT                        "exit"

#define ERROR_MESS                      "Error: "
#define INVALID_INPUT                   "Invalid input!"
#define HISTORY_EMPTY_MESS              "No commands in history.\n"

#endif // !_GLOBAL_INCLUDES_
