
#include "libcx/vec.h"

vec range(int begin, int end)
{
	vec stack = vec();
	for (; begin <= end; begin++)
		push(stack, begin);
	return stack;
}

any inc(any a)
{
	return any(sint(a) + 1);
}

any fact(any a)
{
	int n = sint(a);
	if (n == 1)
		return a;
	else
		return any(n * sint(fact(any(n - 1))));
}

int main()
{
	vec a = range(0, 19);
	vec b = map(a, inc);
	vec c = map(b, fact);
	debug("%d", c);
	destroy(a);
	destroy(b);
	destroy(c);
}
