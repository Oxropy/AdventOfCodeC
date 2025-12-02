#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file_reader_helper.c"

typedef struct {
    int nullCount;
    int currentPosition;
}State;

void part1(const char* filename);
void part2(const char* filename);

int main() {
    const char* filename = "../../resources/year2025/Day01.txt";
    part1(filename);
    part2(filename);
    return 0;
}

void process_line1(const char* line, void* context) {
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
}

void process_line2(const char* line, void* context) {
    State* state = context;
    const size_t size = strlen(line);
    if (size == 0) {
        perror("Empty line");
        return;
    }

    printf("line: %s null count: %d current position: %d\n", line, state->nullCount, state->currentPosition);
    const int number = (int)strtol(line + sizeof(char), NULL, 10);
    int position = state->currentPosition;
    switch (line[0]) {
        case 'L':
            position -= number;
            break;
        case 'R':
            position += number;
            break;
        default: perror("unknown direction"); break;
    }

    int quotient = abs(position / 100);
    int rest = position % 100;

    if (rest < 0) {
        rest += 100;
        if (state->currentPosition != 0) {
            quotient++;
        }
    }

    if (rest == 0) {
        quotient++;
    }

    printf("current null: %d null change: %d position: %d\n", state->nullCount, quotient, rest);

    state->currentPosition = rest;
    state->nullCount += quotient;
}

void part1(const char* filename) {
    State state = {0, 50};
    for_each_line(filename, process_line1, &state);
    printf("Part 1: %d\n", state.nullCount);
}

void part2(const char* filename) {
    State state = {0, 50};
    for_each_line(filename, process_line2, &state);
    printf("Part 2: %d\n", state.nullCount);
}