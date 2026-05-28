#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>
using namespace std;

const int KAPASITAS_MAKS = 20;
const int TARIF_PER_MENIT = 2000;

struct Petugas
{
    string nama;
    string id;
};

class Mobil 
{
public:
    string plat;
    string merk;
    string warna;
    time_t waktuMasuk;

    Mobil(string p, string m, string w) {
        plat = p;
        merk = m;
        warna = w;
        waktuMasuk = time(0);
    }
};

void garis() {
    cout << "====================================================================\n";
}

void garisKecil() {
    cout << "--------------------------------------------------------------------\n";
}

void tampilanAwal(Petugas *petugas) 
{
    garis();
    cout << setw(45) << "S E L A M A T   D A T A N G\n";
    cout << setw(45) << "DI PORTAL PARKIR KHUSUS MOBIL\n";
    cout << setw(38) << "MALL PRIENAL\n";
    garis();

    cout << "\nKami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n\n";

    cout << "Masukkan nama : ";
    getline(cin, petugas->nama);

    cout << "Masukkan ID   : ";
    getline(cin, petugas->id);
}

void tampilanMenu(Petugas *petugas) 
{
    cout << "\nNama Petugas : " << petugas->nama << endl;
    cout << "ID Petugas   : " << petugas->id << endl;

    cout << "\n";
    cout << setw(45) << "TERIMA KASIH ATAS KERJASAMANYA !\n";
    cout << setw(43) << "S E L A M A T   B E R T U G A S\n";
    garis();

    cout << "\nSilahkan input opsi berikut dalam bentuk angka.\n";
    cout << "1. Tambahkan Daftar Kendaraan\n";
    cout << "2. Tampilkan Daftar Kendaraan\n";
    cout << "3. Pembayaran\n";
    cout << "4. Keluar Program\n";
    cout << "Masukkan opsi : ";
}

void tambahKendaraan(vector<Mobil> *daftarMobil) 
{
    int jumlah;

    cout << "Masukkan jumlah mobil yang akan di parkirkan : ";
    cin >> jumlah;
    cin.ignore();

    int sisaSlot = KAPASITAS_MAKS - daftarMobil->size();

    if (sisaSlot == 0) {
        cout << "Maaf, parkiran penuh!\n";
        return;
    }

    if (jumlah > sisaSlot) {
        cout << "Maaf, parkiran hanya dapat memuat " << sisaSlot << " mobil !\n";
        jumlah = sisaSlot;
    }

    for (int i = 0; i < jumlah; i++) 
    {
        string plat, merk, warna;

        cout << "\nMobil ke " << daftarMobil->size() + 1 << endl;

        cout << "Masukkan plat mobil  : ";
        getline(cin, plat);

        cout << "Masukkan merk mobil  : ";
        getline(cin, merk);

        cout << "Masukkan warna mobil : ";
        getline(cin, warna);

        Mobil mobilBaru(plat, merk, warna);

        
        Mobil *ptrMobil = &mobilBaru;

        daftarMobil->push_back(*ptrMobil);
    }

    cout << "\nData kendaraan berhasil ditambahkan.\n";
}

void tampilkanDaftar(vector<Mobil> *daftarMobil) 
{
    if (daftarMobil->empty()) {
        cout << "\nBelum ada mobil yang sedang parkir.\n";
        return;
    }

    cout << "\nDAFTAR MOBIL YANG SUDAH TERPARKIR :\n";
    garis();

    for (int i = 0; i < daftarMobil->size(); i++) {
        time_t waktuSekarang = time(0);
        double selisihDetik = difftime(waktuSekarang, daftarMobil->at(i).waktuMasuk);

        int jam = selisihDetik / 3600;
        int menit = ((int)selisihDetik % 3600) / 60;
        int detik = (int)selisihDetik % 60;

        cout << "Mobil ke-" << i + 1 << endl;
        cout << "Plat mobil   : " << daftarMobil->at(i).plat << endl;
        cout << "Merk mobil   : " << daftarMobil->at(i).merk << endl;
        cout << "Warna mobil  : " << daftarMobil->at(i).warna << endl;
        cout << "Waktu parkir : " << jam << " jam " << menit << " menit " << detik << " detik\n";

        garisKecil();
    }
}

int hitungBiaya(time_t waktuMasuk) 
{
    time_t waktuSekarang = time(0);
    double selisihDetik = difftime(waktuSekarang, waktuMasuk);

    int menit = selisihDetik / 60;

    if ((int)selisihDetik % 60 > 0) {
        menit++;
    }

    if (menit == 0) {
        menit = 1;
    }

    return menit * TARIF_PER_MENIT;
}

void pembayaran(vector<Mobil> *daftarMobil) 
{
    if (daftarMobil->empty()) {
        cout << "\nBelum ada mobil yang dapat dibayar.\n";
        return;
    }

    tampilkanDaftar(daftarMobil);

    string platBayar;
    cout << "\nMasukkan plat mobil yang ingin dibayar : ";
    getline(cin, platBayar);

    bool ditemukan = false;

    for (int i = 0; i < daftarMobil->size(); i++) 
    {
        if (daftarMobil->at(i).plat == platBayar) 
        {
            ditemukan = true;

            int biaya = hitungBiaya(daftarMobil->at(i).waktuMasuk);

            cout << "\nB I A Y A   P A R K I R : Rp" << biaya << endl;

            daftarMobil->erase(daftarMobil->begin() + i);

            cout << "Pembayaran berhasil.\n";
            cout << "Mobil dengan plat " << platBayar << " telah keluar dari parkiran.\n";

            break;
        }
    }

    if (!ditemukan) 
    {
        cout << "PLAT TIDAK DITEMUKAN !\n";
    }
}

#endif