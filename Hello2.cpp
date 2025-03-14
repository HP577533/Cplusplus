#include <iostream>

void printHelloWorld() {
    std::cout << "Hello World" << std::endl;
}

void printText(const std::string& text) {
    std::cout << text << std::endl;
}

int main() {
    printHelloWorld();
    printText("Hello World2");
    return 0;
}