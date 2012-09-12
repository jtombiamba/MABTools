#ifndef BENCH_H
#define BENCH_H

#include <stdint.h>
#include <libmbench.h>
#include <custom.h>

#define REPS	10

perf_t load (stream_t *stream);
perf_t store (stream_t *stream);
perf_t copy (stream_t *dest, stream_t *src);
perf_t add_bench (stream_t *source);
perf_t add_unroll_lea_bench (stream_t *source);
perf_t crc32_bench (stream_t *source);
perf_t add_unroll_32_bench(stream_t *source);
perf_t add_unroll_64_bench(stream_t *source);
perf_t add_unroll_128_bench(stream_t *source);
perf_t add_unroll_256_bench(stream_t *source);
perf_t add_i_nop_bench (stream_t *source);
perf_t latency_load (stream_t *stream);
perf_t mov_i_reg_bench (stream_t *source);
perf_t mov_i_reg_nop_bench (stream_t *source);
perf_t mov_reg_mem_bench(stream_t *source);
perf_t push_reg_bench(stream_t *source);
perf_t lea_bench(stream_t *source);
perf_t add_reg_mem_bench(stream_t *source);
perf_t mult_bench(stream_t *source);
perf_t div_bench(stream_t *source);
perf_t div_i_bench(stream_t *source);
perf_t and_bench(stream_t *source);
perf_t or_bench(stream_t *source);
perf_t xor_reg_mem_bench(stream_t *source);
perf_t nop_bench(stream_t *source);
perf_t ror_rol_bench(stream_t *source);
perf_t add_latency_bench(stream_t *source);
perf_t add_5_reg_bench(stream_t *source);
perf_t add_unroll_8_bench(stream_t *source);
perf_t add_unroll_1_bench(stream_t *source);
perf_t add_unroll_mov_bench(stream_t *source);
perf_t add_mem_reg_bench(stream_t *source);
perf_t mov_i_unroll_8_bench(stream_t *source);
perf_t mov_latency_bench(stream_t *source);
perf_t mov_latency_1reg_bench(stream_t *source);
perf_t jump_bench(stream_t *source);
perf_t jump_reverse_bench(stream_t *source);
perf_t addps_bench(stream_t *source);
perf_t movd_bench(stream_t *source);
perf_t addpd_bench(stream_t *source);
perf_t pmulld_bench(stream_t *source);
perf_t mfence_bench(stream_t *source);
perf_t clflush_bench(stream_t *source);
perf_t vbroadcastsd_bench(stream_t *source);
perf_t vaddpd_bench(stream_t *source);
perf_t output_james(stream_t *source);

#endif // BENCH_H
