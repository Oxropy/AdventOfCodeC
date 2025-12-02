#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file_reader_helper.c"

static void part1(const char* filename);
static void part2(const char* filename);

bool is_part_one = false;

int main() {
    const char* filename = "../../resources/year2025/Day02.txt";
    part1(filename);
    part2(filename);
    return 0;
}

bool is_all_same_pattern(char sId[10], const size_t size) {
    if (size == 1) return false;

    for (int j = 1; j < size; j++) {
        if (sId[0] != sId[j]) return false;
    }
    return true;
}

bool is_half_pattern(char sId[10], const size_t size) {
    const int split = size / 2;
    for (int j = 0; j < split; j++) {
        if (sId[j] != sId[split + j]) {
            return false;
        }
    }
    return true;
}

bool is_third_pattern(char sId[10], const size_t size) {
    const int split = size / 3;
    for (int j = 0; j < split; j++) {
        if (sId[j] != sId[split + j] || sId[j] != sId[split * 2 + j]) {
            return false;
        }
    }
    return true;
}

bool is_fourth_pattern(char sId[10], const size_t size) {
    const int split = size / 4;
    for (int j = 0; j < split; j++) {
        if (sId[j] != sId[split + j] || sId[j] != sId[split * 2 + j] || sId[j] != sId[split * 3 + j]) {
            return false;
        }
    }
    return true;
}

bool is_fifth_pattern(char sId[10], const size_t size) {
    const int split = size / 4;
    for (int j = 0; j < split; j++) {
        if (sId[j] != sId[split + j] || sId[j] != sId[split * 2 + j] || sId[j] != sId[split * 3 + j] || sId[j] != sId[split * 4 + j]) {
            return false;
        }
    }
    return true;
}

bool is_id_invalid(const long id) {
    char sId[10];
    sprintf(sId, "%ld", id);
    const size_t size = strlen(sId);
    if (is_part_one) {
        if (size % 2 != 0) return false;
        if (is_half_pattern(sId, size)) return true;
        return false;
    }

    if (is_all_same_pattern(sId, size)) return true;
    if (size % 2 == 0 && is_half_pattern(sId, size)) return true;
    if (size % 3 == 0 && is_third_pattern(sId, size)) return true;
    if (size % 4 == 0 && is_fourth_pattern(sId, size)) return true;
    if (size % 5 == 0 && is_fifth_pattern(sId, size)) return true;

    return false;
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
    is_part_one = true;
    for_each_line(filename, process_line1, &sum);
    printf("Part 1: %ld\n", sum);
}

static void part2(const char* filename) {
    long sum = 0;
    is_part_one = false;
    for_each_line(filename, process_line1, &sum);
    printf("Part 2: %ld\n", sum);
}