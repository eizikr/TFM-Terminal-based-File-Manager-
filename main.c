#include "filesystem.h"
#include "ui.h"

#define NO_ERR  0
#define ERROR     1

file_item_t* change_dir(file_item_t* list, char* path, bool hidden_flag);

int main(int argc, char *argv[]){
    bool hidden_flag                    = (argc > 1 && strcmp(argv[1], "-a") == 0);
    unsigned short int selected_index   = 0;
    unsigned short int files_number     = 0;
    initscr();
    noecho();               //  Turn off the character prints from user
    cbreak();
    keypad(stdscr, TRUE);   //  Enable special buttons 'F1', 'UP', etc ...

    file_item_t *file_list  = read_directory(hidden_flag);
    if (file_list == NULL) {
        endwin();
        fprintf(stderr, "Could not read directory.\n");
        return ERROR;
    }

    files_number = count_files(file_list);
    draw_file_list(file_list, selected_index);
    
    // Main loop
    int ch;
    while((ch = getch()) != 'q')
    {
        if(ch == KEY_UP && ( selected_index > 0 ) ){
            selected_index--;
        }
        if (( ch == KEY_DOWN ) && (selected_index < (files_number - 1)) ){
            selected_index++;
        }
        if ( ch == '\n' ) // if ENTER pressed
        {
            if (file_list != NULL) {
                
                // Check if current file is a directory
                char *selected_name = get_item(file_list, selected_index)->name;

                // Change dir, and clean old list
                file_list = change_dir(file_list, selected_name, hidden_flag);
                files_number = count_files(file_list);
                selected_index = 0;
            }
        }

        if ( ch == KEY_BACKSPACE || ch == 'b'){

        
            file_list = change_dir(file_list, "..", hidden_flag);
            files_number = count_files(file_list);
            selected_index = 0;
            
        }

        if ( ch == KEY_F(2) ){
                
            if (file_list != NULL) {

                char *selected_name = get_item(file_list, selected_index)->name;

                struct stat file_stat;
                if (lstat(selected_name, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
                    view_file(selected_name);
                }
            }
        }

        if (ch == KEY_F(8)){
            char *selected_name = get_item(file_list, selected_index)->name;
            remove_file(selected_name);
            file_list = change_dir(file_list, ".", hidden_flag);
        }

        if (ch == 'c'){
            char *selected_name = get_item(file_list, selected_index)->name;
            rename_item(selected_name);
            file_list = change_dir(file_list, ".", hidden_flag);
        }
        draw_file_list(file_list, selected_index);

    }

    free_list(file_list);
    endwin();
    return NO_ERR;
}



file_item_t* change_dir(file_item_t* list, char* path, bool hidden_flag){
    struct stat file_stat;
    if (lstat(path, &file_stat) != 0 || !S_ISDIR(file_stat.st_mode)) {
        return list;
    }
    
    if (chdir(path) != 0) {
        return list; 
    }

    free_list(list);

    return read_directory(hidden_flag);
}

