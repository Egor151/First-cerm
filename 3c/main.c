#include "dialog.h"

int (*fptr[])(Table *) = {0, d_insert, d_delete, d_search, d_print};
const char *msgs[] = {"Exit", "Insert", "Delete", "Search", "Print"};
const int nmsgs = 5;

int main()
{
    Table table;
    
    if (d_create(&table)) {
        return 1;
    }

    int msg;
    while ((msg = dialog(msgs, nmsgs)))
        if (fptr[msg](&table))
            break;

    d_destroy(&table);

    return 0;
}
