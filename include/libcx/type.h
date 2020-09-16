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

#ifndef LIBCX_TYPE_H
#define LIBCX_TYPE_H

#include "libcx/any.h"

typedef void (*foreach_f)(any_t);
typedef any_t (*map_f)(any_t);

#include "libcx/queue.h"
#include "libcx/vec.h"

#define array_len(array) (sizeof (array) / sizeof (*array))

#define append(ty, other) _Generic((ty), struct vec *: libcx_vec_append)(ty, other)
#define copy(ty, array) \
    for (size_t i = 0; i < array_len(array); ++i) \
        _Generic((ty), \
            struct vec *: libcx_vec_push, \
            struct queue *: libcx_queue_enqueue) \
            (ty, any((array)[i]));
#define move_copy(ty, array) \
    for (size_t i = 0; i < array_len(array); ++i) \
        push(ty, data((array)[i]));
#define debug(fmt, ty) \
    _Generic((ty), \
        any: libcx_any_debug_ln, \
        struct vec *: libcx_vec_debug, \
        struct queue *: libcx_queue_debug) \
        (fmt, ty)
#define dequeue(ty) _Generic((ty), struct queue *: libcx_queue_dequeue)(ty)
#define destroy(ty) \
    _Generic((ty), \
        struct vec *: libcx_vec_destroy, \
        struct queue *: libcx_queue_destroy)(ty)
#define enqueue(ty, e) _Generic((ty), struct queue *: libcx_queue_enqueue)(ty, any(e))
#define foreach(ty, f) _Generic((ty), struct vec *: libcx_vec_foreach)(ty, f)
#define front(ty) _Generic((ty), struct queue *: libcx_queue_front)(ty)
#define get(ty, v) \
	_Generic((ty), \
		struct vec *: libcx_vec_get) \
		(ty, v)
#define len(ty) \
	_Generic((ty), \
		struct vec *: libcx_vec_len, \
		struct queue *: libcx_queue_len) \
		(ty)
#define map(ty, f) _Generic((ty), struct vec *: libcx_vec_map)(ty, f)
#define move(ty, s) push(ty, data(s))
#define push(ty, e) \
	_Generic((ty), \
		struct vec *: libcx_vec_push) \
		(ty, any(e))
#define pop(ty) _Generic((ty), struct vec *: libcx_vec_pop)(ty)

#endif
