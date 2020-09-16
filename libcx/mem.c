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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdnoreturn.h>

#include "libcx/mem.h"

noreturn static void libcx_mem_err(void)
{
    strerror(errno);
    abort();
}

void *libcx_alloc(size_t n)
{
    assert(n > 0);

    void *m;
    if (!(m = malloc(n)))
        libcx_mem_err();
    return m;
}

void *libcx_zalloc(size_t n)
{
    assert(n > 0);

    void *m;
    if (!(m = calloc(1, n)))
        libcx_mem_err();
    return m;
}

void *libcx_realloc(void *m, size_t n)
{
    assert(m != NULL);
    assert(n > 0);

    if (!(m = realloc(m, n)))
        libcx_mem_err();
    return m;
}

void libcx_free(void *m)
{
    assert(m != NULL);
    if (m)
        free(m);
}
