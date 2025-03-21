#include <iostream>  // For input/output in the main programme
#include <string>    // For using the string class in the classes
#include <vector>    // For using the vector container in the classes
#include <map>       // For using the map container in generate report

using namespace std; // Using the standard namespace

// Base class Resource
class Resource {
protected:
    // Properties 
    string title;
    string author;
    int year;
    string ISBN;
    string type;

public:
    // Constructor
    Resource(const string& title, const string& author, int year, const string& ISBN, const string& type)
        : title(title), author(author), year(year), ISBN(ISBN), type(type) {}

    // Method display resource
    virtual void display() const {
        cout << "Title: " << title << "\nAuthor: " << author << "\nYear: " << year
             << "\nISBN: " << ISBN << "\nType: " << type << endl;
    }

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    string getType() const { return type; }

    // Destructor
    virtual ~Resource() = default;
};

// Inheritance class Books
class Book : public Resource {
public:
    Book(const string& title, const string& author, int year, const string& ISBN)
        : Resource(title, author, year, ISBN, "Book") {}
};

// Inheritance class Journals
class Journal : public Resource {
public:
    Journal(const string& title, const string& author, int year, const string& ISBN)
        : Resource(title, author, year, ISBN, "Journal") {}
};

// Inheritance class Digital Resources
class DigitalResource : public Resource {
public:
    DigitalResource(const string& title, const string& author, int year, const string& ISBN)
        : Resource(title, author, year, ISBN, "DigitalResource") {}
};

// Catalog class
class Catalog {
private:
    vector<shared_ptr<Resource>> resources;

public:
    // Add a resource to the catalog
    void addResource(shared_ptr<Resource> resource) {
        resources.push_back(resource);
    }

    // Remove a resource from the catalog by ISBN
    void removeResource(const string& ISBN) {
        resources.erase(
            remove_if(resources.begin(), resources.end(),
                [&ISBN](const shared_ptr<Resource>& resource) {
                    return resource->getISBN() == ISBN;
                }),
            resources.end());
    }

    // Search for resources using multiple criteria
    vector<shared_ptr<Resource>> searchResources(const string& title = "", const string& author = "", const string& ISBN = "", const string& type = "") {
        vector<shared_ptr<Resource>> results;
        for (const auto& resource : resources) {
            if ((title.empty() || resource->getTitle() == title) &&
                (author.empty() || resource->getAuthor() == author) &&
                (ISBN.empty() || resource->getISBN() == ISBN) &&
                (type.empty() || resource->getType() == type)) {
                results.push_back(resource);
            }
        }
        return results;
    }

    // Generate a report, grouped by type
    void generateReport() {
        map<string, vector<shared_ptr<Resource>>> groupedResources;
        for (const auto& resource : resources) {
            groupedResources[resource->getType()].push_back(resource);
        }

        for (const auto& group : groupedResources) {
            cout << "Type: " << group.first << endl;
            for (const auto& resource : group.second) {
                resource->display();
                cout << endl;
            }
        }
    }
};

int main() {
    Catalog catalog;

    // Create some resources
    shared_ptr<Resource> book = make_shared<Book>("The Piano Man", "Henry", 2025, "1");
    shared_ptr<Resource> journal = make_shared<Journal>("Private", "Unknown", 2021, "2");
    shared_ptr<Resource> digitalResource = make_shared<DigitalResource>("C++ Documentation", "Various Authors", 2023, "3");
    catalog.addResource(book);
    catalog.addResource(journal);
    catalog.addResource(digitalResource);

    // Terminal interface
    int choice;
    do {
        cout << "\nCatalog Menu:\n";
        cout << "1. Add Resource\n";
        cout << "2. Remove Resource\n";
        cout << "3. Search Resources\n";
        cout << "4. Generate Report\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        // Add a resource
        case 1: {
            string title, author, ISBN, type;
            int year;
            cout << "\nEnter title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter ISBN: ";
            cin >> ISBN;
            cout << "Enter type (Book/Journal/DigitalResource): ";
            cin >> type;

            shared_ptr<Resource> resource;
            if (type == "Book") {
                // Add Book
                resource = make_shared<Book>(title, author, year, ISBN);
            } else if (type == "Journal") {
                // Add Journal
                resource = make_shared<Journal>(title, author, year, ISBN);
            } else if (type == "DigitalResource") {
                // Add Digital Resource
                resource = make_shared<DigitalResource>(title, author, year, ISBN);
            } else {
                cout << "Invalid type entered.\n";
                break;
            }
            catalog.addResource(resource);
            cout << "Resource added successfully.\n";
            break;
        }
        case 2: {
            // Remove a resource
            string ISBN;
            cout << "\nEnter ISBN of the resource to remove: ";
            cin >> ISBN;
            catalog.removeResource(ISBN);
            cout << "Resource removed successfully.\n";
            break;
        }
        case 3: {
            // Search for resources
            string title, author, ISBN, type;
            cout << "\nEnter title (or leave empty): ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter author (or leave empty): ";
            getline(cin, author);
            cout << "Enter ISBN (or leave empty): ";
            getline(cin, ISBN);
            cout << "Enter type (or leave empty): ";
            getline(cin, type);

            // Display search results
            vector<shared_ptr<Resource>> results = catalog.searchResources(title, author, ISBN, type);
            if (results.empty()) {
                cout << "No resources found.\n";
            } else {
                for (const auto& resource : results) {
                    resource->display();
                    cout << endl;
                }
            }
            break;
        }
        case 4:
            // Generate a report
            catalog.generateReport();
            break;
        case 5:
            // Exit
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}