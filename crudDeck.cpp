#include <iostream>
#include "utils.h"
#include "crudDeck.h"
#include "csv.h"
using namespace std;

// Helper: cari nama hero by id
string getNamaHero(vector<Hero>& heroes, int heroId) {
    for (auto& h : heroes)
        if (h.id == heroId) return h.name;
    return "unknown";
}

// Helper: cari nama kartu by id
string getNamaKartu(vector<Card>& plants, vector<Card>& zombies,
                    int cardId, bool isPlant) {
    vector<Card>& kartu = isPlant ? plants : zombies;
    for (auto& c : kartu)
        if (c.id == cardId) return c.name;
    return "unknown";
}

void lihatDek(vector<Deck>& decks, vector<Hero>& heroes,
            vector<Card>& plants, vector<Card>& zombies,
            int ownerId) {
    clear();
    while (true) {
        clear();

        // Filter dek milik user
        vector<Deck*> milikSaya;
        for (auto& d : decks)
            if (d.ownerId == ownerId)
                milikSaya.push_back(&d);

        if (milikSaya.empty()) {
            cout << "  Kamu belum punya dek.\n";
            tungguEnter();
            return;
        }

        // Tampilkan preview
        cout << "=== DEK KAMU ===\n";
        vector<string> header = {"No", "Nama Dek", "Tim", "Hero", "Status"};
        vector<vector<string>> rows;
        for (int i = 0; i < (int)milikSaya.size(); i++) {
            Deck* d = milikSaya[i];
            rows.push_back({
                to_string(i + 1),
                d->deckName,
                d->isPlant ? "Plant" : "Zombie",
                getNamaHero(heroes, d->heroId),
                d->status
            });
        }
        printTable(header, rows);

        // Input pilihan
        cout << "  [0] Kembali\n";
        int pilih = readInt("  Pilih no dek: ");
        if (pilih == 0) return;
        if (pilih < 1 || pilih > (int)milikSaya.size()) {
            cout << "  [!] Pilihan tidak valid.\n";
            tungguEnter();
            continue;
        }

        // Tampilkan detail dek
        Deck* d = milikSaya[pilih - 1];
        clear();
        cout << "================================\n";
        cout << "  Nama Dek : " << d->deckName << "\n";
        cout << "  Hero     : " << getNamaHero(heroes, d->heroId) << "\n";
        cout << "  Tim      : " << (d->isPlant ? "Plant" : "Zombie") << "\n";
        cout << "  Status   : " << d->status << "\n";
        cout << "================================\n";

        // Tampilkan isi dek
        vector<string> hKartu = {"ID", "Nama Kartu", "Qty"};
        vector<vector<string>> rKartu;
        for (auto& dc : d->cards) {
            string nama = getNamaKartu(plants, zombies, dc.cardId, d->isPlant);
            rKartu.push_back({
                to_string(dc.cardId),
                nama,
                to_string(dc.qty)
            });
        }
        printTable(hKartu, rKartu);
        tungguEnter();
        clear();
    }
}

void tambahDek(vector<Deck>& decks, vector<Hero>& heroes,
            vector<Card>& plants, vector<Card>& zombies,
            int ownerId) {
    clear();
    cout << "=== BUAT DEK BARU ===\n";

    // Load & Tampilkan Hero
    vector<string> headerHero = {"No", "Nama Hero", "Tim", "Class"};
    vector<vector<string>> rowHero;
    for (int i = 0; i < (int)heroes.size(); i++) {
        rowHero.push_back({
            to_string(i + 1),
            heroes[i].name,
            heroes[i].isPlant ? "Plant" : "Zombie",
            heroes[i].classes
        });
    }
    printTable(headerHero, rowHero);

    cout << "  [0] Kembali\n";
    int pilihHero = readInt("  Pilih Hero (nomor): ");
    if (pilihHero == 0) return;
    if (pilihHero < 1 || pilihHero > (int)heroes.size()) {
        cout << "  [!] Hero tidak valid.\n";
        tungguEnter();
        return;
    }

    Hero heroTerpilih = heroes[pilihHero - 1];

    // Nama Dek
    string namaDek = readString("  Masukkan Nama Dek: ");

    // Filter Class Hero
    vector<string> classHero = splitPipe(heroTerpilih.classes);
    vector<Card>& poolKartu = heroTerpilih.isPlant ? plants : zombies;
    vector<Card> kartuTersedia;
    

    for (auto& c : poolKartu) {
        for (auto& cls : classHero) {
            if (c.cardClass == cls) {
                kartuTersedia.push_back(c);
                break; 
            }
        }
    }

    // Inisialisasi struct Deck baru
    Deck newDeck;
    newDeck.id = (decks.empty()) ? 1 : decks.back().id + 1;
    newDeck.ownerId = ownerId;
    newDeck.deckName = namaDek;
    newDeck.isPlant = heroTerpilih.isPlant;
    newDeck.heroId = heroTerpilih.id;

    int totalKartu = 0;

    // Input Kartu
    while (totalKartu < 40) {
        clear();
        cout << "  Dek: " << namaDek << " | Hero: " << heroTerpilih.name << "\n";
        cout << "  Jumlah Kartu: " << totalKartu << "/40\n\n";
        
        cout << "=== ISI DEK SAAT INI ===\n";
        if (newDeck.cards.empty()) {
            cout << "  (Dek masih kosong)\n\n";
        } else {
            vector<string> hIsi = {"ID", "Nama Kartu", "Qty"};
            vector<vector<string>> rIsi;
            for (auto& dc : newDeck.cards) {
                string nama = getNamaKartu(plants, zombies, dc.cardId, newDeck.isPlant);
                rIsi.push_back({to_string(dc.cardId), nama, to_string(dc.qty)});
            }
            printTable(hIsi, rIsi);
            cout << "\n";
        }

        cout << "=== KARTU TERSEDIA ===\n";
        vector<string> headerCard = {"No", "Nama Kartu", "Class", "Cost", "Type"};
        vector<vector<string>> rowCard;
        for (int i = 0; i < (int)kartuTersedia.size(); i++) {
            rowCard.push_back({
                to_string(i + 1), kartuTersedia[i].name, kartuTersedia[i].cardClass,
                to_string(kartuTersedia[i].cost), kartuTersedia[i].category
            });
        }
        printTable(headerCard, rowCard);
    
        cout << "  [0] Selesai & Simpan\n";
        int pilihKartu = readInt("  Pilih nomor kartu: ");
        if (pilihKartu == 0) break; 

        if (pilihKartu < 1 || pilihKartu > (int)kartuTersedia.size()) {
            cout << "  [!] Nomor tidak valid.\n";
            tungguEnter();
            continue;
        }

        Card kartuTerpilih = kartuTersedia[pilihKartu - 1];
        int qty = readInt("  Masukkan jumlah (1-4): ",1,4);

        // if (qty < 1 || qty > 4) {
        //     cout << "  [!] Masukkan jumlah antara 1-4!\n";
        //     tungguEnter();
        //     continue;
        // }

        if (totalKartu + qty > 40) {
            cout << "  [!] Slot tidak cukup (Sisa: " << (40 - totalKartu) << ").\n";
            tungguEnter();
            continue;
        }

        bool ketemu = false;
        for (auto& existingCard : newDeck.cards) {
            if (existingCard.cardId == kartuTerpilih.id) {
                if (existingCard.qty + qty > 4) {
                    cout << "  [!] Kartu '" << kartuTerpilih.name 
                        << "' sudah ada " << existingCard.qty << " di dek.\n";
                    cout << "     Maksimal 4 kartu sejenis per dek. Sisa slot: " 
                        << (4 - existingCard.qty) << "\n";
                    tungguEnter();
                    ketemu = true;
                    break;
                }
                existingCard.qty += qty;
                totalKartu += qty;
                cout << "  [+] '" << kartuTerpilih.name << "' ditambah " << qty 
                    << ". Total jenis kartu ini: " << existingCard.qty << "\n";
                tungguEnter();
                ketemu = true;
                break;
            }
        }
        
        if (!ketemu) {
            newDeck.cards.push_back({kartuTerpilih.id, qty});
            totalKartu += qty;
            cout << "  [+] '" << kartuTerpilih.name << "' ditambahkan (" << qty << " kartu).\n";
            tungguEnter();
        }
    }

    // Simpan dek
    newDeck.status = (totalKartu == 40) ? "final" : "draft";
    decks.push_back(newDeck);
    
    saveDeckCSV("deck.csv", decks);
    saveDeckCardsCSV("deckCard.csv", decks);
    
    cout << "  [Success] Dek '" << newDeck.deckName << "' disimpan sebagai " 
        << newDeck.status << " (" << totalKartu << "/40 kartu)!\n";
    tungguEnter();
    clear();
}

void tambahKartuDek(Deck* deckPtr, vector<Hero>& heroes, vector<Card>& plants, vector<Card>& zombies) {
    int totalBaru = 0;
    for (auto& c : deckPtr->cards) {
        totalBaru += c.qty;
    }

    // Cek apakah deck sudah penuh
    if (totalBaru >= 40) {
        cout << "  [!] Dek sudah penuh (40/40). Tidak bisa tambah kartu lagi!\n";
        tungguEnter();
        return;
    }

    // Ambil Hero untuk filter class
    Hero* heroRef = nullptr;
    for(auto& h : heroes) if(h.id == deckPtr->heroId) heroRef = &h;
    
    if (heroRef == nullptr) {
        cout << "  [!] Hero tidak ditemukan!\n";
        tungguEnter();
        return;
    }
    
    vector<string> hClasses = splitPipe(heroRef->classes);
    vector<Card>& pool = deckPtr->isPlant ? plants : zombies;
    vector<Card> tersedia;
    for (auto& c : pool) {
        for (auto& cls : hClasses) {
            if (c.cardClass == cls) { tersedia.push_back(c); break; }
        }
    }

    while (totalBaru < 40) {
        clear();
        cout << "  Mengisi Ulang Dek: " << deckPtr->deckName << "\n";
        cout << "  Jumlah Kartu: " << totalBaru << "/40\n\n";

        // Tampilkan kartu yang sudah ada di deck
        cout << "=== ISI DEK SAAT INI ===\n";
        if (deckPtr->cards.empty()) {
            cout << "  (Dek masih kosong)\n\n";
        } else {
            vector<string> hIsi = {"ID", "Nama Kartu", "Qty"};
            vector<vector<string>> rIsi;
            for (auto& dc : deckPtr->cards) {
                string nama = getNamaKartu(plants, zombies, dc.cardId, deckPtr->isPlant);
                rIsi.push_back({to_string(dc.cardId), nama, to_string(dc.qty)});
            }
            printTable(hIsi, rIsi);
            cout << "\n";
        }

        // Tampilkan kartu tersedia
        cout << "=== KARTU TERSEDIA ===\n";
        vector<string> hK = {"No", "Nama Kartu", "Class", "Cost"};
        vector<vector<string>> rK;
        for (int i = 0; i < (int)tersedia.size(); i++) {
            rK.push_back({to_string(i + 1), tersedia[i].name, tersedia[i].cardClass, to_string(tersedia[i].cost)});
        }
        printTable(hK, rK);

        // Input pilihan kartu
        cout << "  [0] Selesai & Simpan\n";
        int kartuPilih = readInt("  Pilih nomor kartu: ");
        if (kartuPilih == 0) break;
        
        if (kartuPilih < 1 || kartuPilih > (int)tersedia.size()) {
            cout << "  [!] Nomor tidak valid.\n";
            tungguEnter();
            continue;
        }

        int qty = readInt("  Masukkan jumlah (1-4): ", 1, 4);

        if (totalBaru + qty > 40) {
            cout << "  [!] Slot tidak cukup!\n";
            tungguEnter();
            continue;
        }

        // Cek duplikat dan tambah kartu
        bool ketemu = false;
        for (auto& existingCard : deckPtr->cards) {
            if (existingCard.cardId == tersedia[kartuPilih-1].id) {
                if (existingCard.qty + qty > 4) {
                    cout << "  [!] Maksimal 4 kartu sejenis per dek.\n";
                    ketemu = true;
                    break;
                }
                existingCard.qty += qty;
                totalBaru += qty;
                cout << "  [+] '" << tersedia[kartuPilih-1].name << "' ditambah " << qty 
                    << ". Total jenis ini: " << existingCard.qty << "\n";
                ketemu = true;
                break;
            }
        }
        
        // Jika belum ada, tambah kartu baru
        if (!ketemu) {
            deckPtr->cards.push_back({tersedia[kartuPilih-1].id, qty});
            totalBaru += qty;
            cout << "  [+] '" << tersedia[kartuPilih-1].name << "' ditambahkan (" << qty << " kartu).\n";
        }
        
        tungguEnter();
    }

    // Set status deck
    deckPtr->status = (totalBaru == 40) ? "final" : "draft";
    cout << "  [+] Isi dek berhasil diperbarui!\n";
}

void hapusKartuDariDek(Deck* d, vector<Card>& plants, vector<Card>& zombies) {
    if (d->cards.empty()) {
        cout << "  [!] Dek ini sudah kosong.\n";
        return;
    }

    while (true) {
        clear();
        cout << "=== HAPUS KARTU DARI DEK: " << d->deckName << " ===\n";
        
        // Tampilkan isi dek saat ini
        vector<string> hKartu = {"No", "Nama Kartu", "Qty"};
        vector<vector<string>> rKartu;
        for (int i = 0; i < (int)d->cards.size(); i++) {
            string nama = getNamaKartu(plants, zombies, d->cards[i].cardId, d->isPlant);
            rKartu.push_back({
                to_string(i + 1),
                nama,
                to_string(d->cards[i].qty)
            });
        }
        printTable(hKartu, rKartu);

        cout << "  [0] Batal\n";
        int pilih = readInt("  Pilih nomor kartu yang ingin dihapus: ");
        
        if (pilih == 0) return;
        if (pilih < 1 || pilih > (int)d->cards.size()) {
            cout << "  [!] Pilihan tidak valid.\n";
            tungguEnter();
            continue;
        }

        int indexKartu = pilih - 1;
        string namaKartu = getNamaKartu(plants, zombies, d->cards[indexKartu].cardId, d->isPlant);

        while (true) {

            clear();
            int Qty_Sekarang = d->cards[indexKartu].qty;
            cout << "\n Kartu : " << namaKartu << " (Jumlah saat ini : " << Qty_Sekarang << " ) \n";
            int Jumlah_Hapus = readInt("Masukan jumlah kartu yang ingin dihapus (0 = Batal) : ");

            if (Jumlah_Hapus == 0) break;

            if (Jumlah_Hapus < 0 || Jumlah_Hapus > Qty_Sekarang) {
                cout << "[!] Jumlah tidak valid.\n";
                system("pause");
                continue;;
            }

            if (Jumlah_Hapus == Qty_Sekarang) {
                d->cards.erase(d->cards.begin() + indexKartu);

            } else {
                clear();
                d->cards[indexKartu].qty -= Jumlah_Hapus;
                cout << " [-] Qty : " << namaKartu << " dihapus sebanyak : " << Jumlah_Hapus << ".\n";
            }

            // Hitung ulang total kartu untuk update status
            int total = 0;
            for (auto& c : d->cards) total += c.qty;
            d->status = (total == 40) ? "final" : "draft";

            clear();
            cout << "Status dek saat ini : " << d->status << " Total : " << total << "/40) \n";
            system("pause");
            break;
        }
        
        if (d->cards.empty()) return;
    }
}

void editDek(vector<Deck>& decks, vector<Hero>& heroes,
            vector<Card>& plants, vector<Card>& zombies,
            int ownerId) {
    // clear();
    
    decks = loadDeckCSV("deck.csv");
    loadDeckCardsCSV("deckCard.csv", decks);

    // Filter dek milik user
    vector<Deck*> milikSaya;
    for (auto& d : decks) {
        if (d.ownerId == ownerId) milikSaya.push_back(&d);
    }

    if (milikSaya.empty()) {
        clear();
        cout << "=== DEBUG EDIT DEK ===\n";
        cout << "Total dek di file: " << decks.size() << endl;
        cout << "OwnerID kamu: " << ownerId << endl;
        cout << "Pesan: Kamu tidak punya dek.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get(); // Gunakan cin.get() manual untuk memastikan berhenti
        return;
    }

    // Tampilkan Daftar Dek
    cout << "=== PILIH DEK UNTUK DIEDIT ===\n";
    vector<string> header = {"No", "Nama Dek", "Hero", "Status", "Total Kartu"};
    vector<vector<string>> rows;
    for (int i = 0; i < (int)milikSaya.size(); i++) {
        int hitungKartu = 0;
        for (auto& c : milikSaya[i]->cards) hitungKartu += c.qty;
        
        rows.push_back({
            to_string(i + 1),
            milikSaya[i]->deckName,
            getNamaHero(heroes, milikSaya[i]->heroId),
            milikSaya[i]->status,
            to_string(hitungKartu) + "/40"
        });
    }
    printTable(header, rows);

    cout << "  [0] Kembali\n";
    int pilih = readInt("  Pilih nomor dek: ");
    if (pilih == 0) return;
    if (pilih < 1 || pilih > (int)milikSaya.size()) {
        cout << "  [!] Pilihan tidak valid.\n";
        tungguEnter();
        return;
    }

    Deck* deckTerpilih = milikSaya[pilih - 1];

    // Menu Edit
    clear();
    cout << "=== EDIT DEK: " << deckTerpilih->deckName << " ===\n";
    string opsi[] = {"Ubah Nama Dek","Tambah Kartu","Hapus Kartu","Kembali"};
    int subPilih = tampilMenu("", opsi, 4);
    switch(subPilih) {
        case 1: {
            string namaBaru = readString("  Masukkan Nama Dek Baru: ");
            deckTerpilih->deckName = namaBaru;
            cout << "  [+] Nama dek berhasil diubah!\n";
            break;
        }
        case 2: {
            tambahKartuDek(deckTerpilih, heroes, plants, zombies);
            decks = loadDeckCSV("deck.csv");
            loadDeckCardsCSV("deckCard.csv", decks);
            break;
        }
        case 3: {
            hapusKartuDariDek(deckTerpilih, plants, zombies); break;
        }
        case 4: break; 
    }

    // Simpan Perubahan ke CSV
    saveDeckCSV("deck.csv", decks);
    saveDeckCardsCSV("deckCard.csv", decks);
    tungguEnter();
}

void hapusDek(vector<Deck>& decks, int ownerId) {
    clear();
    decks = loadDeckCSV("deck.csv");
    loadDeckCardsCSV("deckCard.csv", decks);

    while (true) {
        // clear();
        
        // Filter dek milik user saja
        vector<int> originalIndices; // Menyimpan index asli di vector 'decks'
        vector<vector<string>> rows;
        vector<string> header = {"No", "Nama Dek", "Status"};

        for (int i = 0; i < (int)decks.size(); i++) {
            if (decks[i].ownerId == ownerId) {
                originalIndices.push_back(i);
                rows.push_back({
                    to_string(originalIndices.size()),
                    decks[i].deckName,
                    decks[i].status
                });
            }
        }

        if (rows.empty()) {
            cout << "  [!] Kamu tidak memiliki dek untuk dihapus.\n";
            tungguEnter();
            return;
        }

        // Tampilkan daftar dek
        cout << "=== HAPUS DEK ===\n";
        printTable(header, rows);
        cout << "  [0] Kembali\n";
        
        int pilih = readInt("  Pilih nomor dek yang akan DIHAPUS PERMANEN: ");
        if (pilih == 0) return;

        if (pilih < 1 || pilih > (int)rows.size()) {
            cout << "  [!] Pilihan tidak valid.\n";
            tungguEnter();
            continue;
        }

        // Konfirmasi penghapusan
        int indexDiDecks = originalIndices[pilih - 1];
        string namaDek = decks[indexDiDecks].deckName;
        
        cout << "  [?] Yakin ingin menghapus dek '" << namaDek << "'? (y/n): ";
        char konfirmasi;
        cin >> konfirmasi;
        cin.ignore(1000, '\n');

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            decks.erase(decks.begin() + indexDiDecks);

            // Simpan perubahan ke file CSV
            saveDeckCSV("deck.csv", decks);
            saveDeckCardsCSV("deckCard.csv", decks);

            cout << "  [OK] Dek '" << namaDek << "' telah dihapus.\n";
            tungguEnter();
            clear();
            return;
        } else {
            cout << "  [!] Penghapusan dibatalkan.\n";
            tungguEnter();
        }
    }
}