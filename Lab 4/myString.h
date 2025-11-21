#pragma once

int string_length(const char* str);

int string_compare(const char* str1, const char* str2);

void to_lower(char* str);

void to_upper(char* str);

bool string_copy(const char* source, char* destination, int destination_capacity);

bool string_append(const char* source, char* destination, int destination_capacity);