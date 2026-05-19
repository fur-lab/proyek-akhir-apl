#ifndef UTILS_H
#define UTILS_H

#include "data.h"
#include <string>
using namespace std;

void reassignIDs(Superpower cards[], int count);
int  readInt(const string& prompt);
int readInt(const string& prompt, int minVal, int maxVal);
string readString(const string& prompt);
int  linearSearchID(Superpower cards[], int count, int id);
void tungguEnter();
void clear();
int tampilMenu(const string& judul, const string opsi[], int jumlah);
vector<string> tampilMenuMulti(const string& judul, const string opsi[], int jumlah);
void printTable(vector<string> header, vector<vector<string>> rows);
string toLower(string str);
bool maksJumlahTag(const vector<string>& tags, int idx = 0);

#endif