#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../file_reader_helper.c"

static void part1(const char* filename);
static void part2(const char* filename);

int main() {
    const char* filename = "../../resources/year2025/Day04.txt";
    part1(filename);
    // part2(filename);
    return 0;
}

static uint32_t is_set(const uint32_t rows, const uint32_t cols, char array[rows][cols], int32_t row, int32_t col, const uint8_t set_value) {
    if (row < 0 || col < 0) return 0;
    if (row >= rows || col >= cols) return 0;
    return array[row][col] == set_value ? 1 : 0;
}


static void part1(const char* filename) {
    const uint32_t rows = 139;
    const uint32_t cols = 139;
    char array[rows][cols];
    int32_t real_rows;
    int32_t real_cols;
    const uint8_t parse_result = parse_file_to_variable_length_array(filename, rows, cols, array, &real_rows, &real_cols);
    if (parse_result != 0) {
        return;
    }

    uint32_t count = 0;

    for (uint8_t row = 0; row < real_rows; row++) {
        for (uint8_t col = 0; col < real_cols; col++) {
            if (array[row][col] == '.') continue;

            const uint32_t sum = is_set(rows, cols, array, row - 1, col - 1, '@')
                                 + is_set(rows, cols, array, row - 1, col, '@')
                                 + is_set(rows, cols, array, row - 1, col + 1, '@')
                                 + is_set(rows, cols, array, row, col - 1, '@')
                                 + is_set(rows, cols, array, row, col + 1, '@')
                                 + is_set(rows, cols, array, row + 1, col - 1, '@')
                                 + is_set(rows, cols, array, row + 1, col, '@')
                                 + is_set(rows, cols, array, row + 1, col + 1, '@');


            if (sum < 4) {
                count++;
            }
        }
    }

    printf("Part 1: %d\n", count);
}

