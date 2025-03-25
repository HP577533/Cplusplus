#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

void moveMouse() {
    POINT cursorPos;
    while (true) {
        GetCursorPos(&cursorPos);
        SetCursorPos(cursorPos.x + 10, cursorPos.y + 10);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        SetCursorPos(cursorPos.x, cursorPos.y);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main() {
    std::cout << "Mouse will move every 5 seconds. Press Ctrl+C to stop." << std::endl;
    moveMouse();
    return 0;
}

