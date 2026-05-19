#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "csv.h"
#include "utils.h"
#include "data.h"
#include <vector>
#include <string>
using namespace std;

void printSuperpowerDetail(Superpower& sp) {
    string clsStr;
    for (int j = 0; j < (int)sp.cls.size(); j++)
        clsStr += (j ? "|" : "") + sp.cls[j];

    vector<string> header = {"Field", "Value"};
    vector<vector<string>> rows = {
        {"ID",        to_string(sp.id)},
        {"Nama",      sp.name},
        {"Class",     clsStr},
        {"Category",  sp.category},
        {"Tribes",    sp.tribes},
        {"Cost",      (sp.cost     == -1 ? "-" : to_string(sp.cost))},
        {"Strength",  (sp.strength == -1 ? "-" : to_string(sp.strength))},
        {"Health",    (sp.health   == -1 ? "-" : to_string(sp.health))},
        {"Traits",    sp.traits},
        {"Effects",   sp.effects},
        {"Deskripsi", sp.desc},
        {"Signature", (sp.isSignature ? "Ya" : "Tidak")}
    };
    cout << "\n  DETAIL SUPERPOWER\n";
    printTable(header, rows);
}

void printCardDetail(Card& c) {
    string tribesStr, traitsStr, effectsStr;
    for (int j = 0; j < (int)c.tags.tribes.size(); j++)
        tribesStr += (j ? "|" : "") + c.tags.tribes[j];
    for (int j = 0; j < (int)c.tags.traits.size(); j++)
        traitsStr += (j ? "|" : "") + c.tags.traits[j];
    for (int j = 0; j < (int)c.tags.effects.size(); j++)
        effectsStr += (j ? "|" : "") + c.tags.effects[j];

    vector<string> header = {"Field", "Value"};
    vector<vector<string>> rows = {
        {"ID",        to_string(c.id)},
        {"Nama",      c.name},
        {"Team",      c.team},
        {"Class",     c.cardClass},
        {"Category",  c.category},
        {"Rarity",    c.rarity},
        {"Card Set",  c.cardSet},
        {"Cost",      (c.cost     == -1 ? "-" : to_string(c.cost))},
        {"Strength",  (c.strength == -1 ? "-" : to_string(c.strength))},
        {"Health",    (c.health   == -1 ? "-" : to_string(c.health))},
        {"Tribes",    (tribesStr.empty()  ? "-" : tribesStr)},
        {"Traits",    (traitsStr.empty()  ? "-" : traitsStr)},
        {"Effects",   (effectsStr.empty() ? "-" : effectsStr)},
        {"Deskripsi", (c.tags.desc.empty() ? "-" : c.tags.desc)}
    };
    cout << "\n  DETAIL KARTU\n";
    printTable(header, rows);
}

void allCardsReview() {
    vector<Card> plants  = loadCardCSV("plants.csv",  "plant");
    vector<Card> zombies = loadCardCSV("zombies.csv", "zombie");
    vector<Card> all = plants;
    all.insert(all.end(), zombies.begin(), zombies.end());
    if (all.empty()) {
        cout << "  Tidak ada kartu!\n";
        tungguEnter(); clear(); return;
    }
    while (true) {
        clear();
        cout << "  Daftar Kartu\n";
        vector<string> header = {"No", "Nama", "Team", "Class", "Cost", "Rarity"};
        vector<vector<string>> rows;
        for (auto& c : all)
            rows.push_back({
                to_string(c.id), c.name, c.team, c.cardClass,
                to_string(c.cost), c.rarity
            });
        printTable(header, rows);
        int pilih = readInt("  Pilih nomor untuk detail (0 = kembali): ");
        if (pilih == 0) return;
        bool ketemu = false;
        for (auto& c : all) {
            if (c.id == pilih) {
                clear();
                printCardDetail(c);
                tungguEnter();
                ketemu = true;
                break;
            }
        }
        if (!ketemu) cout << "  [!] Nomor tidak tersedia.\n";
    }
}

void superpowersReview() {
    vector<Superpower> sp = loadSuperpowerCSV("superpowers.csv");
    if (sp.empty()) {
        cout << "  Tidak ada superpower!\n";
        tungguEnter(); clear(); return;
    }
    while (true) {
        clear();
        cout << "  Daftar Superpower\n";
        vector<string> header = {"No", "Nama", "Class", "Category", "Cost", "Strength", "Health"};
        vector<vector<string>> rows;
        for (auto& s : sp) {
            string clsStr;
            for (int j = 0; j < (int)s.cls.size(); j++)
                clsStr += (j ? "|" : "") + s.cls[j];
            rows.push_back({
                to_string(s.id), s.name, clsStr, s.category,
                (s.cost     == -1 ? "-" : to_string(s.cost)),
                (s.strength == -1 ? "-" : to_string(s.strength)),
                (s.health   == -1 ? "-" : to_string(s.health))
            });
        }
        printTable(header, rows);
        int pilih = readInt("  Pilih nomor untuk detail (0 = kembali): ");
        if (pilih == 0) return;
        bool found = false;
        for (auto& s : sp) {
            if (s.id == pilih) {
                clear();
                printSuperpowerDetail(s);
                tungguEnter();
                found = true;
                break;
            }
        }
        if (!found) cout << "  [!] Nomor tidak tersedia.\n";
    }
}

int Rarity (string r) {
    if (r == "common") return 1;
    if (r == "uncommon") return 2;
    if (r == "rare") return 3;
    if (r == "super-rare") return 4;
    if (r == "event") return 5;
    if (r == "legendary") return 6;

    return 0;
}

// Fungsi Sorting ---------------------------------------------

void Sort_Selection_Cost_Asc(vector<Card>& Cards) {
    int n = Cards.size();
    for (int i = 0 ; i < n - 1 ; i++) {
        int indeksMin = i ;

    for (int j = i + 1 ; j < n ; j++) {
        if (Cards[j].cost < Cards[indeksMin].cost) {
            indeksMin = j ;
        }
    }

    if (indeksMin != i) {
        swap(Cards[i], Cards[indeksMin]) ;
        }
    }
}

void Merge_Sort_Rarity_Asc(vector<Card>& Cards, int l, int m, int r) {
    int n1 = m - l + 1 ; 
    int n2 = r - m ; 
    vector<Card> L, R;

    for (int i = 0; i < n1; i++) L.push_back (Cards[l + i]);
    for (int j = 0; j < n2; j++) R.push_back (Cards[m + 1+ j]);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (Rarity(L[i].rarity) <= Rarity(R[j].rarity)) {
            Cards[k] = L[i] ;
            i++ ;
        } else {
            Cards[k] = R[j] ;
            j++ ;
        }

    k++ ;
    }

    while (i < n1) {
        Cards[k] = L[i] ;
        i++;
        k++;
    }

    while (j < n2) {
        Cards[k] = R[j] ;
        j++;
        k++;
    }
}

void Merge_Sort_Rarity(vector<Card>& Cards, int l, int r) {
    if (l < r) {

        int m = l + (r - l) / 2 ;

        Merge_Sort_Rarity(Cards, l, m) ;
        Merge_Sort_Rarity(Cards, m + 1, r) ;

        Merge_Sort_Rarity_Asc(Cards, l, m, r) ;
    }
}

void Quick_Sort_Class_Asc(vector<Card>& Cards, int low, int high) {
    if (low >= high) return ;

    int mid = low + (high - low) / 2 ;
    string pivot = Cards[mid].cardClass ;
    int i = low, j = high ;

    while (i <= j) {
        while (Cards[i].cardClass < pivot) {
            i++ ;
        }

        while (Cards[j].cardClass > pivot) {
            j-- ;
        }

        if (i <= j) {
            swap(Cards[i], Cards[j]) ;
            i++ ;
            j-- ;
        }
    }

    if (low < j) {
        Quick_Sort_Class_Asc(Cards, low, j) ;
    }

    if (i < high) {
        Quick_Sort_Class_Asc(Cards, i, high) ;
    }
}

void menuLihat() {
    while (true) {
        clear();

        string opsi[] = {"Non-superpower", "Superpower", "Kembali"};
        int Pilihan_Jenis = tampilMenu("Pilih jenis kartu:", opsi, 3);

        if (Pilihan_Jenis == 3) return;
        if (Pilihan_Jenis == 2) {
            superpowersReview();
            continue;
        }

        while (true) {
            clear();
            string Opsi_Tim[] = {"Plants", "Zombie", "Kembali"};
            int Pilihan_Tim = tampilMenu("Pilih Tim :", Opsi_Tim, 3);

            if (Pilihan_Tim == 3) continue;

            string filename = (Pilihan_Tim == 1) ? "plants.csv" : "zombies.csv";
            string tim     = (Pilihan_Tim == 1) ? "plant"      : "zombie";
            vector<Card> cards = loadCardCSV(filename, tim);

            if (cards.empty()) {
                cout << " Tidak ada data kartu ! \n";
                system("pause");
                continue;
            }

            while (true) {
                clear();
                string Opsi_Sort[] = {"Cost", "Class", "Rarity", "Kembali"};
                int Pilihan_Sort = tampilMenu("Sorting ASC berdasarkan : ", Opsi_Sort, 4);

                if (Pilihan_Sort == 4) return;

                switch (Pilihan_Sort) {
                    case 1 : 
                        Sort_Selection_Cost_Asc(cards); 
                        break;
                    
                    case 2 : 
                        Quick_Sort_Class_Asc(cards, 0, cards.size() - 1); 
                        break;

                    case 3 : 
                    Merge_Sort_Rarity(cards, 0, cards.size() - 1); 
                    break;
                }

                clear();
                cout << "Hasil Sorting " << (Pilihan_Tim == 1 ? "plant" : "zombie") << "(ASC) \n";

                vector<string> header = {"ID", "Nama", "Class", "Cost", "Rarity"};
                vector <vector<string>> rows;

                for (auto& c : cards) {
                    rows.push_back({to_string(c.id), c.name, c.cardClass, to_string(c.cost), c.rarity});
                }

                printTable(header, rows);
                
                int Pilih_Kartu_Detail = readInt ("\n Pilih ID kartu untuk lihat detail (0 = kembali) : ");

                if (Pilih_Kartu_Detail != 0) {
                    bool Ketemu = false;

                    for (auto& c : cards) {
                        if (c.id == Pilih_Kartu_Detail) {
                            clear();
                            printCardDetail(c);
                            system("pause");
                            Ketemu = true;
                            break;
                        }
                    }

                    if (!Ketemu) {
                        cout << "ID tidak ditemukan. \n";
                        system("pause");
                    }
                } else {
                    continue;
                }
            }
        }
    }
}

void menuTambah() {
    clear();

    string opsiTeam[] = {"Plant", "Zombie", "Kembali"};
    int pilihanTeam = tampilMenu("=== TAMBAH KARTU ===\nPilih tim:", opsiTeam, 3);

    if (pilihanTeam == 3) return;
    string filename = (pilihanTeam == 1) ? "plants.csv" : "zombies.csv";
    string team     = (pilihanTeam == 1) ? "plant"      : "zombie";

    vector<Card> cards = loadCardCSV(filename, team);

    Card c;
    c.id   = cards.empty() ? 1 : cards.back().id + 1;
    c.team = team;
    clear();
    
    cout << "=== TAMBAH KARTU " << (pilihanTeam == 1 ? "PLANT" : "ZOMBIE") << " ===\n";

    c.name = readString("  Nama: ");
    c.name = toLower(c.name);

    bool namaSudahAda = false;
    for (int i = 0; i < (int)cards.size(); i++) {
    if (cards[i].name == c.name) {
        namaSudahAda = true;
        break;
        }
    }

    if (namaSudahAda) {
        cout << "  [!] Kartu dengan nama \"" << c.name << "\" sudah ada!\n";
        tungguEnter();
        return;
    }

    if (pilihanTeam == 1) {
        int pilihCls = tampilMenu("  Pilih Class:", PLANT_CLASS, 5);
        c.cardClass  = PLANT_CLASS[pilihCls - 1];
    } else {
        int pilihCls = tampilMenu("  Pilih Class:", ZOMBIE_CLASS, 5);
        c.cardClass  = ZOMBIE_CLASS[pilihCls - 1];
    }

    int pilihCat = tampilMenu("  Pilih Category:", CATEGORY, 3);
    c.category   = CATEGORY[pilihCat - 1];

    int pilihRar = tampilMenu("  Pilih Rarity:", RARITY, 6);
    c.rarity     = RARITY[pilihRar - 1];

    int pilihSet = tampilMenu("  Pilih Card Set:", CARD_SET, 5);
    c.cardSet    = CARD_SET[pilihSet - 1];

    c.cost     = readInt("  Cost     : ", 0, 20);
    c.strength = readInt("  Strength (-1 jika tidak ada): ", -1, 20);
    c.health   = readInt("  Health   (-1 jika tidak ada): ", -1, 20);

    while (true) {
        if (pilihanTeam == 1)
            c.tags.tribes = tampilMenuMulti("  Pilih Tribes (MAX 2, 0 = selesai):", PLANT_TRIBES, 20);
        else
            c.tags.tribes = tampilMenuMulti("  Pilih Tribes (MAX 2, 0 = selesai):", ZOMBIE_TRIBES, 15);

        if (c.tags.tribes.size() <= 2) {
            break;
        } else {
            cout << "[!] Total maksimal Tribes hanya 2 .\n";
            tungguEnter();
        }
    }

    while (true) {
        vector<string> traits;
        if (pilihanTeam == 1)
            traits = tampilMenuMulti("  Pilih Traits (MAX 5, 0 = selesai):", PLANT_TRAITS, 2);
        else
            traits = tampilMenuMulti("  Pilih Traits (MAX 5, 0 = selesai):", ZOMBIE_TRAITS, 4);

        vector<string> globalTraits = tampilMenuMulti("  Pilih Global Traits (MAX 5, 0 = selesai):", GLOBAL_TRAITS, 8);
        traits.insert(traits.end(), globalTraits.begin(), globalTraits.end());

        if (maksJumlahTag(traits, 0)) {
            c.tags.traits = traits;
            break;
        } else {
            cout << "[!] Total maksimal Traits hanya 5 .\n";
            tungguEnter();
        }
    }

    while (true) {
        c.tags.effects = tampilMenuMulti("  Pilih Effects (MAX 5, 0 = selesai) :", EFFECTS, 15);

        if (maksJumlahTag(c.tags.effects,0)) {
            break;
        } else {
            cout << "[!] Total maksimal Effects hanya 5 .\n";
            tungguEnter();
        }
    }

    c.tags.desc = readString("  Deskripsi (- jika tidak ada): ");
    if (c.tags.desc == "-") c.tags.desc = "";
    cards.push_back(c);
    saveCardCSV(filename, cards);
    clear();
    cout << "  [OK] Kartu berhasil ditambahkan!\n";
    tungguEnter();
}

void menuUpdate() {
    clear();

    string opsiTeam[] = {"Plant", "Zombie", "Kembali"};
    int pilihanTeam = tampilMenu("=== UPDATE KARTU ===\nPilih tim:", opsiTeam, 3);

    if (pilihanTeam == 3) return;
    string filename = (pilihanTeam == 1) ? "plants.csv" : "zombies.csv";
    string team     = (pilihanTeam == 1) ? "plant"      : "zombie";
    
    vector<Card> cards = loadCardCSV(filename, team);

    if (cards.empty()) {
        cout << "  Tidak ada kartu!\n";
        tungguEnter(); clear(); return;
    }

    clear();
    cout << "=== UPDATE KARTU " << (pilihanTeam == 1 ? "PLANT" : "ZOMBIE") << " ===\n";

    vector<string> header = {"No", "Nama", "Class", "Cost", "Rarity"};
    vector<vector<string>> rows;

    for (auto& c : cards)
        rows.push_back({
            to_string(c.id), c.name, c.cardClass,
            to_string(c.cost), c.rarity
        });

    printTable(header, rows);

    int pilih = readInt("  Pilih ID kartu yang akan diupdate (0 = kembali): ");

    if (pilih == 0) return;
    int idx = -1;

    for (int i = 0; i < (int)cards.size(); i++) {
        if (cards[i].id == pilih) { idx = i; break; }
    }

    if (idx == -1) {
        cout << "  [!] ID tidak ditemukan.\n";
        tungguEnter(); return;
    }

    Card& c = cards[idx];
    clear();

    cout << "=== UPDATE KARTU: " << c.name << " ===\n";
    cout << "  (Tekan Enter untuk mempertahankan nilai lama)\n\n";

    string input;
    cout << "  Nama [" << c.name << "]: ";
    getline(cin, input);

    if (!input.empty()) {
        input = toLower(input);
        if (input == c.name) {
            cout << "  [!] Nama baru sama dengan nama sebelumnya!\n";
            tungguEnter();
            return;
        }

        bool namaSudahAda = false;
        for (int i = 0; i < (int)cards.size(); i++) {
            if (cards[i].name == input && cards[i].id != c.id) {
                namaSudahAda = true;
                break;
            }
        }

        if (namaSudahAda) {
            cout << "  [!] Kartu dengan nama \"" << input << "\" sudah ada!\n";
            tungguEnter();
            return;
            }
            c.name = input;
    }

    cout << "  Cost saat ini: " << c.cost << "\n";
    int val = readInt("  Cost baru (-999 = skip): ");
    if (val != -999) c.cost = val;

    cout << "  Strength saat ini: " << (c.strength == -1 ? "-" : to_string(c.strength)) << "\n";
    val = readInt("  Strength baru (-999 = skip, -1 = tidak ada): ");
    if (val != -999) c.strength = val;

    cout << "  Health saat ini: " << (c.health == -1 ? "-" : to_string(c.health)) << "\n";
    val = readInt("  Health baru (-999 = skip, -1 = tidak ada): ");
    if (val != -999) c.health = val;
    
    cout << "  Traits saat ini: ";
    for (int j = 0; j < (int)c.tags.traits.size(); j++)
        cout << (j ? "|" : "") << c.tags.traits[j];
    cout << "\n";
    string opsiUbah[] = {"Ya", "Tidak"};
    int ubahTraits = tampilMenu("  Ubah Traits?", opsiUbah, 2);
    if (ubahTraits == 1) {

        while (true) {
            vector<string> traits;
            if (pilihanTeam == 1) {
                traits = tampilMenuMulti("  Pilih Traits baru (MAX 5, 0 = selesai):", PLANT_TRAITS, 2);
            } else {
                traits = tampilMenuMulti("  Pilih Traits baru (MAX 5, 0 = selesai):", ZOMBIE_TRAITS, 4);
            vector<string> globalTraits = tampilMenuMulti("  Pilih Global Traits baru (MAX 5, 0 = selesai) :", GLOBAL_TRAITS, 8);
            traits.insert(traits.end(), globalTraits.begin(), globalTraits.end());
            }
            
            if (traits.size() <= 5) {
                c.tags.traits = traits;
                break;
            } else {
                cout << "[!] Total maksimal Traits hanya 5 .\n";
                tungguEnter();
            }
        }
    }
    
    cout << "  Effects saat ini: ";
    for (int j = 0; j < (int)c.tags.effects.size(); j++)
        cout << (j ? "|" : "") << c.tags.effects[j];
    cout << "\n";
    int ubahEffects = tampilMenu("  Ubah Effects?", opsiUbah, 2);

    if (ubahEffects == 1) {

        while (true) {
            vector<string> effects = tampilMenuMulti("  Pilih Effects baru (MAX 5, 0 = selesai) :", EFFECTS, 15);
            cout << "  Deskripsi saat ini: " << (c.tags.desc.empty() ? "-" : c.tags.desc) << "\n";
            cout << "  Deskripsi baru (Enter = skip, - = hapus): ";
            getline(cin, input);

            if (effects.size() <= 5) {
                c.tags.effects = effects;
                break;
            } else {
                cout << "[!] Total maksimal Effects hanya 5 .\n";
                tungguEnter();
            }
        }
    }

    if (input == "-")        c.tags.desc = "";
    else if (!input.empty()) c.tags.desc = input;
    saveCardCSV(filename, cards);
    clear();
    cout << "  [OK] Kartu berhasil diupdate!\n";
    tungguEnter();
}

void menuDelete() {
    clear();
    string opsiTeam[] = {"Plant", "Zombie", "Kembali"};
    int pilihanTeam = tampilMenu("=== HAPUS KARTU ===\nPilih tim:", opsiTeam, 3);

    if (pilihanTeam == 3) return;
    string filename = (pilihanTeam == 1) ? "plants.csv" : "zombies.csv";
    string team     = (pilihanTeam == 1) ? "plant"      : "zombie";

    vector<Card> cards = loadCardCSV(filename, team);

    if (cards.empty()) {
        cout << "  Tidak ada kartu!\n";
        tungguEnter(); clear(); return;
    }
    clear();

    cout << "=== HAPUS KARTU " << (pilihanTeam == 1 ? "PLANT" : "ZOMBIE") << " ===\n";

    vector<string> header = {"No", "Nama", "Class", "Cost", "Rarity"};
    vector<vector<string>> rows;

    for (auto& c : cards)
        rows.push_back({
            to_string(c.id), c.name, c.cardClass,
            to_string(c.cost), c.rarity
        });

    printTable(header, rows);

    int pilih = readInt("  Pilih ID kartu yang akan dihapus (0 = kembali): ");
    if (pilih == 0) return;

    int idx = -1;
    for (int i = 0; i < (int)cards.size(); i++) {
        if (cards[i].id == pilih) { idx = i; break; }
    }

    if (idx == -1) {
        cout << "  [!] ID tidak ditemukan.\n";
        tungguEnter(); return;
    }
    clear();

    printCardDetail(cards[idx]);

    string opsiKonfirm[] = {"Ya, hapus", "Batal"};
    int konfirm = tampilMenu("  Yakin ingin menghapus kartu ini?", opsiKonfirm, 2);

    if (konfirm == 2) {
        cout << "  [i] Penghapusan dibatalkan.\n";
        tungguEnter(); return;
    }

    cards.erase(cards.begin() + idx);
    saveCardCSV(filename, cards);
    clear();
    cout << "  [OK] Kartu berhasil dihapus!\n";
    tungguEnter();
}

/// FUNGSI SEARCHING ----------
int Cari_Nama_Linear (vector<Card>& Cards, int Panjang, string Target) {
    for (int i = 0 ; i < Panjang ; i++) {
        if (Cards[i].name == Target) {
            return i ;
            break ;
            }
        }

    return -1 ; 
}

void Menu_Cari_Nama (vector<Card>& Cards, int Panjang) {
    string Target ;
    system("cls") ;

    if (Panjang == 0) {
        cout << "Data masih kosong" ;
        system("pause") ;
        return ;
    }

    cout << "=================================== " << endl ;
    cout << "            CARI NAMA       " << endl ;
    cout << "=================================== " << endl ;
    cout << "Masukan Nama yang ingin dicari : " ; cin >> Target ;
    
    int Hasil = Cari_Nama_Linear(Cards, Panjang, Target) ;

    if (Hasil != -1) {
        system("cls") ;
        cout << "Nama ditemukan !" << endl ;
        cout << "------------------------------" << endl ;

        printCardDetail(Cards[Hasil]);

        system("pause") ;

    } else {
        cout << "Nama tidak ditemukan dalam data ! " << endl ;
        system("pause") ;
    }
}

void menuSearch() {
    while (true) {
        clear();

        string opsi[] = {"Plants", "Zombie", "Kembali"};
        int Pilih_Tim_Search = tampilMenu("Pilih tim yang ingin dicari :", opsi, 3);

        if (Pilih_Tim_Search == 3) return;

        string filename = (Pilih_Tim_Search == 1) ? "plants.csv" : "zombies.csv";
        string tim     = (Pilih_Tim_Search == 1) ? "plant"      : "zombie";
        vector<Card> cards = loadCardCSV(filename, tim);

        if (cards.empty()) {
            cout << " Tidak ada data kartu ! \n";
            system("pause");
            continue;
        }

        clear();

        Menu_Cari_Nama(cards, cards.size());

    }
}