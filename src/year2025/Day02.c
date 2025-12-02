#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file_reader_helper.c"

static void part1(const char* filename);
static void part2(const char* filename);

int main() {
    const char* filename = "../../resources/year2025/Day02.txt";
    part1(filename);
    // part2(filename);
    return 0;
}

bool is_id_invalid(const long id) {
    char sId[10];
    sprintf(sId, "%ld", id);
    if (strlen(sId) % 2 != 0) return false;

    const size_t size = strlen(sId);
    const int half = size / 2;
    for (int j = 0; j < half; j++) {
        if (sId[j] != sId[half + j]) {
            return false;
        }
    }
    return true;
}

long get_invalid_id_sum(char* range) {
    char* savePtr;
    const char* first = strtok_r(range, "-", &savePtr);
    const long from_id = atol(first);
    const char* second = strtok_r(NULL, "-", &savePtr);
    const long till_id = atol(second);

    long sum = 0;
    for (long i = from_id; i <= till_id; i++) {
        if (is_id_invalid(i)) {
            sum += i;
        }
    }

    return sum;
}

void process_line1(const char* line, void* context) {
    long* sum = context;
    char* savePtr;
    char* range = strtok_r(line, ",", &savePtr);
    while (range != NULL) {
        *sum += get_invalid_id_sum(range);
        range = strtok_r(NULL, ",", &savePtr);
    }
}

static void part1(const char* filename) {
    long sum = 0;
    for_each_line(filename, process_line1, &sum);
    printf("Part 1: %ld\n", sum);
}