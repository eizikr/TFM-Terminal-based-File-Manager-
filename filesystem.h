#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ncurses.h>
#include <dirent.h>     //  readdir() and opendir()
#include <sys/stat.h>   //  stat() and lstat()          to get information about files and directories
#include <unistd.h>     //  chdir(), rmdir(), unlink()
#include <stdbool.h>

typedef struct file_item{
    char* name;
    struct file_item* next;
} file_item_t;

file_item_t* read_directory(bool hidden_flag);
file_item_t* get_item(file_item_t* list, int index);
int count_files(file_item_t* list);
void free_list(file_item_t* list);
#endif