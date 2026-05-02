#include <iostream>
using namespace std;

#include "data.h"

void tampilMenu (string judul, const string opsi[], int jumlah) {
    cout << judul << "\n";
    for (int i=0; i<jumlah; i++) {
        cout << " [" << i+1 << "] " << opsi[i] << "\n";
    }
}

int main() {
    tampilMenu("Daftar Rarity: ", RARITY, 6);
    Card c;
    
    return 0;
}