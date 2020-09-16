
#include "libcx/vec.h"

int main()
{
	// Create a new vec
	vec a = vec();
	// An array of data
	char *const fruits[] = {
		"apple", "banana", "cherry"
	};
	// Copy array into vec
	copy(a, fruits);

	// Create another vec
	vec b = vec();
	// Copy compound literal
	copy(b, ((char *const []){"x", "y", "z"}));

	// Append vec b to a
	append(a, b);

	// Display values as a string
	debug("%s", a);

	destroy(a);
	destroy(b);
}
