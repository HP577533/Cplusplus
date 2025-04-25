#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Create a vector of integers
    vector<int> vec = {1, 2, 3, 4, 5};

    // Access elements by index
    cout << "Element at index 2: " << vec[2] << endl;

    // Add an element to the end
    vec.push_back(6);
    cout << "Element added: " << vec.back() << endl;

    // Iterate through the vector
    for (int val : vec) {
        cout << val << " ";
    }

    return 0;
}
