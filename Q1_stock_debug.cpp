/*
 * Name       : HAFSA SHABBIR
 * Reg No     : L1F25BSCS0393
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#include <iostream>
// FIX 1: <fstream> was missing, so file streams were not recognized.
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");

    // FIX 2: !inFile checks whether the file failed to open.
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: Skip the header line before reading item records.
    inFile.ignore(100, '\n');

    // FIX 4: ios::app keeps old reorder.txt lines and adds new ones.
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;

    // FIX 5: double preserves decimal values in the stock total.
    double total = 0;

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;
        if (qty < 10) {
            // FIX 6: endl puts each low-stock item on a separate line.
            reorder << code << " " << qty << endl;
            low++;
        }
    }

    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}
