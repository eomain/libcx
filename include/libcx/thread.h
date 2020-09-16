/* Copyright 2020 eomain
   this program is licensed under the 2-clause BSD license
   see COPYING for the full license info

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBCX_THREAD_H
#define LIBCX_THREAD_H

#include <stddef.h>
#include <threads.h>

#include "libcx/any.h"
#include "libcx/type.h"

#define spawn(thread, start, args) libcx_thread_spawn(thread, start, any(args))
#define join(thread) libcx_thread_join(thread)
#define result(thread) libcx_thread_result(thread)
#define terminate(res) thrd_exit(res)
#define yield() thrd_yield()

typedef int (*thread_f)(any);

struct thread {
	thrd_t t;
	thread_f start;
	any args;
	int res;
};

extern int libcx_thread_start(void *init);

static inline void libcx_thread_init(struct thread *t, thread_f start, any args)
{
	t->start = start;
	t->args = args;
	t->res = 0;
}

static inline int libcx_thread_spawn(struct thread *t, thread_f start, any args)
{
	libcx_thread_init(t, start, args);
	return thrd_create(&t->t, libcx_thread_start, t);
}

static inline int libcx_thread_join(struct thread *t)
{
	return thrd_join(t->t, &t->res);
}

static inline int libcx_thread_result(struct thread *t)
{
	return t->res;
}

#endif
