#include <iostream>
#include <list>

using namespace std;

int main() {
    // Create a list of integers
    std::list<int> lst = {10, 20, 30};

    // Add elements to the front and back
    lst.push_front(5);
    lst.push_back(40);

    // Remove an element from the front
    lst.pop_front();

    // Iterate through the list
    for (int val : lst) {
        std::cout << val << " ";
    }

    return 0;
}
