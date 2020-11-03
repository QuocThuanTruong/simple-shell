#ifndef _CMD_EXECUTOR_H
#define _CMD_EXECUTOR_H

#include "global_includes.h"

//Forwarding cmd argument when it does not have redirect or pipe operator
void pass_children_execution(char* filename, char *argv[]);
void do_parent(pid_t child_pid, int wait);

//Pipe op
void do_children_pipe();

//Redirect op


#endif // !_CMD_EXECUTOR_H