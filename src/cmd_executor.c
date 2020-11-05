#include "cmd_executor.h"

void pass_children_execution(char* filename, char *argv[])
{
    if (execvp(filename, argv) == -1)
    {
        perror(ERROR_MESS);
        exit(EXIT_FAILURE);
    }
}

void do_parent(pid_t child_pid, int is_waiting)
{
    static int bg_proc_counter = 0;
    int child_status;

    switch (is_waiting) {
        case 1: 
            waitpid(child_pid, &child_status, 0);
            break;
        //Simulating do child process in background
        default:
            bg_proc_counter += 1;

            printf("[%d] %d\n",bg_proc_counter,child_pid);
            waitpid(child_pid, &child_status, WNOHANG);

            if (WIFEXITED(child_status))
            {
                printf("[%d] Done\n", bg_proc_counter);
                bg_proc_counter -=1;
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
    //create pipe
    int pipes[2];
    if (pipe(pipes) == -1) {
        perror("Error: pipe not created");
        exit(EXIT_FAILURE);
    }

    //children write into pipe
    pid_t write_pid = fork();
    if (write_pid == 0) {
        dup2(pipes[1], STDOUT_FILENO);

        //close read pipe
        if (close(pipes[0]) == -1) {
            perror("Unexpected error when closing read pipe");
        }

        pass_children_execution(args_pipe_write[0], args_pipe_write);
    }

    //children read from pipe
    pid_t read_pid = fork();
    if (read_pid == 0) {
        dup2(pipes[0], STDIN_FILENO);

        //close write pipe
        if (close(pipes[1]) == -1) {
            perror("Uexpected error when closing write pipe");
        }

        pass_children_execution(args_pipe_read[0], args_pipe_read);
    }

    close(pipes[1]);
    close(pipes[0]);

    //waiting for write and read child finish
    wait(0);
    wait(0);
}

void do_history(char **args, char **history_list, int *history_size)
{
    int args_counter = 0;

    while (args[args_counter] != NULL)
    {
        args_counter++;
    }

    //Exclude arg "history"
    args_counter--;

    if (args_counter == 0)
    {
        show_history_list(history_list, *history_size);
    } 
    else if (args_counter == 1)
    {
        if (strcmp(args[1], "-c") == 0 || strcmp(args[1], "--clear") == 0)
        {
            *history_size = 0;
            printf("History has cleared\n");
        }
    }
    else
    {
        perror("To many arguments for history command");
    }
}