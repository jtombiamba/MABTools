#include <bench.h>


perf_t load (stream_t *s) {
    perf_t ret = {s->size, s->size/16};
    if (s->size >= 128) {
	__asm__ __volatile__(
	    "mfence;"
	    "_loop:"
	    "movaps (%%rbx), %%xmm0;"
	    "movaps 16(%%rbx), %%xmm0;"
	    "movaps 32(%%rbx), %%xmm0;"
	    "movaps 48(%%rbx), %%xmm0;"
	    "movaps 64(%%rbx), %%xmm0;"
	    "movaps 80(%%rbx), %%xmm0;"
	    "movaps 96(%%rbx), %%xmm0;"
	    "movaps 112(%%rbx), %%xmm0;"
	    "add $128, %%rbx;"
	    "sub $128, %%rcx;"
	    "jnz _loop;"
	    "mfence;"
	    :
	    : "b"(s->stream), "c" (s->size)
	    : "%xmm0"
	    );
    }
    return ret;
}
