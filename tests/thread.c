
#include <assert.h>
#include <stdio.h>

#include "libcx/thread.h"

int start(any args)
{
	const char **argv = ptr(args);
	puts(argv[0]);
	yield();
	terminate(1);
	return 0;
}

int main()
{
	struct thread t;
	spawn(&t, start, ((const char *[]){ "Spawned a new thread" }));
	join(&t);
	assert(result(&t) == 1);
	return 0;
}
