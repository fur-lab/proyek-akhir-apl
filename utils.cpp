#include "utils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;

void reassignIDs(Superpower cards[], int count) {
    for (int i = 0; i < count; i++)
        cards[i].id = i + 1;
}

int readInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(1000, '\n');
            return val;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "  [!] Input harus berupa angka. Coba lagi.\n";
    }
}

int readInt(const string& prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            if (val >= minVal && val <= maxVal) {
                cin.ignore(1000, '\n');
                return val;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Input harus antara " << minVal << "-" << maxVal << ". Coba lagi.\n";
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Input harus berupa angka. Coba lagi.\n";
        }
    }
}

string readString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        // trim spasi di awal dan akhir
        int start = input.find_first_not_of(" \t");
        int end   = input.find_last_not_of(" \t\r\n");
        if (start != string::npos) {
            input = input.substr(start, end - start + 1);
        } else {
            input = "";
        }
        if (!input.empty()) return input;
        cout << "  [!] Input tidak boleh kosong. Coba lagi.\n";
    }
}

int linearSearchID(Superpower cards[], int count, int id) {
    for (int i = 0; i < count; i++)
        if (cards[i].id == id) return i;
    return -1;
}

void tungguEnter() {
    cout << "\n  Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

#ifdef _WIN32
    #include <cstdlib>
#endif
void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int tampilMenu(const string& judul, const string opsi[], int jumlah) {
    int pilih;
    cout << judul << "\n";  // ← sebelumnya judul tidak di-cout
    for (int i = 0; i < jumlah; i++)
        cout << "  [ " << i+1 << " ] " << opsi[i] << "\n";  // ← tambah \n
    while (true) {
        cout << "  Pilih: ";
        if (cin >> pilih && pilih >= 1 && pilih <= jumlah) {
            cin.ignore(1000, '\n');
            return pilih;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "  [!] Pilihan tidak valid. Coba lagi.\n";
    }
}

vector<string> tampilMenuMulti(const string& judul, const string opsi[], int jumlah) {
    vector<string> hasil;
    while (true) {
        cout << judul << "\n";
        for (int i = 0; i < jumlah; i++)
            cout << "  [ " << i+1 << " ] " << opsi[i] << "\n";
        cout << "  [ 0 ] Selesai\n";
        cout << "  Terpilih: ";
        for (int i = 0; i < (int)hasil.size(); i++)
            cout << (i ? "|" : "") << hasil[i];
        cout << "\n  Pilih: ";
        int pilih;
        if (cin >> pilih) {
            cin.ignore(1000, '\n');
            if (pilih == 0) return hasil;
            if (pilih >= 1 && pilih <= jumlah)
                hasil.push_back(opsi[pilih - 1]);
            else
                cout << "  [!] Tidak valid.\n";
        } else {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "  [!] Tidak valid.\n";
        }
    }
}

void printTable(vector<string> header, vector<vector<string>> rows) {
    vector<int> lebar(header.size(), 0);
    for (int i = 0; i < (int)header.size(); i++)
        lebar[i] = header[i].size();
    for (auto& row : rows)
        for (int i = 0; i < (int)row.size() && i < (int)lebar.size(); i++)
            if (row[i].size() > (size_t)lebar[i]) lebar[i] = row[i].size();

    auto garis = [&]() {
        cout << "  +";
        for (int w : lebar) cout << string(w + 2, '-') << "+";
        cout << "\n";
    };
    auto cetakBaris = [&](vector<string>& cols) {
        cout << "  |";
        for (int i = 0; i < (int)cols.size(); i++) {
            cout << " " << cols[i]
                << string(lebar[i] - cols[i].size(), ' ') << " |";
        }
        cout << "\n";
    };

    garis();
    cetakBaris(header);
    garis();
    for (auto& row : rows) cetakBaris(row);
    garis();
}

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), 
              [](unsigned char c) { return tolower(c); });
    return str;
}

bool maksJumlahTag(const vector<string>& tags, int idx) {
    // Base case: selesai iterasi
    if (idx >= (int)tags.size()) {
        return true;
    }
    
    // Base case: sudah lebih dari 5
    if (idx >= 5) {
        return false;
    }
    
    // Recursive: lanjut ke index berikutnya
    return maksJumlahTag(tags, idx + 1);
}