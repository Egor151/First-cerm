#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int get_int(int *res, int min, int max, char *msg)
{
    int n;
    do {
        printf("%s", msg);
        
        n = scanf("%d", res);
        if (n < 0) {
            return 1;
        }
        
        if (n == 0) {
            printf("Not a number\n");
        } else if (*res < min || *res > max) {
            printf("Number must from %d to %d\n", min, max);
            n = 0;
        }

        scanf("%*[^\n]");
        scanf("%*c");
    } while (n == 0);
    
    return 0;
}

int fget_int(FILE *fd, int *res, int min, int max)
{
    int n;
    do {
        n = fscanf(fd, "%d", res);
        if (n < 0) {
            return 1;
        }
        
        if (*res < min || *res > max) {
            n = 0;
        }

        fscanf(fd, "%*[^\n]");
        fscanf(fd, "%*c");
    } while (n == 0);
    
    return 0;

}

char *readline(char *msg)
{
    printf("%s", msg);

    char *res = calloc(1, sizeof(char));
    char buf[81] = {0};
    int len = 0;

    int n;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            free(res);
            return NULL;
        }

        if (n == 0) {
            scanf("%*c");
        } else {
            len += strlen(buf);
            res = realloc(res, len + 1);
            strcat(res, buf);
        }
    } while (n > 0);

    return res;
}

char *freadline(FILE *fd)
{
    char *res = calloc(1, sizeof(char));
    char buf[81] = {0};
    int len = 0;

    int n;
    do {
        n = fscanf(fd, "%80[^\n]", buf);
        if (n < 0) {
            free(res);
            return NULL;
        }

        if (n == 0) {
            fscanf(fd, "%*c");
        } else {
            len += strlen(buf);
            res = realloc(res, len + 1);
            strcat(res, buf);
        }
    } while (n > 0);

    return res;
}
