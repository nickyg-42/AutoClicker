#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
    AllocConsole();
    freopen("CON", "w", stdout); // redirect stdout to console window
    printf("Hello, console!\n");
    system("pause");
    return 0;
}
