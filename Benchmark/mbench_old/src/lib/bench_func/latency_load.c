#include <bench.h>


perf_t latency_load (stream_t *stream) {
    perf_t ret = {0, 0};
    int cpt = 0;
    char *end;
    if (stream->size >= 128) {
	__asm__ __volatile__(
	    "mfence;"
	    "_loop:"
	    
	    "mov 112(%%rbx,%%rcx,8), %%rbx;"
	    "mov 96(%%rbx,%%rcx,8), %%rbx;"
	    "mov 80(%%rbx,%%rcx,8), %%rbx;"
	    "mov 64(%%rbx,%%rcx,8), %%rbx;"
	    "mov 48(%%rbx,%%rcx,8), %%rbx;"
	    "mov 32(%%rbx,%%rcx,8), %%rbx;"
	    "mov 16(%%rbx,%%rcx,8), %%rbx;"
	    "mov (%%rbx,%%rcx,8), %%rbx;"
	    
	    "add $8, %%rcx;"
	    "sub $128, %%rax;"
	    "jnz _loop;"
	    "mfence;"
	    : "=c" (cpt)
	    : "a" (stream->size), "b" (stream->stream), "c" (0)
	    :
	    );
	ret.instructions = cpt;
	ret.bytes = cpt * 8;
    }
    else {
	ret.instructions = 0;
	ret.bytes = 0;
    }
    return ret;
}
