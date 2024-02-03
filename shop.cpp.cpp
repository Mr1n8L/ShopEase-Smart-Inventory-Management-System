#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#define FILE_NAME "shop.dat"

using namespace std;

class Item {
private:
    char itemCode[20], itemName[20];
    double itemPrice;

public:
    void readItem() {
        cout << endl << "INPUT ITEM DETAILS" << endl;
        cout << "ITEM CODE: ";
        cin.ignore();
        cin.getline(itemCode, 20);
        cout << "ITEM NAME: ";
        cin.getline(itemName, 20);
        cout << "ITEM PRICE: ";
        cin >> itemPrice;
    }

    void displayItem() const {
        cout << left << setw(15) << itemCode
             << left << setw(15) << itemName
             << left << setw(15) << setprecision(4) << itemPrice << endl;
    }

    const char* getItemCode() const { return itemCode; }
};

int writeToFile(const Item& item, const string& filename) {
    ofstream file(filename, ios::out | ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Error writing file" << endl;
        return -1;
    }
    file.write(reinterpret_cast<const char*>(&item), sizeof(item));
    cout << "SAVED..." << endl;
    return 0;
}

int readFromFile(const string& filename) {
    Item item;
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return -1;
    }
    cout << endl
         << left << setw(15) << "ITEM CODE"
         << left << setw(15) << "ITEM NAME"
         << left << setw(15) << "ITEM PRICE" << endl;

    while (file.read(reinterpret_cast<char*>(&item), sizeof(item))) {
        item.displayItem();
    }

    file.close();
    return 0;
}

int searchItemCode(const string& search, const string& filename) {
    Item item;
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return -1;
    }
    cout << endl
         << left << setw(15) << "ITEM CODE"
         << left << setw(15) << "ITEM NAME"
         << left << setw(15) << "ITEM PRICE" << endl;

    while (file.read(reinterpret_cast<char*>(&item), sizeof(item))) {
        if (search == item.getItemCode()) {
            item.displayItem();
            file.close();
            return 0;
        }
    }

    file.close();
    cout << "\nItem not found." << endl;
    return -1;
}

int main() {
    Item item;
    int menuItem;
    string search;
    cout << "**********SHOP PROGRAM**********" << endl;
    cout << "0: EXIT" << endl;
    cout << "1: ADD ITEM" << endl;
    cout << "2: DISPLAY ALL ITEMS" << endl;
    cout << "3: SEARCH ITEM" << endl;

    while (true) {
        cout << endl << "PLEASE SELECT AN OPTION: ";
        cin >> menuItem;
        switch (menuItem) {
            case 0:
                return 0;
            case 1:
                writeToFile(item, FILE_NAME);
                break;
            case 2:
                readFromFile(FILE_NAME);
                break;
            case 3:
                cout << "\nSearch for item code: ";
                cin >> search;
                searchItemCode(search, FILE_NAME);
                break;
            default:
                cout << "\nERROR: Unknown selection" << endl;
                return 0;
        }
    }

    return 0;
}
