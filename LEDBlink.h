#pragma once
#include <string>

class LEDBlink {
    public:
        LEDBlink();

        void set(bool input);

        // boolean status();

        // void blink();
    private:
        bool ledState;
        std::string ledPath;
};
