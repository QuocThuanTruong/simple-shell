#ifndef _HISTORY_H_
#define _HISTORY_H_

#include "global_includes.h"

void aloc_history_list(char **history_list);

void free_history_list(char **history_list);

void append_to_history_list(char **history_list, const char* current_cmd, int *history_size);

void show_history_list(char **history_list, int history_size);

char *get_history_at(char **history_list, int history_size, int index);

//If cmd is valid (eg: !2, !3) func will return the index of this cmd in history list else return -1
int is_valid_history_cmd(char* his_cmd, int history_size);         

#endif // !_HISTORY_H_