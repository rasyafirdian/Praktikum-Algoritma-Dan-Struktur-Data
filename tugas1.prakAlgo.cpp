#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Produk{
    char name[60];
    char category[30];
    double price;
    int stock;
    float rating;
};

Produk arr[100];
int n = 0;

// LOAD FILE
void loadFile(){
    FILE *pf = fopen("shopease_db.txt","r");

    if(pf == NULL){
        return;
    }

    while(fscanf(pf," %[^|]|%[^|]|%lf|%d|%f\n",
        arr[n].name,
        arr[n].category,
        &arr[n].price,
        &arr[n].stock,
        &arr[n].rating) != EOF){

        n++;
    }

    fclose(pf);
}

// SAVE FILE
void saveFile(){
    FILE *pf = fopen("shopease_db.txt","w");

    for(int i=0;i<n;i++){
        fprintf(pf,"%s|%s|%.0lf|%d|%.1f\n",
        arr[i].name,
        arr[i].category,
        arr[i].price,
        arr[i].stock,
        arr[i].rating);
    }

    fclose(pf);
}

// TAMBAH PRODUK
void tambahProduk(){

    if(n >= 100){
        cout<<"Data sudah penuh!\n";
        return;
    }

    cin.ignore();

    cout<<"Nama Produk : ";
    cin.getline(arr[n].name,60);

    cout<<"Kategori : ";
    cin.getline(arr[n].category,30);

    cout<<"Harga : ";
    cin>>arr[n].price;

    cout<<"Stok : ";
    cin>>arr[n].stock;

    cout<<"Rating : ";
    cin>>arr[n].rating;

    n++;

    saveFile();

    cout<<"Produk berhasil ditambahkan\n";
}

// BUBBLE SORT (NAMA ASC)
void bubbleSort(){
    Produk temp;

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){

            if(strcmp(arr[j].name,arr[j+1].name) > 0){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }

        }
    }
}

// QUICK SORT (RATING DESC)
void quickSort(int low, int high){

    int i = low;
    int j = high;
    float pivot = arr[(low+high)/2].rating;

    Produk temp;

    while(i <= j){

        while(arr[i].rating > pivot) i++;
        while(arr[j].rating < pivot) j--;

        if(i <= j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    if(low < j) quickSort(low, j);
    if(i < high) quickSort(i, high);
}

// TAMPIL PRODUK
void tampilProduk(){

    int pilih;

    cout<<"\n1. Urut Nama (Bubble Sort)";
    cout<<"\n2. Urut Rating (Quick Sort)";
    cout<<"\nPilih : ";
    cin>>pilih;

    if(pilih == 1){
        bubbleSort();
    }
    else if(pilih == 2){
        quickSort(0, n-1);
    }

    cout<<"\n-------------------------------------------------------------\n";
    cout<<"| Nama        | Kategori   | Harga     | Stok | Rating |\n";
    cout<<"-------------------------------------------------------------\n";

    for(int i=0;i<n;i++){
        printf("| %-10s | %-10s | %-9.0lf | %-4d | %-6.1f |\n",
        arr[i].name,
        arr[i].category,
        arr[i].price,
        arr[i].stock,
        arr[i].rating);
    }

    cout<<"-------------------------------------------------------------\n";
}

// CARI PRODUK (SEQUENTIAL)
void cariProduk(){

    char cari[60];
    bool ketemu = false;

    cin.ignore();

    cout<<"Masukkan nama produk : ";
    cin.getline(cari,60);

    for(int i=0;i<n;i++){

        if(strcmp(arr[i].name, cari) == 0){

            cout<<"\nProduk ditemukan\n";
            cout<<"Nama : "<<arr[i].name<<endl;
            cout<<"Kategori : "<<arr[i].category<<endl;
            cout<<"Harga : "<<arr[i].price<<endl;
            cout<<"Stok : "<<arr[i].stock<<endl;
            cout<<"Rating : "<<arr[i].rating<<endl;

            ketemu = true;
        }
    }

    if(!ketemu){
        cout<<"Produk tidak ditemukan!\n";
    }
}

// MAIN
int main(){

    loadFile();

    int menu;

    do{
        cout<<"\n=== SHOPEASE ===\n";
        cout<<"1. Tambah Produk\n";
        cout<<"2. Tampilkan Produk\n";
        cout<<"3. Cari Produk\n";
        cout<<"4. Keluar\n";

        cout<<"Pilih menu : ";
        cin>>menu;

        if(menu == 1){
            tambahProduk();
        }
        else if(menu == 2){
            tampilProduk();
        }
        else if(menu == 3){
            cariProduk();
        }

    }while(menu != 4);

    saveFile();

    cout<<"Terima kasih telah menggunakan program\n";

    return 0;
}
