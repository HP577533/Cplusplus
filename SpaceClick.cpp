#include <windows.h>
#include <iostream>

void hideConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_HIDE); // Hide the console window
}

int main() {
    std::cout << "Press SPACE to simulate a mouse click. Press ESC to exit.\n";

    // Hide the console window to run in the background
    hideConsoleWindow();

    while (true) {
        // Check if the spacebar is pressed
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            // Simulate a left mouse button down and up (click)
            INPUT input = {0};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            SendInput(1, &input, sizeof(INPUT));

            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(1, &input, sizeof(INPUT));

            // Add a small delay to prevent multiple clicks from a single press
            Sleep(200);
        }

        // Exit the program if the ESC key is pressed
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        Sleep(10); // Small delay to reduce CPU usage
    }

    return 0;
}