#include "hqueue.h"

int main(int argc, const char *argv[])
{
    hqueue_t *queue = hqueue_new();
    hqueue_push(queue, "hello");
    hqueue_push(queue, "world");
    printf("%s\n", hqueue_pop(queue));
    printf("%s\n", hqueue_top(queue));
    printf("%ld\n", queue->size);
    hqueue_free(queue);
    return 0;
}
