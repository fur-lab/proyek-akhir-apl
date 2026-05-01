#include <iostream>
#include <string>
using namespace std;

#include "data.h"
#include "Auth.h"

bool Menu_Login = false;
string Input_Username;
string Input_Pw;
string Program_Jalan = "y";
int Pilihan_Login

int main () {
    system("cls");

    while (Program_Jalan == "y") {

    system("cls");

    cout << "=================================== " << endl;
    cout << "         Silahkan Login !" << endl;
    cout << "===================================  " << endl;
    cout << " 1. Login " << endl;
    cout << " 2. Sign in " << endl;
    cout << " 3. Exit " << endl;
    cout << "-----------------------------------" << endl; 

    try {
        cout << "Pilih (1-3) : " << endl;
        cout << "=================================== " << endl;
        cin >> Pilihan_Login;

        if (cin.fail()) {
            throw invalid_argument("Inputan harus berupa angka !");
        }

        if (Pilihan_Login < 0) {
            throw runtime_error("Bilangan harus bernilai positif !");
        }

    
        switch (Pilihan_Login) {
            case 1 : 
                Login();
                break;

            case 2 :          
                Sign_In();
                break;

            case 3 :            
                system("cls") ; 
                Program_Jalan = "n";
                break; 
            
            default : 
                system("cls"); 
                cout << "Pilihan Salah !" << endl; 
                system("pause");
                break; 
            } 
    
        }
        
        catch (const invalid_argument& e) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error : " << e.what() << endl;
            system("pause");
        }

        catch (const runtime_error& e) {
            cout << "Error : " << e.what() << endl;
            system("pause");
        }

    }
    return 0;
    }