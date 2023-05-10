#include <string>
#include <windows.h>
#include "AutoClicker.h"

AutoClicker::AutoClicker(char keybind = 'k', double interval = 0.5) {
    this->keybind = keybind;
    this->interval = interval;
}

void AutoClicker::click() {
    POINT mousePos;

    GetCursorPos(&mousePos);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, mousePos.x, mousePos.y, 0, 0);
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