#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <thread>
#include <atomic>
#include "AutoClicker.h"

std::atomic<bool> running(true);

void clear() {
    std::cout << "\033[2J\033[1;1H";
}

void printOptions(HANDLE console) {
    SetConsoleTextAttribute(console, 15);
    std::cout << "======";
    SetConsoleTextAttribute(console, 11);
    std::cout << " C++ AutoClicker ";
    SetConsoleTextAttribute(console, 15);
    std::cout << "======" << std::endl;
    SetConsoleTextAttribute(console, 3);
    std::cout << "1";
    SetConsoleTextAttribute(console, 7);
    std::cout << ") Change Keybind" << std::endl;
    SetConsoleTextAttribute(console, 3);
    std::cout << "2";
    SetConsoleTextAttribute(console, 7);
    std::cout << ") Change Interval" << std::endl;
    SetConsoleTextAttribute(console, 3);
    std::cout << "3";
    SetConsoleTextAttribute(console, 7);
    std::cout << ") Start Program" << std::endl;
    SetConsoleTextAttribute(console, 3);
    std::cout << "4";
    SetConsoleTextAttribute(console, 7);
    std::cout << ") Quit" << std::endl;
    SetConsoleTextAttribute(console, 3);
    std::cout << "5";
    SetConsoleTextAttribute(console, 7);
    std::cout << ") Reset Defaults" << std::endl;
    SetConsoleTextAttribute(console, 11);
    std::cout << "> ";
    SetConsoleTextAttribute(console, 7);
}

void changeKeybind(AutoClicker* ac, HANDLE console) {
    clear();
    char newKeybind;

    std::cout << "Current keybind: ";
    SetConsoleTextAttribute(console, 3);
    std::cout << ac->getKeybind() << std::endl;
    SetConsoleTextAttribute(console, 7);
    std::cout << "Enter new Keybind (or q to cancel)" << std::endl;
    SetConsoleTextAttribute(console, 11);
    std::cout << "> ";
    SetConsoleTextAttribute(console, 7);

    std::cin >> newKeybind;
    // VALIDATE

    if (newKeybind != 'q' && newKeybind != 'Q') {
        ac->setKeybind(newKeybind);
    }

    clear();
    return;
}

void changeInterval(AutoClicker* ac, HANDLE console) {
    clear();
    double newInterval;

    std::cout << "Current interval: ";
    SetConsoleTextAttribute(console, 3);
    std::cout << ac->getInterval() << std::endl;
    SetConsoleTextAttribute(console, 7);
    std::cout << "Enter your new interval (or -1 to cancel)" << std::endl;
    SetConsoleTextAttribute(console, 11);
    std::cout << "> ";
    SetConsoleTextAttribute(console, 7);

    std::cin >> newInterval;
    // VALIDATE

    if (newInterval != -1) {
        ac->setInterval(newInterval);
    }

    clear();
    return;
}

void quitListen(AutoClicker* ac) {
    while(running) {
        if (GetAsyncKeyState(0x51) & 0x8000) {
            ac->stop();
            clear();
            running = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return;
}

void start(AutoClicker* ac, HANDLE console) {
    clear();

    std::string input;
    short vk = VkKeyScan(ac->getKeybind());
    int vKey = LOBYTE(vk);

    std::cout << "Listening for keypress... (";
    SetConsoleTextAttribute(console, 3);
    std::cout << ac->getKeybind();
    SetConsoleTextAttribute(console, 7);
    std::cout << ")" << std::endl;

    while(true) {
        if (GetAsyncKeyState(0x51) & 0x8000) {
            ac->stop();
            clear();
            break;
        }
        else if (GetAsyncKeyState(vKey) & 0x8000) {
            clear();
            std::thread listener(quitListen, ac);
            std::cout << "RUNNING" << std::endl;
            ac->start();
            listener.join();
            break;
        }
    }

    clear();
    return;
}

void reset(AutoClicker* ac, HANDLE console) {
    //todo
    return;
}

int main()
{
    AllocConsole();
    freopen("CON", "w", stdout);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    AutoClicker* ac = new AutoClicker('k', 0.5);
    int choice;

    while(choice != 4) {
        printOptions(console);

        std::cin >> choice;

        switch(choice) {
            case 1:
                changeKeybind(ac, console);
                break;
            case 2:
                changeInterval(ac, console);
                break;
            case 3:
                start(ac, console);
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }

    delete ac;
    return 0;
}
