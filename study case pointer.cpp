#include <iostream> 
using namespace std;

int main() {

    int n; // jumlah elemen

    cout << "Masukkan jumlah data: "; // menginput panjang array
    cin >> n; // jumlah

    int *ptr = new int[n]; // membuat array dinamis

    // menginput data
    for(int i = 0; i < n; i++) {
        cout << "Nilai ke-" << i + 1 << " : "; // meminta nilai
        cin >> *(ptr + i); // mengisi array pakai pointer
    }

    cout << "\nIsi array: "; // menampilkan isi array

    // mencetak tanpa index langsung
    for(int i = 0; i < n; i++) {
        cout << *(ptr + i) << " "; // mengakses dengan pointer
    }

    int max = *ptr; // nilai awal max
    int min = *ptr; // nilai awal min
    int jumlah = 0; // total jumlah

    // mencari max, min, dan jumlah
    for(int i = 0; i < n; i++) {

        if(*(ptr + i) > max) // cek maksimum
            max = *(ptr + i);

        if(*(ptr + i) < min) // cek minimum
            min = *(ptr + i);

        jumlah += *(ptr + i); // tambah ke total
    }

    float rata = (float)jumlah / n; // menghitung rata-rata

    cout << "\n\nNilai maksimum : " << max;
    cout << "\nNilai minimum  : " << min;
    cout << "\nJumlah         : " << jumlah;
    cout << "\nRata-rata      : " << rata;

    return 0; // selesai
}
