#ifndef DATA_H
#define DATA_H

struct Akun {
    int ID;
    string Username;
    string Password;
    string Role;
};

extern vector<Akun> List_Akun;
extern bool Menu_Login;
extern string Input_Username;
extern string Input_Pw;




#endif