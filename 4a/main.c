#include "dialog.h"

int (*fptr[])(Tree *) = {0, d_insert, d_delete, d_search, d_special, d_walk, d_print};
const char *msgs[] = {"Exit", "Insert", "Delete", "Search", "Special", "Walk", "Print"};
const int nmsgs = 7;

int main()
{
    Tree tree;
    
    if (d_create(&tree)) {
        return 1;
    }

    int msg;
    while ((msg = dialog(msgs, nmsgs)))
        if (fptr[msg](&tree))
            break;

    d_destroy(&tree);

    return 0;
}
