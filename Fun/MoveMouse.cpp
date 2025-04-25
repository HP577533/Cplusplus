#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

void moveMouse() {
    POINT cursorPos;
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    while (true) {
        GetCursorPos(&cursorPos);
        SetCursorPos(cursorPos.x + 10, cursorPos.y + 10);

        // Generate a 5-digit random number
        int randomNumber = 10000 + (rand() % 90000);
        cout << "Generated Random Number: " << randomNumber << endl;

        this_thread::sleep_for(chrono::seconds(1));
        SetCursorPos(cursorPos.x, cursorPos.y);
        this_thread::sleep_for(chrono::seconds(5));
    }
}

int main() {
    cout << "Mouse will move every 5 seconds. Press Ctrl+C to stop." << endl;
    moveMouse();
    return 0;
}

