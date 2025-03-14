#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>

using namespace std;

class Item {
protected:
    string name;
    double price;

public:
    Item(const string& name, double price) : name(name), price(price) {}
    virtual ~Item() = default;

    virtual void display() const {
        cout << "Item: " << name << ", Price: $" << price << endl;
    }
};

class DiscountedItem : public Item {
private:
    double discount;

public:
    DiscountedItem(const string& name, double price, double discount)
        : Item(name, price), discount(discount) {}

    void display() const override {
        cout << "Item: " << name << ", Price: $" << price
             << ", Discount: " << discount * 100 << "%" << endl;
    }
};

int main() {
    vector<unique_ptr<Item>> items;

    items.push_back(make_unique<Item>("Regular Item", 20.0));
    items.push_back(make_unique<DiscountedItem>("Discounted Item", 50.0, 0.2));

    for (const auto& item : items) {
        item->display();
    }

    return 0;
}