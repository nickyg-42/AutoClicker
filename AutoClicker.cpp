#include <string>
#include <windows.h>

class AutoClicker {
    private:
        std::string keybind;
        double interval;
        bool keepGoing;

    public:
        AutoClicker(std::string keybind = "k", double interval = 0.5) {
            this->keybind = keybind;
            this->interval = interval;
        }

        AutoClicker() {
            keybind = "k";
            interval = 0.5;
        }

        void start() {
            setKeepGoing(true);

            POINT mousePos;
            while(getKeepGoing()) {
                GetCursorPos(&mousePos);

                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, mousePos.x, mousePos.y, 0, 0);

                Sleep(getInterval() * 1000);
            }
        }

        void stop() {
            setKeepGoing(false);
        }

        void setKeybind(std::string keybind) {
            // validation logic
            this->keybind = keybind;
        }

        void setInterval(double interval) {
            // validation logic
            this->interval = interval;
        }

        std::string getKeybind() {
            return keybind;
        }

        double getInterval() {
            return interval;
        }

        void setKeepGoing(bool keepGoing) {
            this->keepGoing = keepGoing;
        }

        bool getKeepGoing() {
            return keepGoing;
        }
};