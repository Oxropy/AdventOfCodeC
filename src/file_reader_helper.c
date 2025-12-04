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

int parse_file_to_variable_length_array(const char* filename, const int max_rows, const int max_cols,
                           char grid[max_rows][max_cols], int* actual_rows, int* actual_cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return -1;
    }

    char buffer[1024];
    *actual_rows = 0;
    *actual_cols = 0;

    while (fgets(buffer, sizeof(buffer), file) && *actual_rows < max_rows) {
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        if (*actual_cols == 0) *actual_cols = len;

        for (int col = 0; col < len && col < max_cols; col++) {
            grid[*actual_rows][col] = buffer[col];
        }
        (*actual_rows)++;
    }

    fclose(file);
    return 0;
}