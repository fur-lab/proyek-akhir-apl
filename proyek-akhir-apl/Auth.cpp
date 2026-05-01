#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Auth.h"
#include <fstream>
#include <sstream>

vector<Akun> List_Akun;

int Muat_Akun() {
    ifstream file("accounts.csv");

    if (!file.is_open()) {
        cout << "  [!] File accounts.csv tidak ditemukan.\n";
        return 0;
        }

    string baris;
    getline(file, baris);
    int jumlah = 0;

    while (getline(file, baris) && jumlah < 300) {
        if (baris.empty())
            continue;
        if (!baris.empty() && baris.back() == '\r')
            baris.pop_back();

        stringstream parser(baris);
        string id, username, pw, role;
        getline(parser, id, ',');
        getline(parser, username, ',');
        getline(parser, pw, ',');
        getline(parser, role, ',');

        if (!id.empty()) {
            List_Akun acc_baru;
            acc_baru.ID = stoi(id);
            acc_baru.Username = username;
            acc_baru.Password  = pw;
            acc_baru.Role = role;

            accounts.push_back(acc_baru);
            jumlah++;
            }
    }
    return jumlah;
}

void Login () {
    system("cls");                         
    

    while () {
        cout << "Username : " << endl;
        cin >> Input_Username;
        cout << "Password : " << endl;
        cin >> Input_Pw;


            
        if (Input_Username !=  || Input_Pw != Pw_Admin) {
            cout << "Inputan salah !" << endl;
            system("pause");

        } else {
            break ;
        }
    }  
}

void Sign_In () {
    system("cls");                         
    

    while () {
        cout << "Username : " << endl;
        cin >> Input_Username;
        cout << "Password : " << endl;
        cin >> Input_Pw;


            
        if (Input_Username !=  ) {
            cout << "Username sudah ada !" << endl;
            system("pause");

        } else {
            break ;
        }
    }  
}