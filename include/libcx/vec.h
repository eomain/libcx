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

#ifndef LIBCX_VEC_H
#define LIBCX_VEC_H

#include <stddef.h>
#include <stdlib.h>

#include "libcx/any.h"
#include "libcx/type.h"

#define vec() libcx_vec_new()

struct vec;
typedef struct vec *vec;

extern struct vec *libcx_vec_with(size_t);
extern struct vec *libcx_vec_new(void);
extern void libcx_vec_destroy(struct vec *);
extern void libcx_vec_append(struct vec *, struct vec *);
extern any libcx_vec_get(struct vec *, size_t);
extern any *libcx_vec_get_ref(struct vec *);
extern any libcx_vec_set(struct vec *, size_t, any);
extern any libcx_vec_pop(struct vec *);
extern void libcx_vec_push(struct vec *, any);
extern size_t libcx_vec_len(struct vec *);
extern void libcx_vec_foreach(struct vec *, foreach_f);
extern struct vec *libcx_vec_map(struct vec *, map_f);
extern void libcx_vec_debug(const char *, struct vec *);

#endif
