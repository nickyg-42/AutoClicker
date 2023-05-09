#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "AutoClicker.h"

void printOptions();

int main()
{

    AllocConsole();
    freopen("CON", "w", stdout);
    int choice;

    while(choice != 5) {
        printOptions();

        std::cin >> choice;

        switch(choice) {
            case 1:
                printf("Your");
            case 2:

            case 3:

            case 4:
            case 5:
            default:
                printf("Invalid option\n");
                break;
        }
    }

    return 0;
}

void printOptions() {
    printf("====== C++ AutoClicker ======\n");
    printf("1) Change Keybind\n");
    printf("2) Change Interval\n");
    printf("3) Start\n");
    printf("4) Stop\n");
    printf("5) Quit\n");
    printf("> ");
}
