#include <stdlib.h>
#include <stdio.h>

#include "unlzma_tiny.h"

int main(int argc, char **argv) {
	FILE *in_f, *out_f;
	uint8_t *in_buff, *out_buff;
	int in_size, out_size;

	if (argc != 4) {
		printf("Usage %s src output output_buffer_size\n", argv[0]);
		return -1;
	}

	in_f = fopen(argv[1], "r");
	fseek(in_f, 0L, SEEK_END);
	in_size = ftell(in_f);
	rewind(in_f);

	in_buff = malloc(in_size);
	if (fread(in_buff, 1, in_size, in_f) != (size_t)in_size) {
		printf("failed to read\n");
	}

	out_size = atoi(argv[3]);
	out_buff = malloc(out_size);

	out_size = lzma_inflate(in_buff, in_size, out_buff, out_size);
	if (out_size < 0) {
		printf("failed to inflate\n");
		fclose(in_f);
		free(in_buff);
		free(out_buff);
		return -1;
	}

	out_f = fopen(argv[2], "w");
	if (fwrite(out_buff, 1, out_size, out_f) != (size_t)out_size) {
		printf("failed to write\n");
	}

	fclose(out_f);
	fclose(in_f);

	free(in_buff);
	free(out_buff);
	return 0;
}
