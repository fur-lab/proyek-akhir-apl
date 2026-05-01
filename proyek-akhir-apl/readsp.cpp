#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
void tampilTabelKartu() {
    ifstream file("superpowers.csv");
    string line;
    if (!file.is_open()) {
        cout << "filenya ga ada\n";
        return;
    }
    cout << left << setw(5) << "ID"
        << setw(20) << "nama"
        << setw(25) << "class" << endl;
    cout << "----------------------------------------------------------\n";
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string id, isPlant, name, kelas;
        getline(ss, id, ',');
        getline(ss, isPlant, ',');
        getline(ss, name, ',');
        getline(ss, kelas, ',');
        cout << left << setw(5) << id
            << setw(20) << name
            << setw(25) << kelas << endl;
    }
    file.close();
}
int main() {
    cout << "-- daftar kartu --\n\n";
    tampilTabelKartu();
    return 0;
}