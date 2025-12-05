#include <algorithm>
#include <iostream>
#include <string>

static bool isValidAlphabeticString(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c) && !std::isspace(c)) {
            return false;
        }
    }
    return str.length() > 2;
}

std::string getValidAlphabeticString(const char* prompt) {
    std::string input = "";

    printf("%s", prompt);
    bool successRead = std::getline(std::cin >> std::ws, input).good();

    if (successRead && isValidAlphabeticString(input)) {
        return input;
    }

    std::cin.clear();
    printf("Invalid input. Use letters and spaces only.\n");
    return "";
}


static bool isValidPositiveNumber(const std::string& str) {
    if (str.empty()) return false;

    if (std::any_of(str.begin(), str.end(), [](char c) { return std::iscntrl(c); })) {
        return false;
    }

    try {
        size_t pos;
        double value = std::stod(str, &pos);
        return pos == str.length() && value > 0;
    } catch (...){
        return false;
    }
}


double getValidPositiveNumber(const char* prompt) {
    std::string input = "";

    printf("%s", prompt);
    bool successRead = std::getline(std::cin >> std::ws, input).good();

    if (successRead && isValidPositiveNumber(input)) {
        return std::stod(input);
    }

    std::cin.clear();
    printf("Invalid input. Enter a positive number.\n");
    return 0;
}