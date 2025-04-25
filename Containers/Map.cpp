#include <iostream>
#include <map>

using namespace std;

int main() {
    // Create a map of key-value pairs (name -> age)
    map<string, int> ageMap;
    ageMap["Alice"] = 30;
    ageMap["Bob"] = 25;
    ageMap["Charlie"] = 35;

    // Access elements by key
    cout << "Bob's age: " << ageMap["Bob"] << endl;

    // Iterate through the map (sorted by key)
    for (const auto& pair : ageMap) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
