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
    for(int i = 0;i < HISTORY_SIZE; i++)
    {
        if(history_list[i] != NULL)
        {
            free(history_list[i]);
        }
    }
}

void append_to_history_list(char **history_list, const char* current_cmd, int *history_size)
{
    if(history_size != 0)
    {
        if(strcmp(current_cmd, history_list[history_size - 1]) == 0)
        {
            return;
        }
    }
    else if(history_size < HISTORY_SIZE)
    {
        strcpy(history_list[history_size], current_cmd);
        history_size++;
    }
    else 
    {
        for(int i = 0; i < history_size; i++)
        {
            strcpy(history_list[i- 1], history_list[i]);
        }
        strcpy(history_list[history_size - 1], current_cmd);
    }
}

void show_history_list(char **history_list, int history_size)
{
    if(history_size == 0)
    {
        printf("history list is empty\n");
    }
    else
    {
        for(int i = 0; i < history_size; i++)
        {
            printf ("%d %s\n", i + 1, history_list[i]);
        }
    }
}

char *get_history_at(char **history_list, int history_size, int index)
{
    if(index > history_size || index < 0 || history_size == 0)
    {
        return NULL;
    }
    else
    {
        return history_list[index];
    }
}