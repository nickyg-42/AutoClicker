#include <string>
#include <windows.h>
#include <ctype.h>
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
    if (isalpha(keybind)) {
        this->keybind = keybind;
    }
    else return;
}

void AutoClicker::setInterval(double interval) {
    if (interval >= 0.0) {
        this->interval = interval;
    }
    else return;
}

char AutoClicker::getKeybind() {
    return keybind;
}

double AutoClicker::getInterval() {
    return interval;
}