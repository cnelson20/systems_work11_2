#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void generate_random(void *ptr, size_t bytes);
void print_ints(unsigned int *array, size_t length);
int main();


int main() {
	unsigned int randoms[10];
	
	printf("Generating random numbers\n");
	generate_random(randoms,sizeof(unsigned int) * 10);
	
	print_ints(randoms,10);
	
	
	int fp;
	printf("\nWriting to file\n\n");
	fp = open("hold_random.bin",O_WRONLY,0700);
	if (errno != 0) {
		printf("Cannot create/open file.\n");
		return 0;
	}
	if (-1 == write(fp,randoms,sizeof(unsigned int)*10)) {
		printf("Cannot write to file!\n");
		return 0;
	}
        //close(fp);
	
	printf("Reading from file\n\n");
	fp = open("hold_random.bin",O_RDONLY);
	if (errno != 0) {
		printf("Cannot open file.\n");
		return 0;
	}
	unsigned int *buffer = malloc(sizeof(unsigned int) * 10);
	if (-1 == read(fp,buffer,sizeof(unsigned int)*10)) {
		printf("Cannot read from file!\n");
		return 0;
	}
	//close(fp);
	
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
	int fp;
	fp = open("/dev/urandom",O_RDONLY);
	read(fp,ptr,bytes);
	//close(fp);
}
