#include <algorithm>
#include <iostream>
#include <string>

static bool isValidAlphabeticString(const std::string& str) {
    if (str.empty()) return false;

    return std::all_of(str.begin(), str.end(), [](char c) {
               return std::isalpha(c) || std::isspace(c);
           });
}

std::string getValidAlphabeticString(const char* prompt) {
    std::string input;
    bool validString = false;

    while (!validString) {
        printf("%s", prompt);
        bool successRead = std::getline(std::cin >> std::ws, input).good();

        if (successRead && isValidAlphabeticString(input)) {
            validString = true;
        } else {
            std::cin.clear();
            printf("Invalid input. Use letters and spaces only.\n");
        }
    }

    return input;
}


static bool isValidPositiveNumber(const std::string& str) {
    if (str.empty()) return false;

    if (std::any_of(str.begin(), str.end(), [](char c) { return std::iscntrl(c); })) {
        return false;
    }

    try {
        size_t pos;
        double value = std::stod(str, &pos);
        return pos == str.length() && value >= 0;
    } catch (...){
        return false;
    }
}

double getValidPositiveNumber(const char* prompt) {
    std::string input;
    bool validNumber = false;

    while (!validNumber) {
        printf("%s", prompt);
        bool successRead = std::getline(std::cin >> std::ws, input).good();

        if (successRead && isValidPositiveNumber(input)) {
            validNumber = true;
        } else {
            std::cin.clear();
            printf("Invalid input. Enter a positive number.\n");
        }
    }

    return std::stod(input);
}
