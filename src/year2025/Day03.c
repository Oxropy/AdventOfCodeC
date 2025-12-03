#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file_reader_helper.c"

static void part1(const char* filename);
static void part2(const char* filename);

int main() {
    const char* filename = "../../resources/year2025/Day03.txt";
    part1(filename);
    // part2(filename);
    return 0;
}

int get_highest_value_index(const char* line, const int start_index, const int end_index) {
    int highest_value = -1;
    int highest_index = start_index;
    for (int i = start_index; i < end_index; i++) {
        const int value = line[i] - '0';
        if (value > highest_value) {
            highest_value = value;
            highest_index = i;

            if (highest_value == 9) {
                return highest_index;
            }
        }
    }

    return highest_index;
}

void process_line1(const char* line, void* context) {
    long* sum = context;
    char value[2];
    const size_t size = strlen(line);
    const int highest_value_index = get_highest_value_index(line, 0, size);
    if (highest_value_index == size - 1) {
        const int first_number = get_highest_value_index(line, 0, size - 1);
        value[0] = line[first_number];
        value[1] = line[highest_value_index];
    } else {
        const int second_number = get_highest_value_index(line, highest_value_index + 1, size);
        value[0] = line[highest_value_index];
        value[1] = line[second_number];
    }

    *sum += atoi(value);
}

static void part1(const char* filename) {
    long sum = 0;
    for_each_line(filename, process_line1, &sum);
    printf("Part 1: %ld\n", sum);
}