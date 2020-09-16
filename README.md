
# LIBCX
	An easy to use portable C library designed for rapid software development.

## Features
	- Uses modern C language features (requires C11 or later)
	- Common data structures vector, queue, etc.
	- Focus on performance, efficiency and productivity

## Example
```c
#include "libcx/vec.h"

// Define a new data type
typedef struct point {
    int x;
    int y;
} point;

// Prints out type data
void print(any a)
{
    point *p = ptr(a);
    printf("x: %d, y: %d\n", p->x, p->y);
}

int main()
{
	// Create a new vector
    vec v = vec();
	// Append array literal values to the vector
    move_copy(v, ((point []) {
        { .x = 2, .y = 5 },
        { .x = 7, .y = 0 },
        { .x = 3, .y = 3 }
    }));
	// Print each value
    foreach(v, print);
}

```

## License
	Distributed under the 2-clause BSD license. See COPYING for more info.
