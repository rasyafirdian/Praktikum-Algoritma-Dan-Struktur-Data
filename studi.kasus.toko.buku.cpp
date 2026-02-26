#include <iostream>
#include <string>
using namespace std;

struct Buku {
    string nama;
    int harga;
};

int main() {

    Buku toko[5] = {
        {"algoritma struktur data", 75000},
        {"manejemen basis Data", 85000},
        {"kalkulus", 90000},
        {"pemrograman web dasar", 95000},
        {"pengantar bisnis", 100000}
    };

    string cari;
    int pilihan;
    bool found = false; // penanda apakah buku ketemu atau nggak

    // Input nama buku yang mau dicari
    cout << "Masukkan nama buku yang dicari: ";
    getline(cin, cari);

    // Pilih metode pencarian
    cout << "\nPilih metode pencarian:\n";
    cout << "1. Sequential Search\n";
    cout << "2. Binary Search\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    // SEQUENTIAL SEARCH
    if (pilihan == 1) {

        int i = 0; // mulai dari index pertama

        // ngecek satu-satu dari depan sampai akhir
        while (i < 5 && found == false) {

            // kalau nama buku sama dengan yang dicari
            if (toko[i].nama == cari)
                found = true; // tandain kalau ketemu
            else
                i++; // kalau belum ketemu, lanjut ke index berikutnya
        }

        // hasil akhir pencarian
        if (found)
            cout << "Harga buku: " << toko[i].harga << endl;
        else
            cout << "Buku tidak ditemukan.\n";
    }

    // BINARY SEARCH
    else if (pilihan == 2) {

        // karena binary search, data harus sudah urut
        int awal = 0;
        int akhir = 4;
        int tengah;

        // proses pencarian selama belum ketemu dan range masih ada
        while (!found && awal <= akhir) {

            // cari posisi tengah
            tengah = (awal + akhir) / 2;

            // kalau pas sama, berarti ketemu
            if (cari == toko[tengah].nama)
                found = true;

            // kalau lebih kecil dari tengah, geser ke kiri
            else if (cari < toko[tengah].nama)
                akhir = tengah - 1;

            // kalau lebih besar, geser ke kanan
            else
                awal = tengah + 1;
        }

        // hasil akhir
        if (found)
            cout << "Harga buku: " << toko[tengah].harga << endl;
        else
            cout << "Buku tidak ditemukan.\n";
    }

    // kalau user pilih selain 1 atau 2
    else {
        cout << " Maaf Pilihan tidak valid.\n";
    }

    return 0;
}
