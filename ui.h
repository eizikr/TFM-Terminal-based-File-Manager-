#ifndef UI_H
#define UI_H
#include "filesystem.h"

void rename_item(const char* file_path);
void view_file(const char* file);
void remove_file(const char* file_path);
void draw_dir_name();
void draw_file_list(file_item_t *head, int selected_index);

#endif