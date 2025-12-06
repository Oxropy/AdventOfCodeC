#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../file_reader_helper.c"

static void part1(const char* filename);
static void part2(const char* filename);

typedef struct {
    uint64_t from;
    uint64_t to;
} Range;

typedef struct {
    uint32_t index;
    Range ranges[185];
} Range_Indexed;

typedef struct {
    uint32_t index;
    uint64_t ids[1000];
} Id_Indexed;

int main() {
    const char* filename = "../../resources/year2025/Day05.txt";
    part1(filename);
    // part2(filename);
    return 0;
}

void process_range(const char* line, void* context) {
    Range_Indexed* ranges = context;
    char* from = strtok(line, "-");
    ranges->ranges[ranges->index].from = atol(from);
    char* to = strtok(NULL, "-");
    ranges->ranges[ranges->index].to = atol(to);
    ranges->index++;
}

void process_id(const char* line, void* context) {
    Id_Indexed* ids = context;
    ids->ids[ids->index] = atol(line);
    ids->index++;
}

static void part1(const char* filename) {
    Range_Indexed ranges = {0, {0}};
    Id_Indexed ids = {0, {0}};
    for_each_line_with_split(filename, process_range, &ranges, process_id, &ids);

    uint32_t fresh = 0;
    for (uint32_t i = 0; i < ids.index; i++) {
        for (uint32_t j = 0; j < ranges.index; j++) {
            if (ids.ids[i] >= ranges.ranges[j].from && ids.ids[i] <= ranges.ranges[j].to) {
                fresh++;
                break;
            }
        }
    }

    printf("Part 1: %d\n", fresh);
}