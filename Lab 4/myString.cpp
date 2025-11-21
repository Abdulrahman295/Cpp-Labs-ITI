#include "myString.h"

int string_length(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int string_compare(const char* str1, const char* str2) {
    while (*str1 != '\0' && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    if (*str1 > *str2) {
        return 1; // str1 is greater than str2
    }

    if (*str1 < *str2) {
        return -1; // str1 is less than str2
    }

    return 0; // str1 is equal to str2
}

void to_lower(char* str) {
    const int capital_offset = 'a' - 'A';
    int index = 0;

    while (str[index] != '\0') {
        if (str[index] >= 'A' && str[index] <= 'Z') {
            str[index] += capital_offset;
        }
        index++;
    }
}

void to_upper(char* str) {
    const int capital_offset = 'a' - 'A';
    int index = 0;

    while (str[index] != '\0') {
        if (str[index] >= 'a' && str[index] <= 'z') {
            str[index] -= capital_offset;
        }
        index++;
    }
}

bool string_copy(const char* source, char* destination, int destination_capacity) {
    int source_length = string_length(source);

    if (source_length >= destination_capacity) {
        return false;
    }

    for (int i = 0; i < source_length; i++) {
        destination[i] = source[i];
    }

    destination[source_length] = '\0';
    return true;
}

bool string_append(const char* source, char* destination, int destination_capacity) {
    int dest_length = string_length(destination);
    int source_length = string_length(source);

    if (dest_length + source_length >= destination_capacity) {
        return false;
    }

    int index = 0;
    while (source[index] != '\0') {
        destination[dest_length + index] = source[index];
        index++;
    }

    destination[dest_length + index] = '\0';
    return true;
}