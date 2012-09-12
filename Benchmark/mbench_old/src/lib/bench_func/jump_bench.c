#include<bench.h>


perf_t jump_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop:"
												"jmp 1f;"
												"1:"
												"jmp 2f;"
												"2:"
												"jmp 3f;"
												"3:"
												"jmp 4f;"
												"4:"
												"jmp 5f;"
												"5:"
												"jmp 6f;"
												"6:"
												"jmp 7f;"
												"7:"
												"jmp 8f;"
												"8:"
												"jmp 9f;"
												"9:"
												"jmp 10f;"
												"10:"
												"jmp 11f;"
												"11:"
												"jmp 12f;"
												"12:"
												"jmp 13f;"
												"13:"
												"jmp 14f;"
												"14:"
												"jmp 15f;"
												"15:"
												"jmp 16f;"
												"16:"
												"jmp 17f;"
												"17:"
												"jmp 18f;"
												"18:"
												"jmp 19f;"
												"19:"
												"jmp 20f;"
												"20:"
												"jmp 21f;"
												"21:"
												"jmp 22f;"
												"22:"
												"jmp 23f;"
												"23:"
												"jmp 24f;"
												"24:"
												"jmp 25f;"
												"25:"
												"jmp 26f;"
												"26:"
												"jmp 27f;"
												"27:"
												"jmp 28f;"
												"28:"
												"jmp 29f;"
												"29:"
												"jmp 30f;"
												"30:"
												"jmp 31f;"
												"31:"
												"jmp 32f;"
												"32:"
											/*	"jmp 33f;"
												"33:"
												"jmp 34f;"
												"34:"
												"jmp 35f;"
												"35:"
												"jmp 36f;"
												"36:"
												"jmp 37f;"
												"37:"
												"jmp 38f;"
												"38:"
												"jmp 39f;"
												"39:"
												"jmp 40f;"
												"40:"
												"jmp 41f;"
												"41:"
												"jmp 42f;"
												"42:"
												"jmp 43f;"
												"43:"
												"jmp 44f;"
												"44:"
												"jmp 45f;"
												"45:"
												"jmp 46f;"
												"46:"
												"jmp 47f;"
												"47:"
												"jmp 48f;"
												"48:"
												"jmp 49f;"
												"49:"
												"jmp 50f;"
												"50:"
												"jmp 51f;"
												"51:"
												"jmp 52f;"
												"52:"
												"jmp 53f;"
												"53:"
												"jmp 54f;"
												"54:"
												"jmp 55f;"
												"55:"
												"jmp 56f;"
												"56:"
												"jmp 57f;"
												"57:"
												"jmp 58f;"
												"58:"
												"jmp 59f;"
												"59:"
												"jmp 60f;"
												"60:"
												"jmp 61f;"
												"61:"
												"jmp 62f;"
												"62:"
												"jmp 63f;"
												"63:"
												"jmp 64f;"
												"64:"*/
	      								"sub $32, %%rcx;"
												"jnz _loop;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: 
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t jump_reverse_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loopk:"
												"jmp 16f;"
												"2:"
												"jmp 17f;"
												"3:"
												"jmp 2b;"
												"4:"
												"jmp 3b;"
												"5:"
												"jmp 4b;"
												"6:"
												"jmp 5b;"
												"7:"
												"jmp 6b;"
												"8:"
												"jmp 7b;"
												"9:"
												"jmp 8b;"
												"10:"
												"jmp 9b;"
												"11:"
												"jmp 10b;"
												"12:"
												"jmp 11b;"
												"13:"
												"jmp 12b;"
												"14:"
												"jmp 13b;"
												"15:"
												"jmp 14b;"
												"16:"
												"jmp 15b;"
												"17:"
												"sub $16, %%rcx;"
												"jnz _loopk;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: 
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}


