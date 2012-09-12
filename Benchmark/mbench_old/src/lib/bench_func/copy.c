#include <bench.h>


perf_t copy (stream_t *dest, stream_t *src) {
    perf_t ret = {0, 0};
    int cpt = 0;

    if (dest->size >= 128) {
	__asm__ __volatile__(
	    "mfence;"
	    "_loop:"
	    "movaps (%%rbx), %%xmm0;"
	    "movaps %%xmm0, (%%rdx);"

	    "movaps 16(%%rbx), %%xmm0;"
	    "movaps %%xmm0, 16(%%rdx);"

	    "movaps 32(%%rbx), %%xmm0;"
	    "movaps %%xmm0, 32(%%rdx);"

	    "movaps 48(%%rbx), %%xmm0;"
	    "movaps %%xmm0, 48(%%rdx);"

	    "movaps 64(%%rbx), %%xmm0;"
	    "movaps %%xmm0, 64(%%rdx);"

	    "movaps 80(%%rbx), %%xmm0;"
	    "movaps %%xmm0, 80(%%rdx);"

	    "movaps 96(%%rbx), %%xmm0;"
	    "movaps %%xmm0, 96(%%rdx);"

	    "movaps 112(%%rbx), %%xmm0;"
	    "movaps %%xmm0, 112(%%rdx);"

	    "add $128, %%rbx;"
	    "add $128, %%rdx;"
	    "sub $128, %%rcx;"
	    "jnz _loop;"
	    "mfence;"
	    :
	    : "b" (src->stream), "d" (dest->stream), "c" (dest->size)
	    : "%xmm0"
	    );
	ret.instructions = 2*src->size / 16;
	ret.bytes = 2*src->size;
    }
    else {
	ret.instructions = 0;
	ret.bytes = 0;
    }
    return ret;
}
