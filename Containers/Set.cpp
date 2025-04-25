#include <iostream>
#include <set>

using namespace std;

int main() {
    // Create a set of integers (unique and sorted)
    set<int> s = {10, 20, 30, 10};

    // Add elements
    s.insert(25);

    // Remove an element
    s.erase(20);

    // Iterate through the set
    for (int val : s) {
        cout << val << " ";
    }

    return 0;
}
