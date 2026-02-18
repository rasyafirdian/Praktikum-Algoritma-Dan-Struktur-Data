#include <iostream> 
using namespace std;

int main() {

    int n; // jumlah elemen

    cout << "Masukkan jumlah data: "; // input panjang array
    cin >> n; // simpan jumlah

    int *ptr = new int[n]; // membuat array dinamis

    // input data
    for(int i = 0; i < n; i++) {
        cout << "Nilai ke-" << i + 1 << " : "; // minta nilai
        cin >> *(ptr + i); // isi array pakai pointer
    }

    cout << "\nIsi array: "; // tampilkan isi array

    // cetak tanpa index langsung
    for(int i = 0; i < n; i++) {
        cout << *(ptr + i) << " "; // akses dengan pointer
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

    float rata = (float)jumlah / n; // hitung rata-rata

    cout << "\n\nNilai maksimum : " << max;
    cout << "\nNilai minimum  : " << min;
    cout << "\nJumlah         : " << jumlah;
    cout << "\nRata-rata      : " << rata;

    return 0; // selesai
}
