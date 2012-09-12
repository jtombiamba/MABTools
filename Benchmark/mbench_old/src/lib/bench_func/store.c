#include <bench.h>


perf_t store (stream_t *s) {
    perf_t ret = {0, 0};
    if (s->size >= 128) {
	__asm__ __volatile__(
	    "movlpd (%%rbx), %%xmm0;"
	    "mfence;"
	    "_loop:"
	    "movaps %%xmm0, (%%rbx);"
	    "movaps %%xmm0, 16(%%rbx);"
	    "movaps %%xmm0, 32(%%rbx);"
	    "movaps %%xmm0, 48(%%rbx);"
	    "movaps %%xmm0, 64(%%rbx);"
	    "movaps %%xmm0, 80(%%rbx);"
	    "movaps %%xmm0, 96(%%rbx);"
	    "movaps %%xmm0, 112(%%rbx);"
	    "add $128, %%rbx;"
	    "sub $128, %%rcx;"
	    "jnz _loop;"
	    "mfence;"
	    :
	    : "b"(s->stream), "c" (s->size)
	    : "%xmm0"
	    );
	ret.instructions = s->size / 16;
	ret.bytes = s->size;
    }
    else {
	ret.instructions = 0;
	ret.bytes = 0;
    }
    
    return ret;
}



