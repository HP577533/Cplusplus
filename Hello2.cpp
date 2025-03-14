#include <iostream>

void printHelloWorld() {
    std::cout << "Hello World" << std::endl;
}

void printText(const std::string& text) {
    std::cout << text << std::endl;
}

void printStuff() {
    int file_size;
    int file_size2 = 0;
    std::cout << file_size << std::endl;
    std::cout << file_size2 << std::endl;
}

int main() {
    printHelloWorld();
    printText("Hello World2");
    printStuff();
    return 0;
}