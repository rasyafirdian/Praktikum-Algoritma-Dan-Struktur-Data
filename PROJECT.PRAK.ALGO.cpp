#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ======================================================
// STRUCT MOBIL (Single Linked List)
// ======================================================
struct Mobil {
    int id;
    string nama;
    string plat;
    int tahun;
    double harga;
    string status;
    int jumlahRental;
    Mobil* next;
};

Mobil* headMobil = NULL;

// ======================================================
// CUSTOMER
// ======================================================
struct Customer {
    int id;
    string nama;
    string hp;
    string alamat;
};

struct CustomerNode {
    Customer data;
    CustomerNode* next;
};

CustomerNode* headCustomer = NULL;

// ======================================================
// HISTORI (Double Linked List)
// ======================================================
struct Histori {
    string customer;
    string mobil;
    int lama;
    double total;

    Histori* prev;
    Histori* next;
};

Histori* headHistori = NULL;
Histori* tailHistori = NULL;

// ======================================================
// STACK
// ======================================================
struct StackNode {
    string aktivitas;
    StackNode* next;
};

StackNode* topStack = NULL;

// ======================================================
// QUEUE
// ======================================================
struct QueueNode {
    string namaCustomer;
    QueueNode* next;
};

QueueNode* frontQueue = NULL;
QueueNode* rearQueue = NULL;

// ======================================================
// BST
// ======================================================
struct BSTNode {
    int id;
    string nama;

    BSTNode* left;
    BSTNode* right;
};

BSTNode* rootBST = NULL;

// ======================================================
// INPUT VALIDATION
// ======================================================
int inputAngka() {
    int angka;

    while (!(cin >> angka)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input harus angka: ";
    }

    return angka;
}

// ======================================================
// STACK
// ======================================================
void pushStack(string aktivitas) {
    StackNode* baru = new StackNode;
    baru->aktivitas = aktivitas;
    baru->next = topStack;
    topStack = baru;
}

void popStack() {
    if (topStack == NULL) {
        cout << "Undo kosong\n";
        return;
    }

    cout << "Undo: " << topStack->aktivitas << endl;

    StackNode* hapus = topStack;
    topStack = topStack->next;
    delete hapus;
}

// ======================================================
// QUEUE
// ======================================================
void enqueue(string nama) {
    QueueNode* baru = new QueueNode;
    baru->namaCustomer = nama;
    baru->next = NULL;

    if (frontQueue == NULL) {
        frontQueue = rearQueue = baru;
    } else {
        rearQueue->next = baru;
        rearQueue = baru;
    }
}

void tampilQueue() {
    QueueNode* temp = frontQueue;

    if (temp == NULL) {
        cout << "Queue kosong\n";
        return;
    }

    while (temp != NULL) {
        cout << temp->namaCustomer << endl;
        temp = temp->next;
    }
}

// ======================================================
// BST
// ======================================================
BSTNode* insertBST(BSTNode* root, int id, string nama) {
    if (root == NULL) {
        BSTNode* baru = new BSTNode;
        baru->id = id;
        baru->nama = nama;
        baru->left = NULL;
        baru->right = NULL;
        return baru;
    }

    if (id < root->id)
        root->left = insertBST(root->left, id, nama);
    else
        root->right = insertBST(root->right, id, nama);

    return root;
}

BSTNode* cariBST(BSTNode* root, int id) {
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return cariBST(root->left, id);

    return cariBST(root->right, id);
}

// ======================================================
// LOGIN
// ======================================================
bool login() {

    string user, pass;

    cout << "Username: ";
    cin >> user;

    cout << "Password: ";
    cin >> pass;

    if (user == "admin" && pass == "123")
        return true;

    return false;
}

// ======================================================
// TAMBAH MOBIL
// ======================================================
void tambahMobil() {

    Mobil* baru = new Mobil;

    cout << "ID Mobil: ";
    baru->id = inputAngka();
    cin.ignore();

    cout << "Nama Mobil: ";
    getline(cin, baru->nama);

    cout << "Plat: ";
    getline(cin, baru->plat);

    cout << "Tahun: ";
    baru->tahun = inputAngka();

    cout << "Harga: ";
    cin >> baru->harga;

    baru->status = "Tersedia";
    baru->jumlahRental = 0;
    baru->next = NULL;

    if (headMobil == NULL) {
        headMobil = baru;
    } else {

        Mobil* temp = headMobil;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = baru;
    }

    rootBST = insertBST(rootBST, baru->id, baru->nama);

    pushStack("Tambah Mobil");

    cout << "Mobil ditambahkan\n";
}

// ======================================================
// TAMPIL MOBIL
// ======================================================
void tampilMobil() {

    Mobil* temp = headMobil;

    if (temp == NULL) {
        cout << "Data kosong\n";
        return;
    }

    while (temp != NULL) {

        cout << "-------------------\n";
        cout << "ID      : " << temp->id << endl;
        cout << "Nama    : " << temp->nama << endl;
        cout << "Plat    : " << temp->plat << endl;
        cout << "Tahun   : " << temp->tahun << endl;
        cout << "Harga   : " << temp->harga << endl;
        cout << "Status  : " << temp->status << endl;

        temp = temp->next;
    }
}

// ======================================================
// EDIT MOBIL
// ======================================================
void editMobil() {

    int id;

    cout << "ID Mobil: ";
    cin >> id;

    Mobil* temp = headMobil;

    while (temp != NULL) {

        if (temp->id == id) {

            cin.ignore();

            cout << "Nama baru: ";
            getline(cin, temp->nama);

            cout << "Plat baru: ";
            getline(cin, temp->plat);

            cout << "Tahun baru: ";
            cin >> temp->tahun;

            cout << "Harga baru: ";
            cin >> temp->harga;

            pushStack("Edit Mobil");

            cout << "Berhasil edit\n";
            return;
        }

        temp = temp->next;
    }

    cout << "Mobil tidak ditemukan\n";
}

// ======================================================
// HAPUS MOBIL
// ======================================================
void hapusMobil() {

    int id;

    cout << "ID Mobil: ";
    cin >> id;

    Mobil* temp = headMobil;
    Mobil* prev = NULL;

    while (temp != NULL) {

        if (temp->id == id) {

            if (prev == NULL)
                headMobil = temp->next;
            else
                prev->next = temp->next;

            delete temp;

            pushStack("Hapus Mobil");

            cout << "Mobil dihapus\n";
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "Mobil tidak ditemukan\n";
}

// ======================================================
// SEARCH
// ======================================================
void cariMobilLinear() {

    int id;

    cout << "ID Cari: ";
    cin >> id;

    Mobil* temp = headMobil;

    while (temp != NULL) {

        if (temp->id == id) {
            cout << "Mobil ditemukan: " << temp->nama << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Tidak ditemukan\n";
}

// ======================================================
// SORT
// ======================================================
void bubbleSortHarga() {

    if (headMobil == NULL)
        return;

    bool swap;

    do {

        swap = false;

        Mobil* current = headMobil;

        while (current->next != NULL) {

            if (current->harga > current->next->harga) {

                std::swap(current->id, current->next->id);
                std::swap(current->nama, current->next->nama);
                std::swap(current->plat, current->next->plat);
                std::swap(current->tahun, current->next->tahun);
                std::swap(current->harga, current->next->harga);
                std::swap(current->status, current->next->status);

                swap = true;
            }

            current = current->next;
        }

    } while (swap);

    cout << "Sorting selesai\n";
}

// ======================================================
// HISTORI
// ======================================================
void tambahHistori(string customer, string mobil, int lama, double total) {

    Histori* baru = new Histori;

    baru->customer = customer;
    baru->mobil = mobil;
    baru->lama = lama;
    baru->total = total;

    baru->next = NULL;
    baru->prev = NULL;

    if (headHistori == NULL) {
        headHistori = tailHistori = baru;
    } else {
        tailHistori->next = baru;
        baru->prev = tailHistori;
        tailHistori = baru;
    }
}

void tampilHistori() {

    Histori* temp = headHistori;

    while (temp != NULL) {

        cout << "------------------\n";
        cout << "Customer : " << temp->customer << endl;
        cout << "Mobil    : " << temp->mobil << endl;
        cout << "Lama     : " << temp->lama << endl;
        cout << "Total    : " << temp->total << endl;

        temp = temp->next;
    }
}

// ======================================================
// RENTAL
// ======================================================
void rentalMobil() {

    string customer;
    int id, lama;

    cin.ignore();

    cout << "Nama Customer: ";
    getline(cin, customer);

    cout << "ID Mobil: ";
    cin >> id;

    Mobil* temp = headMobil;

    while (temp != NULL) {

        if (temp->id == id) {

            if (temp->status == "Disewa") {

                cout << "Mobil sedang disewa\n";
                enqueue(customer);
                return;
            }

            cout << "Lama Rental: ";
            cin >> lama;

            double total = lama * temp->harga;

            temp->status = "Disewa";
            temp->jumlahRental++;

            tambahHistori(customer, temp->nama, lama, total);

            pushStack("Rental");

            cout << "Total bayar: " << total << endl;

            return;
        }

        temp = temp->next;
    }

    cout << "Mobil tidak ditemukan\n";
}

// ======================================================
// PENGEMBALIAN
// ======================================================
void pengembalianMobil() {

    int id;

    cout << "ID Mobil: ";
    cin >> id;

    Mobil* temp = headMobil;

    while (temp != NULL) {

        if (temp->id == id) {

            temp->status = "Tersedia";

            cout << "Mobil dikembalikan\n";
            return;
        }

        temp = temp->next;
    }
}

// ======================================================
// CUSTOMER
// ======================================================
void tambahCustomer() {

    CustomerNode* baru = new CustomerNode;

    cout << "ID Customer: ";
    cin >> baru->data.id;
    cin.ignore();

    cout << "Nama: ";
    getline(cin, baru->data.nama);

    cout << "HP: ";
    getline(cin, baru->data.hp);

    cout << "Alamat: ";
    getline(cin, baru->data.alamat);

    baru->next = NULL;

    if (headCustomer == NULL)
        headCustomer = baru;
    else {

        CustomerNode* temp = headCustomer;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = baru;
    }

    cout << "Customer ditambahkan\n";
}

// ======================================================
// FILE SAVE
// ======================================================
void saveData() {

    ofstream file("mobil.txt");

    Mobil* temp = headMobil;

    while (temp != NULL) {

        file << temp->id << "|";
        file << temp->nama << "|";
        file << temp->plat << "|";
        file << temp->tahun << "|";
        file << temp->harga << "|";
        file << temp->status << "|";
        file << temp->jumlahRental << endl;

        temp = temp->next;
    }

    file.close();
}

// ======================================================
// STATISTIK
// ======================================================
void statistik() {

    int tersedia = 0;
    int disewa = 0;

    Mobil* temp = headMobil;

    while (temp != NULL) {

        if (temp->status == "Tersedia")
            tersedia++;
        else
            disewa++;

        temp = temp->next;
    }

    cout << "Mobil tersedia: " << tersedia << endl;
    cout << "Mobil disewa: " << disewa << endl;
}

// ======================================================
// MENU
// ======================================================
void menu() {

    bool loginStatus = false;
    int pilih;

    do {

        if (!loginStatus) {

            cout << "\n===== LOGIN =====\n";
            cout << "1. Login Admin\n";
            cout << "0. Keluar\n";

            cout << "Pilih: ";
            cin >> pilih;

            switch (pilih) {

            case 1:
                if (login()) {
                    loginStatus = true;
                    cout << "Login berhasil\n";
                } else {
                    cout << "Login gagal\n";
                }
                break;

            case 0:
                cout << "Program selesai\n";
                break;
            }

        } else {

            cout << "\n===== RENTAL MOBIL =====\n";
            cout << "1. Tambah Mobil\n";
            cout << "2. Tampil Mobil\n";
            cout << "3. Edit Mobil\n";
            cout << "4. Hapus Mobil\n";
            cout << "5. Cari Mobil\n";
            cout << "6. Sorting Harga\n";
            cout << "7. Rental Mobil\n";
            cout << "8. Pengembalian\n";
            cout << "9. Histori\n";
            cout << "10. Statistik\n";
            cout << "11. Tambah Customer\n";
            cout << "12. Queue\n";
            cout << "13. Undo\n";
            cout << "14. Save Data\n";
            cout << "15. Logout\n";
            cout << "0. Keluar\n";

            cout << "Pilih: ";
            cin >> pilih;

            switch (pilih) {

            case 1:
                tambahMobil();
                break;

            case 2:
                tampilMobil();
                break;

            case 3:
                editMobil();
                break;

            case 4:
                hapusMobil();
                break;

            case 5:
                cariMobilLinear();
                break;

            case 6:
                bubbleSortHarga();
                break;

            case 7:
                rentalMobil();
                break;

            case 8:
                pengembalianMobil();
                break;

            case 9:
                tampilHistori();
                break;

            case 10:
                statistik();
                break;

            case 11:
                tambahCustomer();
                break;

            case 12:
                tampilQueue();
                break;

            case 13:
                popStack();
                break;

            case 14:
                saveData();
                break;

            case 15:
                loginStatus = false;
                cout << "Logout berhasil\n";
                break;

            case 0:
                cout << "Program selesai\n";
                break;
            }
        }

    } while (pilih != 0);
}

// ======================================================
// MAIN
// ======================================================
int main() {

    menu();

    return 0;
}
