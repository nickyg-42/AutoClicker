#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <conio.h>
#include <ctype.h>
#include "AutoClicker.h"

std::atomic<bool> running(true);
std::atomic<bool> quit(false);

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
    std::string input;
    char newKeybind;

    std::cout << "Current keybind: ";
    SetConsoleTextAttribute(console, 3);
    std::cout << ac->getKeybind() << std::endl;
    SetConsoleTextAttribute(console, 7);
    std::cout << "Enter new Keybind (or q to cancel)" << std::endl;
    SetConsoleTextAttribute(console, 11);
    std::cout << "> ";
    SetConsoleTextAttribute(console, 7);
    
    std::cin.get();

    while (true) {
        std::getline(std::cin, input);
        
        if (input.length() == 1 && isalpha(input[0])) {
            break;
        }
        
        std::cout << "Invalid input. Please enter a letter a-z > ";
    }

    newKeybind = input[0];

    if (newKeybind != 'q' && newKeybind != 'Q') {
        ac->setKeybind(newKeybind);
    }

    clear();
    return;
}

void changeInterval(AutoClicker* ac, HANDLE console) {
    clear();
    std::string input;
    double newInterval;

    std::cout << "Current interval: ";
    SetConsoleTextAttribute(console, 3);
    std::cout << ac->getInterval() << std::endl;
    SetConsoleTextAttribute(console, 7);
    std::cout << "Enter your new interval (or q to cancel)" << std::endl;
    SetConsoleTextAttribute(console, 11);
    std::cout << "> ";
    SetConsoleTextAttribute(console, 7);

    std::cin.get();

    while (true) {
        std::getline(std::cin, input);

        if (input[0] == 'q') {
            clear();
            return;
        }

        try {
            newInterval = std::stod(input);
            if (newInterval < 0.0) throw std::invalid_argument("");
            else break;
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a positive double > ";
        }
    }

    ac->setInterval(newInterval);

    clear();
    return;
}

void quitListen(AutoClicker* ac, int vKey) {
    while(running) {
        if (GetAsyncKeyState(vKey) & 0x8000) {
            while (GetAsyncKeyState(vKey) & 0x8000) {};
            running = false;
            return;
        }
        else if (GetAsyncKeyState(0x51) & 0x8000) {
            while (GetAsyncKeyState(0x51) & 0x8000) {};
            running = false;
            quit = true;
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return;
}

void start(AutoClicker* ac, HANDLE console) {
    quit = false;
    clear();

    short vk = VkKeyScan(ac->getKeybind());
    int vKey = LOBYTE(vk);

    std::cout << "Press q at any time to exit" << std::endl;
    std::cout << "Listening for keypress... (";
    SetConsoleTextAttribute(console, 3);
    std::cout << ac->getKeybind();
    SetConsoleTextAttribute(console, 7);
    std::cout << ")" << std::endl;

    while(true) {
        if (GetAsyncKeyState(0x51) & 0x8000) {
            break;
        }
        else if (GetAsyncKeyState(vKey) & 0x8000) {
            clear();

            running = true;

            while (GetAsyncKeyState(vKey) & 0x8000) {};

            std::thread listener(quitListen, ac, vKey);

            SetConsoleTextAttribute(console, 7);
            std::cout << "Press q at any time to exit" << std::endl;
            SetConsoleTextAttribute(console, 2);
            std::cout << "Running..." << std::endl;
            SetConsoleTextAttribute(console, 7);
            std::cout << "Press ";
            SetConsoleTextAttribute(console, 3);
            std::cout << ac->getKeybind();
            SetConsoleTextAttribute(console, 7);
            std::cout << " at any time to pause" << std::endl;

            while(running) {
                ac->click();
                Sleep(ac->getInterval() * 1000);
            }

            listener.join();
            clear();

            if (quit) break;

            SetConsoleTextAttribute(console, 7);
            std::cout << "Press q at any time to exit" << std::endl;
            SetConsoleTextAttribute(console, 6);
            std::cout << "Paused" << std::endl;
            SetConsoleTextAttribute(console, 7);
            std::cout << "Listening for keypress... (";
            SetConsoleTextAttribute(console, 3);
            std::cout << ac->getKeybind();
            SetConsoleTextAttribute(console, 7);
            std::cout << ")" << std::endl;
            continue;
        }
    }

    clear();
    return;
}

void reset(AutoClicker* ac, HANDLE console) {
    while (GetAsyncKeyState(VK_RETURN) & 0x8000) {};
    clear();

    ac->setInterval(.5);
    ac->setKeybind('k');

    SetConsoleTextAttribute(console, 2);
    std::cout << "Settings reset to default" << std::endl;
    SetConsoleTextAttribute(console, 7);
    std::cout << "Press enter to continue..." << std::endl;

    while(true) {
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            while (GetAsyncKeyState(VK_RETURN) & 0x8000) {};
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    clear();
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

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

        // validate
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter an integer > ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

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
                reset(ac, console);
                break;
            default:
                std::cout << "Invalid choice. Please enter 1-5. " << std::endl;
                break;
        }
    }

    FreeConsole();
    delete ac;
    return 0;
}
