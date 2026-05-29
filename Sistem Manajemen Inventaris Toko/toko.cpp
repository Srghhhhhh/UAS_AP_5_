#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};


void clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void cetakGaris(int lebar = 70) {
    cout << string(lebar, '-') << "\n";
}

bool kodeExists(const vector<Barang>& inventaris, const string& kode) {
    for (const auto& b : inventaris)
        if (b.kodeBarang == kode) return true;
    return false;
}


void cetakHeaderTabel() {
    cetakGaris();
    cout << left
         << setw(10) << "Kode"
         << setw(22) << "Nama Barang"
         << setw(16) << "Harga (Rp)"
         << setw(8)  << "Stok"
         << "\n";
    cetakGaris();
}


void cetakBaris(const Barang& b) {
    cout << left
         << setw(10) << b.kodeBarang
         << setw(22) << b.namaBarang
         << setw(16) << fixed << setprecision(0) << b.harga
         << setw(8)  << b.stok
         << "\n";
}


void tambahBarang(vector<Barang>& inventaris) {
    Barang baru;

    cout << "\n===== TAMBAH BARANG =====\n";

    // Kode barang (unik)
    while (true) {
        cout << "Kode Barang : ";
        cin >> baru.kodeBarang;
        if (baru.kodeBarang.empty()) {
            cout << "[ERROR] Kode tidak boleh kosong.\n";
        } else if (kodeExists(inventaris, baru.kodeBarang)) {
            cout << "[ERROR] Kode '" << baru.kodeBarang << "' sudah digunakan. Masukkan kode lain.\n";
        } else {
            break;
        }
    }
    clearBuffer();

    // Nama barang
    while (true) {
        cout << "Nama Barang : ";
        getline(cin, baru.namaBarang);
        if (!baru.namaBarang.empty()) break;
        cout << "[ERROR] Nama tidak boleh kosong.\n";
    }

    // Harga — tidak boleh negatif
    while (true) {
        cout << "Harga (Rp) : ";
        if (cin >> baru.harga && baru.harga >= 0) break;
        cin.clear();
        clearBuffer();
        cout << "[ERROR] Harga tidak valid. Masukkan angka >= 0.\n";
    }

    // Stok — tidak boleh negatif
    while (true) {
        cout << "Stok       : ";
        if (cin >> baru.stok && baru.stok >= 0) break;
        cin.clear();
        clearBuffer();
        cout << "[ERROR] Stok tidak valid. Masukkan angka >= 0.\n";
    }
    clearBuffer();

    inventaris.push_back(baru);
    cout << "[OK] Barang '" << baru.namaBarang << "' berhasil ditambahkan.\n";
}

void tampilkanSemuaBarang(const vector<Barang>& inventaris) {
    cout << "\n===== DAFTAR SEMUA BARANG =====\n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong.\n";
        return;
    }
    cetakHeaderTabel();
    for (const auto& b : inventaris)
        cetakBaris(b);
    cetakGaris();
    cout << "Total barang: " << inventaris.size() << " item.\n";
}

void cariBarangTermahal(const vector<Barang>& inventaris) {
    cout << "\n===== BARANG TERMAHAL =====\n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong.\n";
        return;
    }

    const Barang* termahal = &inventaris[0];
    for (const auto& b : inventaris)
        if (b.harga > termahal->harga)
            termahal = &b;

    cetakHeaderTabel();
    cetakBaris(*termahal);
    cetakGaris();
}

void hitungTotalNilai(const vector<Barang>& inventaris) {
    cout << "\n===== TOTAL NILAI INVENTARIS =====\n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong.\n";
        return;
    }

    double total = 0;
    for (const auto& b : inventaris)
        total += b.harga * b.stok;

    cout << fixed << setprecision(0);
    cout << "Total Nilai Inventaris: Rp " << total << "\n";
}

void cekRestock(const vector<Barang>& inventaris) {
    cout << "\n===== BARANG PERLU RESTOCK (Stok < 5) =====\n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong.\n";
        return;
    }

    bool ada = false;
    cetakHeaderTabel();
    for (const auto& b : inventaris) {
        if (b.stok < 5) {
            cetakBaris(b);
            ada = true;
        }
    }
    cetakGaris();

    if (!ada)
        cout << "Semua barang memiliki stok yang cukup (>= 5).\n";
}

void updateStok(vector<Barang>& inventaris) {
    cout << "\n===== UPDATE STOK BARANG =====\n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong.\n";
        return;
    }

    string kode;
    cout << "Masukkan Kode Barang: ";
    cin >> kode;
    clearBuffer();

    Barang* target = nullptr;
    for (auto& b : inventaris) {
        if (b.kodeBarang == kode) {
            target = &b;
            break;
        }
    }

    if (target == nullptr) {
        cout << "[ERROR] Barang dengan kode '" << kode << "' tidak ditemukan.\n";
        return;
    }

    cout << "Barang ditemukan: " << target->namaBarang
         << " | Stok saat ini: " << target->stok << "\n";
    cout << "Pilih operasi:\n"
         << "  1. Tambah stok  (+)\n"
         << "  2. Kurangi stok (-)\n"
         << "Pilihan: ";

    int pilihan;
    cin >> pilihan;

    int jumlah;
    while (true) {
        cout << "Jumlah: ";
        if (cin >> jumlah && jumlah > 0) break;
        cin.clear();
        clearBuffer();
        cout << "[ERROR] Jumlah harus bilangan bulat positif.\n";
    }
    clearBuffer();

    int* pStok = &(target->stok);

    if (pilihan == 1) {
        *pStok += jumlah;
        cout << "[OK] Stok berhasil ditambah. Stok baru: " << *pStok << "\n";
    } else if (pilihan == 2) {
        if (*pStok - jumlah < 0) {
            cout << "[ERROR] Pengurangan melebihi stok yang tersedia (" << *pStok << "). Operasi dibatalkan.\n";
        } else {
            *pStok -= jumlah;
            cout << "[OK] Stok berhasil dikurangi. Stok baru: " << *pStok << "\n";
        }
    } else {
        cout << "[ERROR] Pilihan tidak valid. Operasi dibatalkan.\n";
    }
}

void tampilkanMenu() {
    cout << "\n";
    cetakGaris(40);
    cout << "   SISTEM MANAJEMEN INVENTARIS TOKO\n";
    cetakGaris(40);
    cout << " 1. Tambah Barang\n";
    cout << " 2. Tampilkan Semua Barang\n";
    cout << " 3. Cari Barang Termahal\n";
    cout << " 4. Hitung Total Nilai Inventaris\n";
    cout << " 5. Cek Restock (Stok < 5)\n";
    cout << " 6. Update Stok\n";
    cout << " 7. Keluar\n";
    cetakGaris(40);
    cout << " Pilihan: ";
}

int main() {
    vector<Barang> inventaris;



    int pilihan = 0;

    while (true) {
        tampilkanMenu();

        if (!(cin >> pilihan)) {
            cin.clear();
            clearBuffer();
            cout << "[ERROR] Input tidak valid. Masukkan angka 1-7.\n";
            continue;
        }
        clearBuffer();

        // sebelum melihat tampilkan semua barang, tambahkan barang terlebih dahulu agar di output tidak kosong

        switch (pilihan) {
            case 1: tambahBarang(inventaris);       break;
            case 2: tampilkanSemuaBarang(inventaris); break;
            case 3: cariBarangTermahal(inventaris); break;
            case 4: hitungTotalNilai(inventaris);   break;
            case 5: cekRestock(inventaris);         break;
            case 6: updateStok(inventaris);         break;
            case 7:
                cout << "\nTerima kasih. Program selesai.\n";
                return 0;
            default:
                cout << "[ERROR] Pilihan tidak tersedia. Masukkan angka 1-7.\n";
        }
    }
}