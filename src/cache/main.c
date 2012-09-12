#include"lib/mylib.h"
#include<getopt.h>

int main(int argc, char **argv){
	int i ;
	int j ;
	int k ;

	while((i=getopt(argc, argv, "o:s:"))!=EOF){
		switch(i){
			case 'o': j = atoi(optarg);
			break;
			case 's': k= atoi(optarg);
			break;
			default: j=-1;
			break;
		}
	}

	perf_t perf;
	char* value;
	value =(char*) malloc(100*sizeof(char));
	stream_t *streaming;
	streaming = malloc(sizeof(stream_t));
	if(j==-1)
	streaming->size = 500*1024;
	else streaming->size = j*k;
	//perf = add_bench(streaming);
	printf("fight\n");
	__asm__ __volatile__ (

											"xor %%rcx,%%rcx;\n"
											"rdpmc;\n"
										//	"mov %%rax,(%%rbx);\n"
											"shl $32, %%rdx;\n"	
											"mov $1,%%rbx;\n"
											"add %%rax, %%rdx;\n"
											"rdpmc;\n"
											: "=d" (j), "=c" (k), "=a" (i)
											: "b" (value) 
											: 
									);
 
	//printf("clock_=%lu et latency=%.2f \n",perf.clock_cycles,(double)perf.clock_cycles/perf.instructions);						
	printf("%d %d %d \n", i, j, k);
	return 0;

}
