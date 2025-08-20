#include "ui.h"

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
    
    mvprintw(y_cor + 2, x_cor, "%s\n", "q = Quite, b = Back");
    refresh();
}