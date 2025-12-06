#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include "../file_reader_helper.c"

static void part1(const char* filename);
static void part2(const char* filename);

#define COLUMNS 1000
#define VALUE_ROWS 4

typedef struct {
    uint32_t index;
    uint64_t values[VALUE_ROWS];
    uint8_t operator;
} Vertical_Values;

typedef struct {
    uint32_t line;
    Vertical_Values values[COLUMNS];
} Input_Values;

int main() {
    const char* filename = "../../resources/year2025/Day06.txt";
    part1(filename);
    // part2(filename);
    return 0;
}

void process_line1(const char* line, void* context) {
    Input_Values* values = context;
    const char* ptr = line;
    uint32_t count = 0;

    while (*ptr && count < COLUMNS) {
        while (isspace(*ptr)) ptr++;

        if (!*ptr) break;

        if (*ptr == '+' || *ptr == '*') {
            values->values[count].operator = *ptr;
            ptr++;
            count++;
            continue;
        }

        if (!isdigit(*ptr)) break;

        uint64_t num = 0;
        while (isdigit(*ptr)) {
            num = num * 10 + (*ptr - '0');
            ptr++;
        }

        values->values[count].values[values->line] = num;
        count++;
    }

    values->line++;
}

static void part1(const char* filename) {
    Input_Values values = {0, {0}};
    for_each_line(filename, process_line1, &values);

    uint64_t result = 0;
    for (int i = 0; i < COLUMNS; i++) {
        uint64_t sum = values.values[i].values[0];
        for (int j = 1; j < VALUE_ROWS; j++) {
            switch (values.values[i].operator) {
                case '+': sum += values.values[i].values[j]; break;
                case '*': sum *= values.values[i].values[j]; break;
                default: perror("unknown operator");
            }
        }
        result += sum;
    }

    printf("Part 1: %ld\n", result);
}