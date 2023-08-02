#include "dialog.h"

int (*fptr[])(Table *) = {0, d_insert, d_delete_release, d_delete, d_search, d_print, d_garbage_collection};
const char *msgs[] = {"Exit", "Insert", "Delete release", "Delete", "Search", "Print", "Garbage collection"};
const int nmsgs = 7;

int main()
{
    Table table;
    
    if (d_load(&table)) {
        return 1;
    }

    int msg;
    while ((msg = dialog(msgs, nmsgs)))
        if (fptr[msg](&table))
            break;

    d_save(&table);

    return 0;
}
