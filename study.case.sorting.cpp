#include <iostream>
#include <string>
using namespace std;

// fungsi untuk menampilkan data
void tampilData(string data[], int jumlah) {
    for(int i = 0; i < jumlah; i++) {
        cout << data[i] << endl;
    }
}

// Bubble Sort untuk ascending (A-Z)
void bubbleSort(string data[], int jumlah) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = 0; j < jumlah - i - 1; j++) {
            if(data[j] > data[j + 1]) {
                string sementara = data[j];
                data[j] = data[j + 1];
                data[j + 1] = sementara;
            }
        }
    }
}

// Quick Sort untuk descending (Z-A)
void quick_sort(string data[], int awal, int akhir) {
    int kiri = awal;
    int kanan = akhir;
    string pivot = data[(awal + akhir) / 2]; // ambil nilai tengah sebagai pivot

    while(kiri <= kanan) {

        // untuk descending dibalik operatornya
        while(data[kiri] > pivot)
            kiri++;

        while(data[kanan] < pivot)
            kanan--;

        if(kiri <= kanan) {
            string sementara = data[kiri];
            data[kiri] = data[kanan];
            data[kanan] = sementara;
            kiri++;
            kanan--;
        }
    }

    // rekursif
    if(awal < kanan)
        quick_sort(data, awal, kanan);

    if(kiri < akhir)
        quick_sort(data, kiri, akhir);
}

int main() {
    int jumlah;

    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlah;
    cin.ignore();

    string dataAsli[jumlah];
    string dataBubble[jumlah];
    string dataQuick[jumlah];

    // input nama mahasiswa
    for(int i = 0; i < jumlah; i++) {
        cout << "Masukkan nama mahasiswa ke-" << i + 1 << ": ";
        getline(cin, dataAsli[i]);

        // disalin supaya tidak merusak data asli
        dataBubble[i] = dataAsli[i];
        dataQuick[i] = dataAsli[i];
    }

    cout << "\nData sebelum diurutkan:" << endl;
    tampilData(dataAsli, jumlah);

    // urutkan ascending dengan bubble sort
    bubbleSort(dataBubble, jumlah);
    cout << "\nAscending (Bubble Sort):" << endl;
    tampilData(dataBubble, jumlah);

    // urutkan descending dengan quick sort
    quick_sort(dataQuick, 0, jumlah - 1);
    cout << "\nDescending (Quick Sort):" << endl;
    tampilData(dataQuick, jumlah);

    return 0;
}
