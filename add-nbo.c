#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

uint32_t add_nbo(char* filename){
	FILE *bin_file;
	uint32_t buf;

	if ((bin_file = fopen(filename, "rb")) == NULL){
		fprintf(stderr, "return null %s", strerror(errno));
		exit(1);
	}

	size_t read_bin = fread(&buf, 1, sizeof(buf), bin_file);
	if (read_bin != sizeof(buf)){
		fprintf(stderr, "thousand bin read error : %lu\n", read_bin);
		exit(1);
	}

	buf = ntohl(buf);
	fclose(bin_file);
	return (buf);
}

int main(int argc, char *argv[]){
	if (argc <= 2){
		printf("syntax : add-nbo <file1> <file2>\n");
		printf("sample : add-nbo a.bin b.bin\n");
		exit(1);
	}

	uint32_t bin[2] = {add_nbo(argv[1]), add_nbo(argv[2])}; 
	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", bin[0], bin[0], bin[1], bin[1], bin[0] + bin[1], bin[0] + bin[1]);

	return 0;
}
