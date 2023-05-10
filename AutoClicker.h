#ifndef AUTOCLICKER_H
#define AUTOCLICKER_H

#include <string>

class AutoClicker {
    private:
        char keybind;
        double interval;

    public:
        AutoClicker(char keybind, double interval);

        void click();

        void setKeybind(char keybind);

        void setInterval(double interval);

        char getKeybind();

        double getInterval();

        void setKeepGoing(bool keepGoing);

        bool getKeepGoing();
};

#endif