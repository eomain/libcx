
# LIBCX
	An easy to use portable C library designed for rapid software development.

## Features
	- Uses modern C language features (requires C11 or later)
	- Common data structures vector, queue, etc.
	- Threading support
	- Focus on performance, efficiency and productivity

## Examples

### Vectors
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

### Threads
```c
#include <stdio.h>

#include "libcx/thread.h"

int start(any args)
{
	puts(ptr(args));
	return 0;
}

int main()
{
	struct thread t;
	spawn(&t, start, "Spawned a new thread");
	join(&t);
	return 0;
}
```

## License
	Distributed under the 2-clause BSD license. See COPYING for more info.
