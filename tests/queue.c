
#include "libcx/queue.h"

int main()
{
	// Create a new queue
	queue q = queue();
	// An array of data
	char *const fruits[] = {
		"apple", "banana", "cherry"
	};
	// Copy array into queue
	copy(q, fruits);

	// Remove from the queue
	printf("%s\n", ptr(dequeue(q)));

	// Display values as a string
	debug("%s", q);

	destroy(q);
}
