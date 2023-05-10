#include <string>
#include <windows.h>
#include "AutoClicker.h"

AutoClicker::AutoClicker(char keybind = 'k', double interval = 0.5) {
    this->keybind = keybind;
    this->interval = interval;
}

void AutoClicker::start() {
    setKeepGoing(true);
    POINT mousePos;
    while(getKeepGoing()) {
        GetCursorPos(&mousePos);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, mousePos.x, mousePos.y, 0, 0);
        Sleep(getInterval() * 1000);
    }
}

void AutoClicker::stop() {
    setKeepGoing(false);
}

void AutoClicker::setKeybind(char keybind) {
    // validation logic
    this->keybind = keybind;
}

void AutoClicker::setInterval(double interval) {
    // validation logic
    this->interval = interval;
}

char AutoClicker::getKeybind() {
    return keybind;
}

double AutoClicker::getInterval() {
    return interval;
}

void AutoClicker::setKeepGoing(bool keepGoing) {
    this->keepGoing = keepGoing;
}

bool AutoClicker::getKeepGoing() {
    return keepGoing;
}
