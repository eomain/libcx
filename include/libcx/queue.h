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

#ifndef LIBCX_QUEUE_H
#define LIBCX_QUEUE_H

#include <stddef.h>

#include "libcx/any.h"
#include "libcx/type.h"

#define queue() libcx_queue_new()

struct queue;
typedef struct queue *queue;

extern struct queue *libcx_queue_with(size_t);
extern struct queue *libcx_queue_new(void);
extern void libcx_queue_destroy(struct queue *);
extern any libcx_queue_front(struct queue *);
extern void libcx_queue_enqueue(struct queue *, any);
extern any libcx_queue_dequeue(struct queue *);
extern size_t libcx_queue_len(struct queue *);
extern void libcx_queue_debug(const char *, struct queue *);

#endif
