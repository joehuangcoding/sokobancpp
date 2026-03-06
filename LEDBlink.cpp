#include "./LEDBlink.h"
#include <fstream>
// #include <unistd.h> 

using namespace std;

LEDBlink::LEDBlink()
{
    ledPath = "/sys/class/gpio/gpio17/value";
    ledState = false;
}

void LEDBlink::set(bool input) 
{
    if (ledState == input) return;
#ifdef __aarch64__
    ofstream valueFile(ledPath);
    if (!valueFile.is_open()) return;

    valueFile << (input ? "1" : "0");
    valueFile.close();

    ledState = input;
#else

#endif
}