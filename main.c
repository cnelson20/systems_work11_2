#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generate_random(void *ptr, size_t bytes);
void print_ints(unsigned int *array, size_t length);
int main();

int main() {
	unsigned int randoms[10];
	
	printf("Generating random numbers\n");
	generate_random(randoms,sizeof(unsigned int) * 10);
	
	print_ints(randoms,10);
	
	
	FILE *fp;
	printf("\nWriting to file\n\n");
	fp = fopen("hold_random.bin","w");
	fwrite(randoms,sizeof(unsigned int),10,fp);
	fclose(fp);
	
	printf("Reading from file\n\n");
	fp = fopen("hold_random.bin","r");
	unsigned int *buffer = malloc(sizeof(unsigned int) * 10);
	fread(buffer,sizeof(unsigned int),10,fp);
	
	printf("Values read from file:\n");
	print_ints(buffer,10);
	free(buffer);
	
	return 0;
}

void print_ints(unsigned int *array, size_t length) {
	unsigned int i;
	printf("{");
	for (i = 0; i < length; i++) {
		if (i != 0) {printf(", ");}
		printf("%u",array[i]);
	}
	printf("}\n");
}
void generate_random(void *ptr, size_t bytes) {
	FILE *fp;
	fp = fopen("/dev/urandom","r");
	fread(ptr,1,bytes,fp);
	fclose(fp);
}