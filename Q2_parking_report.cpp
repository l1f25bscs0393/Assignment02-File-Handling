/*
 * Name       : HAFSA SHABBIR
 * Reg No     : L1F25BSCS0393
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    ifstream inFile("parking.txt");

    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;

    inFile >> d >> slash >> m >> slash >> y;
    inFile.ignore(100, '\n');
    inFile.ignore(100, '\n');

    cout << "Parking report for "
         << d << "/" << m << "/" << y << endl;

    ofstream outFile("receipts.txt");
    outFile << "Receipts for "
            << d << "/" << m << "/" << y << endl;

    char plate[15];
    char longestPlate[15] = "";
    char type;
    char colon1, colon2;

    int inH, inM, outH, outM;
    int count = 0, cars = 0, bikes = 0;
    int total = 0, longest = -1;
    int longestHours = 0, longestMinutes = 0;

    while (count < 30 &&
           inFile >> plate >> type
                  >> inH >> colon1 >> inM
                  >> outH >> colon2 >> outM) {

        int start = inH * 60 + inM;
        int finish = outH * 60 + outM;
        int minutes = finish - start;

        int hoursCharged = (minutes + 59) / 60;

        if (hoursCharged == 0) {
            hoursCharged = 1;
        }

        int fee;

        if (type == 'C') {
            fee = hoursCharged * 100;
            cars++;
        } else {
            fee = hoursCharged * 40;
            bikes++;
        }

        cout << plate << " ";

        if (type == 'C') {
            cout << "Car ";
        } else {
            cout << "Bike ";
        }

        cout << minutes / 60 << " h "
             << minutes % 60 << " min "
             << "Fee: " << fee << endl;

        outFile << plate << " " << fee << endl;

        total = total + fee;
        count++;

        if (minutes > longest) {
            longest = minutes;
            strcpy(longestPlate, plate);
            longestHours = minutes / 60;
            longestMinutes = minutes % 60;
        }
    }

    inFile.close();
    outFile.close();

    if (count == 0) {
        cout << "No vehicles found!" << endl;
        return 0;
    }

    cout << "Vehicles: " << count << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << total << endl;
    cout << "Longest stay: " << longestPlate
         << " (" << longestHours << " h "
         << longestMinutes << " min)" << endl;

    return 0;
}
