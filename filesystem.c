#include "filesystem.h"

file_item_t* read_directory(bool hidden_flag){
    DIR*            dir;
    struct dirent*  entry;
    file_item_t*    head    =    NULL;
    file_item_t*    current =    NULL;

    //  Open the current directory
    dir = opendir(".");
    if(dir == NULL){
        perror("opendir");
        return NULL;
    }

    //  Read content
    while ((entry = readdir(dir)) != NULL){

        if(!hidden_flag && entry->d_name[0] == '.'){
            continue;
        }

        file_item_t* new_item = (file_item_t*)malloc(sizeof(file_item_t));
        if(new_item == NULL){
            perror("malloc");
            break;
        }

        //  Allocate memory and copy the item name
        new_item->name = strdup(entry->d_name);
        new_item->next = NULL;

        // Add item to list
        if(head == NULL){
            head            = new_item;
            current         = head;
        }
        else{
            current->next   = new_item;
            current         = new_item;
        }
    }

    closedir(dir);

    return head;
}

file_item_t* get_item(file_item_t* list, int index){
    file_item_t* curr = list;
    int i = 0;
    while(curr != NULL && index != i++){
        curr = curr->next;
    }
    if(curr == NULL)
    {
        perror("get_item");
    }
    return curr;
}

int count_files(file_item_t* list){
    file_item_t *tmp  = list;
    int files_number = 0;
    while (tmp != NULL)
    {
        files_number++;
        tmp = tmp->next;
    }
    return files_number;
}

void free_list(file_item_t* list){
    file_item_t *current = list;
    while (current != NULL) {
        file_item_t *temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
}