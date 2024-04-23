#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define HANDLE(condition) \
		if (condition) { \
			printf("%s:%d: %s\n", __func__, __LINE__, \
					strerror(errno)); \
			return 1; \
		}

int main(int argc, char **argv) {
	assert(argc == 3);
	FILE *file = fopen(argv[1], "rb");
	HANDLE(file == NULL)
	HANDLE(fseek(file, 0, SEEK_END) == -1)
	long size = ftell(file);
	HANDLE(size == -1)
	HANDLE(fseek(file, 0, SEEK_SET) == -1)
	void *data = malloc(size);
	HANDLE(data == NULL)
	// char data[size]; 
	HANDLE(fread(data, 1, size, file) < size)
	HANDLE(fclose(file) == EOF)
	HANDLE((file = fopen(argv[2], "wb")) == NULL)
	HANDLE(fwrite(data, 1, size, file) < size)
	HANDLE(fclose(file) == EOF)
	free(data);
	return 0;
}
