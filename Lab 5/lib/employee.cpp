#include <cstdio>
#include "employee.h"
#include "terminal.h"
#include "key.h"
#include "input.h"

struct Employee {
    std::string name;
    double salary{};
};

static std::vector<Employee> EMPLOYEES;

void createEmployee() {
    clearScreen();
    disableRawMode();

    setCursorPos(0, 0);
    setColor(YELLOW);
    printf("=== CREATE NEW EMPLOYEE ===\n\n");
    resetColor();

    Employee newEmp;
    newEmp.name   = getValidAlphabeticString("Enter Name: ");
    if (newEmp.name == "") {
        printf("\nOperation cancelled due to invalid name.");
        enableRawMode();
        while (detectKey() != K_BACKSPACE) { /*Busy wait*/ }
        return;
    }

    newEmp.salary = getValidPositiveNumber("Enter Salary: ");
    if (newEmp.salary <= 0) {
        printf("\nOperation cancelled due to invalid salary.");
        enableRawMode();
        while (detectKey() != K_BACKSPACE) { /*Busy wait*/ }
        return;
    }

    EMPLOYEES.push_back(newEmp);

    printf("\nSuccess!");
    enableRawMode();
    while (detectKey() != K_BACKSPACE) { /*Busy wait*/ }
}

void displayEmployees() {
    clearScreen();

    setCursorPos(0, 0);
    setColor(YELLOW);
    printf("=== EMPLOYEE RECORDS ===");
    resetColor();

    setCursorPos(0, 2);
    setColor(WHITE, BLUE);
    printf(" %-20s | %-12s ", "NAME", "SALARY");
    resetColor();

    if (EMPLOYEES.empty()) {
        setCursorPos(0, 4);
        printf("No records found.");
        return;
    }

    int y = 4;
    for (const auto& emp : EMPLOYEES) {
        setCursorPos(0, y++);
        printf(" %-20s | $%-11.2f ", emp.name.c_str(), emp.salary);
    }

    while (detectKey() != K_BACKSPACE) { /*Busy wait*/ }
}