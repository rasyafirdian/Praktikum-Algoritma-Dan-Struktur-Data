#include <iostream>
#include <queue>
#include <stack>
#include <cstdlib>

using namespace std;

// ================= STRUCT =================

struct Kendaraan {
    string nopol, pemilik, status;
};

struct Node {
    Kendaraan data;
    Node *left, *right;
};

struct Riwayat {
    string aksi, nopol;
};

// ================= GLOBAL =================

Node* root = NULL;

queue<string> antrian;
stack<Riwayat> undoStack;

int kapasitas = 2;
int jumlahParkir = 0;

// ================= FUNCTION TAMBAHAN =================

// Membersihkan layar
void cls() {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Pause program
void pause() {

    cout << "\nTekan ENTER untuk lanjut...";
    cin.get();
}

// ================= BST =================

// Membuat node baru
Node* buatNode(string nopol, string pemilik) {

    Node* baru = new Node;

    baru->data.nopol = nopol;
    baru->data.pemilik = pemilik;
    baru->data.status = "Di Luar Parkiran";

    baru->left = baru->right = NULL;

    return baru;
}

// Menambahkan data ke BST
Node* insert(Node* root, string nopol, string pemilik) {

    if (root == NULL)
        return buatNode(nopol, pemilik);

    if (nopol < root->data.nopol)
        root->left = insert(root->left, nopol, pemilik);

    else if (nopol > root->data.nopol)
        root->right = insert(root->right, nopol, pemilik);

    return root;
}

// Mencari kendaraan berdasarkan nopol
Node* cari(Node* root, string nopol) {

    if (root == NULL || root->data.nopol == nopol)
        return root;

    if (nopol < root->data.nopol)
        return cari(root->left, nopol);

    return cari(root->right, nopol);
}

// Menampilkan data kendaraan
void inorder(Node* root) {

    if (root != NULL) {

        inorder(root->left);

        cout << "No Polisi : " << root->data.nopol << endl;
        cout << "Pemilik   : " << root->data.pemilik << endl;
        cout << "Status    : " << root->data.status << endl;
        cout << "============================\n";

        inorder(root->right);
    }
}

// Mencari node terkecil
Node* cariMin(Node* root) {

    while (root->left != NULL)
        root = root->left;

    return root;
}

// Menghapus kendaraan
Node* hapus(Node* root, string nopol) {

    if (root == NULL)
        return NULL;

    if (nopol < root->data.nopol)
        root->left = hapus(root->left, nopol);

    else if (nopol > root->data.nopol)
        root->right = hapus(root->right, nopol);

    else {

        // Tidak punya anak
        if (root->left == NULL && root->right == NULL) {

            delete root;
            return NULL;
        }

        // Satu anak
        else if (root->left == NULL) {

            Node* temp = root->right;

            delete root;
            return temp;
        }

        else if (root->right == NULL) {

            Node* temp = root->left;

            delete root;
            return temp;
        }

        // Dua anak
        Node* temp = cariMin(root->right);

        root->data = temp->data;

        root->right = hapus(root->right, temp->data.nopol);
    }

    return root;
}

// ================= MENU =================

// Tambah kendaraan
void tambahKendaraan() {

    cls();

    string nopol, pemilik;

    cout << "===== TAMBAH KENDARAAN =====\n";

    cout << "Nomor Polisi : ";
    getline(cin, nopol);

    // Validasi duplikat
    if (cari(root, nopol) != NULL) {

        cout << "\nNomor polisi sudah terdaftar!\n";

        pause();
        return;
    }

    cout << "Nama Pemilik : ";
    getline(cin, pemilik);

    root = insert(root, nopol, pemilik);

    cout << "\nData kendaraan berhasil ditambahkan\n";

    pause();
}

// Tampil kendaraan
void tampilKendaraan() {

    cls();

    cout << "===== DATA KENDARAAN =====\n\n";

    if (root == NULL)
        cout << "Data kosong\n";

    else
        inorder(root);

    pause();
}

// Kendaraan masuk
void kendaraanMasuk() {

    cls();

    string nopol;

    cout << "===== KENDARAAN MASUK =====\n";

    cout << "Nomor Polisi : ";
    getline(cin, nopol);

    Node* kendaraan = cari(root, nopol);

    if (kendaraan == NULL) {

        cout << "\nKendaraan tidak ditemukan!\n";

        pause();
        return;
    }

    if (kendaraan->data.status == "Di Parkiran") {

        cout << "\nKendaraan sudah di parkiran\n";

        pause();
        return;
    }

    // Jika parkiran tersedia
    if (jumlahParkir < kapasitas) {

        kendaraan->data.status = "Di Parkiran";

        jumlahParkir++;

        undoStack.push({"masuk", nopol});

        cout << "\nKendaraan berhasil masuk\n";
    }

    // Jika parkiran penuh
    else {

        antrian.push(nopol);

        cout << "\nParkiran penuh, kendaraan masuk antrian\n";
    }

    pause();
}

// Kendaraan keluar
void kendaraanKeluar() {

    cls();

    string nopol;

    cout << "===== KENDARAAN KELUAR =====\n";

    cout << "Nomor Polisi : ";
    getline(cin, nopol);

    Node* kendaraan = cari(root, nopol);

    if (kendaraan == NULL) {

        cout << "\nKendaraan tidak ditemukan!\n";

        pause();
        return;
    }

    if (kendaraan->data.status == "Di Luar Parkiran") {

        cout << "\nKendaraan sudah di luar parkiran\n";

        pause();
        return;
    }

    kendaraan->data.status = "Di Luar Parkiran";

    if (jumlahParkir > 0)
        jumlahParkir--;

    undoStack.push({"keluar", nopol});

    cout << "\nKendaraan berhasil keluar\n";

    // Kendaraan dari antrian masuk otomatis
    if (!antrian.empty()) {

        string next = antrian.front();
        antrian.pop();

        Node* nextKendaraan = cari(root, next);

        nextKendaraan->data.status = "Di Parkiran";

        jumlahParkir++;

        cout << "Kendaraan berikutnya masuk dari antrian\n";
    }

    pause();
}

// Hapus kendaraan
void hapusKendaraan() {

    cls();

    string nopol;

    cout << "===== HAPUS KENDARAAN =====\n";

    cout << "Nomor Polisi : ";
    getline(cin, nopol);

    Node* cek = cari(root, nopol);

    if (cek == NULL) {

        cout << "\nKendaraan tidak ditemukan!\n";
    }

    else {

        // Tidak boleh hapus jika masih parkir
        if (cek->data.status == "Di Parkiran") {

            cout << "\nKendaraan masih di parkiran!\n";
        }

        else {

            root = hapus(root, nopol);

            cout << "\nData kendaraan berhasil dihapus\n";
        }
    }

    pause();
}

// Undo aksi terakhir
void undoAksi() {

    cls();

    cout << "===== UNDO =====\n\n";

    if (undoStack.empty()) {

        cout << "Tidak ada aksi untuk di-undo\n";

        pause();
        return;
    }

    Riwayat last = undoStack.top();
    undoStack.pop();

    Node* kendaraan = cari(root, last.nopol);

    if (last.aksi == "masuk") {

        kendaraan->data.status = "Di Luar Parkiran";

        if (jumlahParkir > 0)
            jumlahParkir--;

        cout << "Undo: Kendaraan keluar dari parkiran\n";
    }

    else {

        kendaraan->data.status = "Di Parkiran";

        jumlahParkir++;

        cout << "Undo: Kendaraan masuk kembali ke parkiran\n";
    }

    pause();
}

// Tampil antrian
void tampilAntrian() {

    cls();

    cout << "===== ANTRIAN =====\n\n";

    if (antrian.empty()) {

        cout << "Antrian kosong\n";

        pause();
        return;
    }

    queue<string> temp = antrian;

    while (!temp.empty()) {

        cout << temp.front()
             << " menunggu giliran masuk parkiran\n";

        temp.pop();
    }

    pause();
}

// ================= MAIN =================

int main() {

    int pilih;

    do {

        cls();

        cout << "=================================\n";
        cout << "   SISTEM PARKIR BANDARA GSA\n";
        cout << "=================================\n";
        cout << "1. Tambah Kendaraan\n";
        cout << "2. Tampil Kendaraan\n";
        cout << "3. Kendaraan Masuk\n";
        cout << "4. Kendaraan Keluar\n";
        cout << "5. Hapus Kendaraan\n";
        cout << "6. Undo\n";
        cout << "7. Tampil Antrian\n";
        cout << "0. Keluar\n";
        cout << "=================================\n";
        cout << "Pilih Menu : ";

        cin >> pilih;
        cin.ignore(1000, '\n');

        switch (pilih) {

            case 1:
                tambahKendaraan();
                break;

            case 2:
                tampilKendaraan();
                break;

            case 3:
                kendaraanMasuk();
                break;

            case 4:
                kendaraanKeluar();
                break;

            case 5:
                hapusKendaraan();
                break;

            case 6:
                undoAksi();
                break;

            case 7:
                tampilAntrian();
                break;

            case 0:
                cout << "\nProgram selesai...\n";
                break;

            default:
                cout << "\nMenu tidak tersedia!\n";
                pause();
        }

    } while (pilih != 0);

    return 0;
}
