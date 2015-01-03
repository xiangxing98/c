#include "hlqueue.h"

int main(int argc, const char *argv[])
{
    hlqueue_t *queue = hlqueue_new();
    hlqueue_push(queue, "hello");
    hlqueue_push(queue, "world");
    printf("%s\n", hlqueue_pop(queue));
    printf("%s\n", hlqueue_top(queue));
    printf("%ld\n", queue->size);
    hlqueue_free(queue);
    return 0;
}
