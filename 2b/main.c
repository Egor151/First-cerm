#include "queue.h"
#include "mymath.h"
#include "computation.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void process(Result *table, int nodes, Queue **compute_queues, Queue **result_queues, int angle_start, int angle_end, int n_min, int n_max)
{
    int cur_queue = 0;
    for (int i = angle_start; i <= angle_end; ++i) {
        while (get_rand(0, 100) < 75) {
            cur_queue = get_rand(0, nodes - 1);
        }

        place_task(compute_queues[cur_queue], i, get_rand(n_min, n_max));
        compute(compute_queues[cur_queue], result_queues[cur_queue]);
        get_result(result_queues[cur_queue], table, i - angle_start);
    }
}

int main()
{
    int arg[5];
    printf("Введите 5 аргументов:\nколичество ведомых узлов, диапазон углов,\nдиапазон количества членов ряда в разложении:\n");

    for(int i = 0; i < 5; ++i) {
        int inp = scanf("%d", arg + i);
        if (inp < 1) {
            printf("Ошибка ввода.\n");
            return 1;
        }
    }
    
    int nodes = arg[0], begin = arg[1], end = arg[2], nmin = arg[3], nmax = arg[4];

   
    Result* table = calloc(end - begin + 1, sizeof(Result));
    for (int i = 0; i < end - begin + 1; ++i) {
        table[i].angle = begin + i;
        table[i].result = NAN;
    }

    Queue **compute_queues = calloc(nodes, sizeof(Queue *));
    Queue **result_queues = calloc(nodes, sizeof(Queue *));
    for (int i = 0; i < nodes; ++i) {
        compute_queues[i] = init_queue();
        result_queues[i] = init_queue();
    }

    
    process(table, nodes, compute_queues, result_queues, begin, end, nmin, nmax);

   
    for(int i = 0; i < end - begin + 1; ++i) {
        printf("%d\t%lf\n", (int) table[i].angle, table[i].result);
    }

    free(table);
    for (int i = 0; i < nodes; ++i) {
        free_queue(result_queues[i]);
        free_queue(compute_queues[i]);
    }
    free(result_queues);
    free(compute_queues);
    return 0;
}

