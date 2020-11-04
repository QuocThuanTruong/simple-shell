#include "history.h"

void aloc_history_list(char **history_list)
{
    for(int i = 0; i < HISTORY_SIZE; i++)
    {
        history_list[i] = (char*)malloc(CMD_LENGTH * sizeof(char));
    }
}

void free_history_list(char **history_list)
{
    for(int i = 0; i < HISTORY_SIZE; i++)
    {
        if(history_list[i] != NULL)
        {
            free(history_list[i]);
        }
    }
}

void append_to_history_list(char **history_list, const char* current_cmd, int *history_size)
{
    if(*history_size != 0)
    {
        if(strcmp(current_cmd, history_list[*history_size - 1]) == 0)
        {
            return;
        }
    }

    if(*history_size < HISTORY_SIZE)
    {
        strcpy(history_list[*history_size], current_cmd);
        (*history_size)++;
    }
    else 
    {
        for(int i = 0; i < *history_size; i++)
        {
            strcpy(history_list[i- 1], history_list[i]);
        }

        strcpy(history_list[*history_size - 1], current_cmd);
    }
}

void show_history_list(char **history_list, int history_size)
{
    if(history_size == 0)
    {
        printf("%s", HISTORY_EMPTY_MESS);
    }
    else
    {
        for(int i = 0; i < history_size; i++)
        {
            printf ("%4d  %s\n", i + 1, history_list[i]);
        }
    }
}

char *get_history_at(char **history_list, int history_size, int index)
{
    if(index > history_size || index < 0 || history_size == 0)
    {
        return NULL;
    }
    
    return history_list[index];  
}

static int parse_to_int(char *index_string)
{
    for (int i = 0; i < strlen(index_string); i++)
    {
        if (!isdigit(index_string[i]))
        {
            return -1;
        }
    }

    return atoi(index_string);
}

int is_valid_history_cmd(char* his_cmd, int history_size)
{
    char *hist_index = (char*)malloc(strlen(his_cmd) * sizeof(char));

    if (his_cmd[1] == '!' && his_cmd[2] == '\0')
    {
        return history_size - 1;
    }

    for (int i = 0; i < strlen(his_cmd) - 1; i++)
    {
        hist_index[i] = his_cmd[i + 1];
    }

    hist_index[strlen(his_cmd)] = '\0';

    return parse_to_int(hist_index) - 1;
}