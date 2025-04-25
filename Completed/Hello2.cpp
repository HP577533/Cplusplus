#include <iostream>

void printHelloWorld() {
    std::cout << "Hello World" << std::endl;
}

void printText(const std::string& text) {
    std::cout << text << std::endl;
}

void printStuff() {
    int file_size;
    int file_size2 = 1;
    std::cout << file_size << std::endl;
    std::cout << file_size2 << std::endl;
}

void swapVlues(){
    int a = 5;
    int b = 10;
    std::cout << "Before swap:" << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    int temp = a;
    a = b;
    b = temp;
    std::cout << "After swap:" << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
}

int main() {
    printHelloWorld();
    std::cout << std::endl;
    printText("Hello World2");
    std::cout << std::endl;
    printStuff();
    std::cout << std::endl;
    swapVlues();
    return 0;
}