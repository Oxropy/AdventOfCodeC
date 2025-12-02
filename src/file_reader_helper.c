#define GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*LineHandler)(const char* line, void* context);

void for_each_line(const char* filename, const LineHandler handler, void* context) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return;
    }

    char* line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        const size_t size = strlen(line);
        if (size > 0 && line[size - 1] == '\n') {
            line[size - 1] = '\0';
        }

        handler(line, context);
    }

    free(line);
    fclose(file);
}