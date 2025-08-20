#include "ui.h"
#define OK_OPT 0
#define CANCEL_OPT 1

void rename_item(const char* file_path){
    char new_name[256];
    clear();
    mvprintw(0, 0, "Enter new name for: ");
    mvprintw(1, 0, "%s", file_path);
    refresh();

    echo();     // Enable Prints
    mvgetnstr(2, 0, new_name, sizeof(new_name) - 1);    // Get string from user
    noecho();   // Disable Prints

    // Change name
    if (strlen(new_name) > 0) {
        if (rename(file_path, new_name) == 0) {
            mvprintw(4, 0, "Rename successful.");
        } else {
            mvprintw(4, 0, "Error renaming item.");
        }
    } else {
        mvprintw(4, 0, "Rename cancelled. New name cannot be empty.");
    }
    
    refresh();
    getch();
}

void view_file(const char* file_path){

    FILE *file = fopen(file_path, "r");
    if (file == NULL){
        clear();
        mvprintw(0,0, "%s", "Error: Could not open this file.");
        mvprintw(1,0, "%s", "Press any key to return.");
        refresh();
        getch();
        return;
    }

    clear();
    int ch;
    int y = 0;
    while ((ch = fgetc(file)) != EOF){
        if(y >= LINES -1){
            // If reach the end of screen, wait for input and back to start
            mvprintw(y, 0, "-- Press any key to continue --");
            refresh();
            getch();
            clear();
            y = 0;
        }
        // Print the character and move the cursor
        addch(ch);
        if(ch == '\n'){
            y++;
        }
    }

    mvprintw(y + 1, 0, "-- END OF FILE -- Press any key to return to main menu --");
    refresh();
    getch();

    fclose(file);

}

void remove_file(const char* file_path){
    const char *options[] = {"OK", "CANCEL"};
    int selected_option = CANCEL_OPT;
    int ch;
    
    while (TRUE) {
        clear();
        mvprintw(0, 0, "Warning: Are you sure you want to delete this item?");
        mvprintw(1, 0, file_path);

        for (int i = 0; i < 2; i++) {
            if (i == selected_option) {
                attron(A_REVERSE);
            }
            mvprintw(3, 0+(i*3), "%s", options[i]);
            attroff(A_REVERSE);
        }
        refresh();

        ch = getch();

        if (ch == KEY_LEFT && selected_option > 0) {
            selected_option = OK_OPT;
        } else if (ch == KEY_RIGHT && selected_option < 1) {
            selected_option = CANCEL_OPT;
        } else if (ch == '\n') { // ENTER
            break;
        } else if (ch == 27) { // ESC key
            selected_option = CANCEL_OPT;
            break;
        }
    }

    if (selected_option == OK_OPT) {
        struct stat file_stat;
        if (lstat(file_path, &file_stat) == 0) {
            if (S_ISDIR(file_stat.st_mode)) {
                if (rmdir(file_path) == 0) {
                    mvprintw(5, 0, "Directory deleted successfully.");
                } else {
                    mvprintw(5, 0, "Error deleting directory.");
                }
            } else {
                if (unlink(file_path) == 0) {
                    mvprintw(5, 0, "File deleted successfully.");
                } else {
                    mvprintw(5, 0, "Error deleting file.");
                }
            }
        } else {
            mvprintw(5, 0, "Error: Item not found.");
        }
    }
    
    refresh();
}

void draw_dir_name(){
    long size;
    char *buf;
    char *ptr;

    size = pathconf(".", _PC_PATH_MAX);
    if ((buf = (char *)malloc((size_t)size)) != NULL)
        ptr = getcwd(buf, (size_t)size);
    attron(A_BOLD);
    mvprintw(0,0,"%s", ptr);
    attroff(A_BOLD);
}

void draw_file_list(file_item_t *head, int selected_index){
    unsigned short int x_cor=0, y_cor=1;
    file_item_t *temp = head;
    
    clear();

    draw_dir_name();
    
    if(temp == NULL){
        mvprintw(y_cor + 1, x_cor, "%s\n", "[Empty directory]");
    }

    while (temp != NULL) {
        if ((y_cor - 1) == selected_index) {
            attron(A_REVERSE);
        }

        mvprintw(y_cor + 1, x_cor, "%s", temp->name);

        if ((y_cor - 1) == selected_index) {
            attroff(A_REVERSE);
        }

        y_cor++;
        temp = temp->next;
    }
    
    mvprintw(y_cor + 2, x_cor, "%s\n", "q = Quite, b = Back, c = Rename, F2 Read, F8 Remove");
    refresh();
}