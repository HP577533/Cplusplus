#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <string>
#include <cctype>

using namespace std;

//Resource class where resource properties will be stored 
class Resource {
protected:
    string type, title, author, isbn, genre, year;

public:
    Resource(string type, string t, string a, string i, string y) : type(type), title(t), author(a), isbn(i), year(y) {}
    
    virtual void PrintOutResources() const {
        cout << "| Type: " << type <<" | Title: " << title << " | Author:" << author << " | Published in: " << year <<  " | ISBN: " << isbn << " | "<< endl;
    }

    //Creating getters for all resource details to be used in search method
    string getTitle() const {return title;}
    string getAuthor() const {return author;} 
    string getISBN() const {return isbn;}
    string getType() const {return type;}
    string getYear() const {return year;}
    
};

//Different resource classes inherited from main Resource class
class Book : public Resource {
public:
    Book(string t, string a, string i,string y) : Resource("Book", t, a, i, y) {}
};

class Journal : public Resource {
public:
    Journal(string t, string a, string i,string y) : Resource("Journal", t, a, i, y) {}
};

class Digital : public Resource {
public:
    Digital(string t, string a, string i, string y) : Resource("Digital", t, a, i, y ) {}
};

// Catalog class where resources will be added, deleted and searched for
class Catalog {
    //Create a STL container for the Resource class
    vector<shared_ptr<Resource>> resources;

public:
    //Method that will add a new resource using the .push_back() method
    void AddNewResource(shared_ptr<Resource> resource) {
        resources.push_back(resource);
    }

    //Method to remove a resource by its Title using the .erase() method
    void RemoveExistingResource(const string& title) {
        resources.erase(remove_if(resources.begin(), resources.end(),
            [&](const shared_ptr<Resource>& resource) {
                return resource->getTitle() == title;
            }), resources.end());
    }

    //Method to search for a resource using the getters created earlier
    vector<shared_ptr<Resource>> ResourceSearch(const string& keyword) const {
        vector<shared_ptr<Resource>> results;
        for (const auto& resource : resources) {
            if (resource->getTitle() == keyword ||
                resource->getAuthor() == keyword ||
                resource->getISBN() == keyword ||
                resource->getYear() == keyword ||
                resource->getType() == keyword) {
                results.push_back(resource);
            }
        }
        return results;
    }

    //Method to group resources by type
    void ReportGroupedByType() const {
        map<string, vector<shared_ptr<Resource>>> grouped;
        for (const auto& r : resources)
            grouped[r->getType()].push_back(r);

        for (const auto& pair : grouped) {
            cout << "\n-- " << pair.first << "s --\n";
            for (const auto& res : pair.second)
                res->PrintOutResources();
        }
    }
};

// Method that converts any string to lowercase for use in adding a new resource
string toLower(const string& str) {
    string result = str;
    for (char& c : result) c = tolower(c);
    return result;
}

// Checks if the ISBN is exactly 13 digits and all numbers
bool ValidISBN(const string& isbn) {
    if (isbn.length() != 13) return false;
    return all_of(isbn.begin(), isbn.end(), ::isdigit);
}

// Checks if the year is all numbers
bool ValidYear(const string& year) {
    return all_of(year.begin(), year.end(), ::isdigit);
}

int main() {
    Catalog catalog;
    int ActionChosen;

    while (true) {
        cout << "\n Welcome to the Richfield Library Catalog! \n";
        cout << "\n What would you like to do? \n";
        cout << "1. Add new Resource: \n2. Remove Resource: \n3. Search Resources: \n4. Generate Report: \n5. Exit: \n";
        cin >> ActionChosen;
        cin.ignore();

        if (ActionChosen == 1) {
            string type, title, author, isbn, year;

            // Keep asking for resource type until it is valid
            do {
                cout << "Enter type (book/journal/digital): ";
                getline(cin, type);
                type = toLower(type);
                if (type != "book" && type != "journal" && type != "digital") {
                    cout << "Invalid resource type. Please enter 'book', 'journal', or 'digital'.\n";
                }
            } while (type != "book" && type != "journal" && type != "digital");

            cout << "Title: ";
            getline(cin, title);
            cout << "Author: ";
            getline(cin, author);
            
            // Keep asking for year until it is valid
            do {
                cout << "Year: ";
                getline(cin, year);
                if (!ValidYear(year)) {
                    cout << "Please enter a valid year.\n";
                }
            } while (!ValidYear(year));

            // Keep asking for ISBN until it is valid
            do {
                cout << "ISBN (13 digits only): ";
                getline(cin, isbn);
                if (!ValidISBN(isbn)) {
                    cout << "Please enter a valid year ISBN. It must be 13 digits.\n";
                }
            } while (!ValidISBN(isbn));

            if (type == "book") catalog.AddNewResource(make_shared<Book>(title, author, isbn, year));
            else if (type == "journal") catalog.AddNewResource(make_shared<Journal>(title, author, isbn, year ));
            else catalog.AddNewResource(make_shared<Digital>(title, author, isbn, year));

        } else if (ActionChosen == 2) {
            string isbn;
            cout << "Enter title of resource to remove: ";
            getline(cin, isbn);
            catalog.RemoveExistingResource(isbn);
            cout << "Resource removed\n ";
        } else if (ActionChosen == 3) {
            string keyword;
            cout << "Enter keyword to search for: ";
            getline(cin, keyword);
            auto results = catalog.ResourceSearch(keyword);
            if (results.empty()) cout << "No matches found using this keyword.\n";
            else for (const auto& r : results) r->PrintOutResources();
        } else if (ActionChosen == 4) {
            catalog.ReportGroupedByType();
        } else if (ActionChosen == 5) {
            break;
        } else {
            cout << "Invalid. Please select a valid action to perform\n";
        }
    }
    return 0;
}
