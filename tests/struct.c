
#include "libcx/vec.h"

typedef struct point {
    int x;
    int y;
} point;

void print(any a)
{
    point *p = ptr(a);
    printf("x: %d, y: %d\n", p->x, p->y);
}

int main()
{
    vec v = vec();
    move_copy(v, ((point []) {
        { .x = 2, .y = 5 },
        { .x = 7, .y = 0 },
        { .x = 3, .y = 3 }
    }));
    foreach(v, print);
}
