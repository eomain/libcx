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
#include "libcx/queue.h"

#define QUEUE_DEFAULT_SIZE 8

struct queue {
    any *data;
    size_t length;
    size_t capacity;
    size_t front;
    size_t rear;
};

static void libcx_queue_resize(struct queue *);

struct queue *libcx_queue_with(size_t len)
{
    struct queue *queue;
    queue = libcx_alloc(sizeof *queue);
    queue->data = libcx_zalloc(len * sizeof *queue->data);
    queue->length = 0;
    queue->capacity = len;
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

struct queue *libcx_queue_new(void)
{
    return libcx_queue_with(QUEUE_DEFAULT_SIZE);
}

void libcx_queue_destroy(struct queue *queue)
{
    if (queue->data)
        libcx_free(queue->data);
    libcx_free(queue);
}

any libcx_queue_front(struct queue *queue)
{
    size_t index;
    index = queue->front;
    return queue->data[index];
}

void libcx_queue_enqueue(struct queue *queue, any v)
{
    if ((queue->length > 0) &&
        (queue->front == queue->rear))
        libcx_queue_resize(queue);

    size_t index;
    index = queue->rear;
    queue->data[index] = v;
    queue->rear = ((queue->rear + 1) % queue->capacity);
    queue->length++;
}

any libcx_queue_dequeue(struct queue *queue)
{
    any v = libcx_any_default();
    size_t index;
    index = queue->front;
    v = queue->data[index];
    queue->data[index] = libcx_any_default();
    queue->front = ((queue->front + 1) % queue->capacity);
    queue->length--;
    return v;
}

size_t libcx_queue_len(struct queue *queue)
{
    return queue->length;
}

static void libcx_queue_resize(struct queue *queue)
{
    size_t len, size, index;
    any *buffer;

    index = queue->front;
    len = queue->length;
    size = (queue->capacity * 2);
    buffer = libcx_zalloc((size * sizeof *queue->data));

    for (size_t i = 0; i < len; ++i) {
        buffer[i] = queue->data[index];
        index = ((index + 1) % queue->capacity);
    }

    libcx_free(queue->data);
    queue->data = buffer;
    queue->capacity = size;
    queue->front = 0;
    queue->rear = len;
}

void libcx_queue_debug(const char *fmt, struct queue *queue)
{
	size_t len = libcx_queue_len(queue);
	if (len == 0) {
		printf("[]\n");
	} else {
		printf("[");
		if (len > 1) {
			for (size_t i = queue->front; i < (queue->rear - 1); ++i) {
				libcx_any_debug(fmt, queue->data[i]);
                printf(", ");
            }
		}
		libcx_any_debug(fmt, queue->data[queue->rear - 1]);
		printf("]\n");
	}
}
