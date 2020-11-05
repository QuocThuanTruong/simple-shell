#ifndef _CMD_EXECUTOR_H
#define _CMD_EXECUTOR_H

#include "global_includes.h"

//Forwarding cmd argument when it does not have redirect or pipe operator
void pass_children_execution(char* filename, char *argv[]);
void do_parent(pid_t child_pid, int wait);

//Pipe op
void do_children_pipe(char **args_pipe_write, char **args_pipe_read);

//Redirect op
void do_children_re_to_file(char **args, char *dir);
void do_children_re_from_file(char **args, char *dir);

//History
void do_history(char **args, char **history_list, int *history_size);

#endif // !_CMD_EXECUTOR_H