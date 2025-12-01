#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file_reader_helper.c"

typedef struct {
    int nullCount;
    int currentPosition;
}State;

long getNumber(const char* line);
void part1(const char* filename);
void part2(const char* filename);

int main() {
    const char* filename = "../../resources/year2025/Day01.txt";
    part1(filename);
    // part2(filename);
    return 0;
}

void processLine(const char* line, void* context) {
    State* state = context;
    const size_t size = strlen(line);
    if (size == 0) {
        perror("Empty line");
        return;
    }

    const int number = (int)strtol(line + sizeof(char), NULL, 10);
    switch (line[0]) {
        case 'L':
            const int difference = (state->currentPosition - number) % 100;
            if (difference < 0) {
                state->currentPosition = 100 + difference;
            } else {
                state->currentPosition = difference;
            }
            break;
        case 'R':
            state->currentPosition = (state->currentPosition + number) % 100;
            break;
        default: perror("unknown direction"); break;
    }

    if (state->currentPosition == 0) {
        state->nullCount++;
    }

    printf(" current position: %d\n", state->currentPosition);
}

void part1(const char* filename) {
    State state = {0, 50};
    for_each_line(filename, processLine, &state);
    printf("Part 1: %d\n", state.nullCount);
}