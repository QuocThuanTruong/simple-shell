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

void do_children_re_to_file(char **args, char *dir)
{
    int file_descriptor;

    file_descriptor = creat(dir, S_IRWXU);

    if (file_descriptor == -1)
    {
        perror(ERROR_MESS);
        exit(EXIT_FAILURE);
    }

    //Duplicate fd to std out
    dup2(file_descriptor, STDOUT_FILENO);

    if (close(file_descriptor) == -1)
    {
        perror(ERROR_MESS);
        exit(EXIT_FAILURE);
    }

    //Execution after duplicate fd
    pass_children_execution(args[0], args);
}

void do_children_re_from_file(char **args, char *dir)
{
    int file_descriptor;

    file_descriptor = open(dir, O_RDONLY);

    if (file_descriptor == -1)
    {
        perror(ERROR_MESS);
        exit(EXIT_FAILURE);
    }

    //Duplicate fd to std in
    dup2(file_descriptor, STDIN_FILENO);

    if (close(file_descriptor) == -1)
    {
        perror(ERROR_MESS);
        exit(EXIT_FAILURE);
    }

    //Execution after duplicate fd
    pass_children_execution(args[0], args);
}

void do_children_pipe(char **args_pipe_write, char **args_pipe_read)
{
    
}