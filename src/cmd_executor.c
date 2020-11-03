#include "cmd_executor.h"

void pass_children_execution(char* filename, char *argv[])
{
    if (execvp(filename, argv) == -1)
    {
        perror(ERROR_MESS);
        exit(EXIT_FAILURE);
    }
}

void do_parent(pid_t child_pid, int wait)
{
    static int bg_proc_counter = 0;
    int child_status;

    switch (wait) {
        // parent and child run concurrently
        case 0: {
            waitpid(child_pid, &child_status, 0);
            break;
        }
        // parrent wait for child
        // case '&' | run in background.
        default:
            bg_proc_counter += 1;

            printf("[%d] %d\n",bg_proc_counter,child_pid);
            waitpid(child_pid, &child_status, WUNTRACED);

            if (WIFEXITED(child_status))
            {
                bg_proc_counter -=1;
                printf("[%d] is finished and exited with status %d\n", child_pid, child_status);
            }
            break;
    }
}