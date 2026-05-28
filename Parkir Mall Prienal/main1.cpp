#include "main.h"

int main() 
{
    Petugas petugas;
    vector<Mobil> daftarMobil;

    int opsi;

    tampilanAwal(&petugas);

    do 
    {
        tampilanMenu(&petugas);
        cin >> opsi;
        cin.ignore();

        if (opsi == 1) {
            tambahKendaraan(&daftarMobil);
        }
        else if (opsi == 2) {
            tampilkanDaftar(&daftarMobil);
        }
        else if (opsi == 3) {
            pembayaran(&daftarMobil);
        }
        else if (opsi == 4) {
            cout << "\nTerima kasih, program selesai.\n";
        }
        else {
            cout << "\nOpsi tidak valid. Silahkan pilih 1 sampai 4.\n";
        }

    } 
    while (opsi != 4);

    return 0;
}