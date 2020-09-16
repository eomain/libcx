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

#ifndef LIBCX_ANY
#define LIBCX_ANY

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "libcx/mem.h"

#define any(x) _Generic((x), \
    any: libcx_any_any, \
    bool: libcx_any_bool, \
    signed char: libcx_any_sint, \
    signed int: libcx_any_sint, \
    signed short: libcx_any_sint, \
    signed long: libcx_any_sint, \
    signed long long: libcx_any_sint, \
    unsigned char: libcx_any_uint, \
    unsigned int: libcx_any_uint, \
    unsigned short: libcx_any_uint, \
    unsigned long: libcx_any_uint, \
    unsigned long long: libcx_any_uint, \
    float: libcx_any_float, \
    double: libcx_any_float, \
    default: libcx_any_ptr) \
    (x)

#define ptr(x) (x).p
#define boolean(x) (x).b
#define sint(x) (x).s
#define uint(x) (x).u
#define fp(x) (x).d

#define data(s) libcx_any_data((const void *)&s, sizeof s)

typedef union {
    void *p;
    bool b;
    signed long long int s;
    unsigned long long int u;
    double d;
} any;

typedef any any_t;

static inline any libcx_any_ptr(const void *ptr)
{
    return (any) {
        .p = (void *) ptr
    };
}

static inline any libcx_any_bool(bool b)
{
    return (any) {
        .b = b
    };
}

static inline any libcx_any_sint(signed long long int s)
{
    return (any) {
        .s = s
    };
}

static inline any libcx_any_uint(unsigned long long int u)
{
    return (any) {
        .u = u
    };
}

static inline any libcx_any_float(double d)
{
    return (any) {
        .d = d
    };
}

static inline any libcx_any_any(any a)
{
    return a;
}

static inline any libcx_any_data(const void *d, size_t s)
{
    void *p = libcx_zalloc(s);
    memcpy(p, d, s);
    return any(p);
}


static inline any libcx_any_default(void)
{
    return (any) {
        .p = NULL,
        .b = false,
        .s = 0,
        .u = 0,
        .d = 0.0
    };
}

static inline void libcx_any_debug(const char *fmt, any a)
{
    if (!strcmp(fmt, "%p"))
        printf(fmt, a.p);
    else if (!strcmp(fmt, "%b"))
        printf("%s", a.b ? "true": "false");
    else if (!strcmp(fmt, "%d"))
        printf("%ld", a.s);
    else if (!strcmp(fmt, "%u"))
        printf("%lu", a.u);
    else if (!strcmp(fmt, "%f"))
        printf("%f", a.d);
    else if (!strcmp(fmt, "%s"))
        printf("%s", a.p);
}

static inline void libcx_any_debug_ln(const char *fmt, any a)
{
    libcx_any_debug(fmt, a);
    printf("\n");
}

#endif
