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

#include <stddef.h>

#include "libcx/any.h"
#include "libcx/mem.h"
#include "libcx/type.h"
#include "libcx/vec.h"

#define VEC_MAX_ALLOC 4096
#define VEC_DEFAULT_SIZE 8

struct vec {
    any *data;
    size_t length;
    size_t capacity;
};

struct vec *libcx_vec_with(size_t len)
{
    struct vec *vec;
    vec = libcx_alloc(sizeof *vec);
    vec->data = libcx_zalloc(len * sizeof *vec->data);
    vec->length = 0;
    vec->capacity = len;
    return vec;
}

struct vec *libcx_vec_new(void)
{
    return libcx_vec_with(VEC_DEFAULT_SIZE);
}

void libcx_vec_destroy(struct vec *vec)
{
    if (vec->data)
        libcx_free(vec->data);
    libcx_free(vec);
}

void libcx_vec_append(struct vec *vec, struct vec *v)
{
    size_t len = libcx_vec_len(v);

    for (size_t i = 0; i < len; ++i)
        libcx_vec_push(vec, v->data[i]);
}

void libcx_vec_clone(struct vec *vec)
{
    struct vec *v = libcx_vec_new();
    return libcx_vec_append(v, vec);
}

any libcx_vec_get(struct vec *vec, size_t index)
{
    any v = libcx_any_default();
    if (index < vec->length)
        v = vec->data[index];
    return v;
}

any *libcx_vec_get_ref(struct vec *vec)
{
    return vec->data;
}

any libcx_vec_set(struct vec *vec, size_t index, any v)
{
    any n = libcx_any_default();
    if (index < vec->length) {
        n = vec->data[index];
        vec->data[index] = v;
    }
    return n;
}

any libcx_vec_pop(struct vec *vec)
{
    size_t index;
    any v = libcx_any_default();

    if (vec->length > 0) {
        index = (vec->length - 1);
        v = vec->data[index];
        vec->length--;
    }
    return v;
}

void libcx_vec_push(struct vec *vec, any v)
{
    size_t index;
    index = vec->length;

    if (index >= vec->capacity) {
        size_t len;
        if ((vec->capacity * 2) < (VEC_MAX_ALLOC / 2))
            len = (vec->capacity * 2);
        else
            len = (vec->capacity + VEC_MAX_ALLOC);

        vec->data = libcx_realloc(vec->data, len * sizeof *vec->data);
        vec->capacity = len;
    }

    vec->data[index] = v;
    vec->length++;
}

size_t libcx_vec_len(struct vec *vec)
{
    return vec->length;
}

void libcx_vec_foreach(struct vec *vec, foreach_f f)
{
    size_t len = libcx_vec_len(vec);

    for (size_t i = 0; i < len; ++i)
        f(vec->data[i]);
}

struct vec *libcx_vec_map(struct vec *vec, map_f f)
{
    size_t len;
    struct vec *v;

    len = libcx_vec_len(vec);
    v = libcx_vec_with(len);

    for (size_t i = 0; i < len; ++i)
        libcx_vec_push(v, f(vec->data[i]));

    return v;
}

void libcx_vec_debug(const char *fmt, struct vec *vec)
{
	size_t len = libcx_vec_len(vec);
	if (len == 0) {
		printf("[]\n");
	} else {
		printf("[");
		if (len > 1) {
			for (size_t i = 0; i < len - 1; ++i) {
				libcx_any_debug(fmt, libcx_vec_get(vec, i));
                printf(", ");
            }
		}
		libcx_any_debug(fmt, libcx_vec_get(vec, len - 1));
		printf("]\n");
	}
}
