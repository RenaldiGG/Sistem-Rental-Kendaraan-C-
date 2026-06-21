#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 100;

// =====================================
// STRUCT KENDARAAN (ARRAY)
// =====================================
struct Kendaraan {
    string id;
    string nama;
    string plat;
    string jenis;
    int tahun;
    double harga;
};

Kendaraan kendaraan[MAX];
int jumlahKendaraan = 0;

// =====================================
// BST KENDARAAN
// =====================================
struct BSTNode {
    Kendaraan data;
    BSTNode *left, *right;

    BSTNode(Kendaraan k) {
        data = k;
        left = right = NULL;
    }
};

BSTNode* root = NULL;

BSTNode* insertBST(BSTNode* root, Kendaraan k) {
    if(root == NULL)
        return new BSTNode(k);

    if(k.id < root->data.id)
        root->left = insertBST(root->left, k);
    else if(k.id > root->data.id)
        root->right = insertBST(root->right, k);

    return root;
}

BSTNode* searchBST(BSTNode* root, string id) {
    if(root == NULL || root->data.id == id)
        return root;

    if(id < root->data.id)
        return searchBST(root->left, id);

    return searchBST(root->right, id);
}

BSTNode* cariMin(BSTNode* root) {
    while(root && root->left != NULL)
        root = root->left;

    return root;
}

BSTNode* hapusBST(BSTNode* root, string id) {

    if(root == NULL)
        return root;

    if(id < root->data.id)
        root->left = hapusBST(root->left, id);

    else if(id > root->data.id)
        root->right = hapusBST(root->right, id);

    else {

        if(root->left == NULL) {

            BSTNode* temp = root->right;
            delete root;
            return temp;
        }

        else if(root->right == NULL) {

            BSTNode* temp = root->left;
            delete root;
            return temp;
        }

        BSTNode* temp = cariMin(root->right);

        root->data = temp->data;

        root->right =
            hapusBST(root->right,
                     temp->data.id);
    }

    return root;
}

// =====================================
// QUEUE PENYEWA
// =====================================
struct Penyewa {
    string id;
    string nama;
};

struct Queue {
    Penyewa data[MAX];
    int front;
    int rear;
};

Queue antrean = {{},0,-1};

bool isQueueEmpty() {
    return antrean.rear < antrean.front;
}

void enqueue(Penyewa p) {
    antrean.rear++;
    antrean.data[antrean.rear] = p;
}

Penyewa dequeue() {
    return antrean.data[antrean.front++];
}

// =====================================
// STACK UNDO TRANSAKSI
// =====================================
struct Stack {
    string data[MAX];
    int top;
};

Stack undoStack = {{},-1};

void push(string aksi) {
    undoStack.data[++undoStack.top] = aksi;
}

void popUndo() {
    if(undoStack.top == -1){
        cout << "Tidak ada transaksi!\n";
        return;
    }

    cout << "Undo : "
         << undoStack.data[undoStack.top]
         << endl;

    undoStack.top--;
}

// =====================================
// LINKED LIST RIWAYAT
// =====================================
struct Riwayat {
    string penyewa;
    string id;
    string nama;
    string plat;
    string jenis;
    int tahun;
    double harga;
};

struct Node {
    Riwayat data;
    Node* next;
};

Node* head = NULL;

void tambahRiwayat(string penyewa,
                   Kendaraan k)
{
    Node* baru = new Node;

    baru->data.penyewa = penyewa;
    baru->data.id = k.id;
    baru->data.nama = k.nama;
    baru->data.plat = k.plat;
    baru->data.jenis = k.jenis;
    baru->data.tahun = k.tahun;
    baru->data.harga = k.harga;

    baru->next = head;
    head = baru;
}

void tampilRiwayat() {

Node* curr = head;

cout << "\n========================================================================================\n";
cout << left
     << setw(15) << "Penyewa"
     << setw(10) << "ID"
     << setw(20) << "Nama Kendaraan"
     << setw(12) << "Plat"
     << setw(12) << "Jenis"
     << setw(8) << "Tahun"
     << setw(10) << "Harga"
     << endl;

cout << "========================================================================================\n";

while(curr != NULL) {

    cout << left
         << setw(15) << curr->data.penyewa
         << setw(10) << curr->data.id
         << setw(20) << curr->data.nama
         << setw(12) << curr->data.plat
         << setw(12) << curr->data.jenis
         << setw(8) << curr->data.tahun
         << setw(10) << curr->data.harga
         << endl;

    curr = curr->next;
}

}

// =====================================
// GRAPH CABANG RENTAL
// =====================================
int graph[4][4] =
{
    {0,1,1,0},
    {1,0,0,1},
    {1,0,0,1},
    {0,1,1,0}
};

string cabang[4] =
{
    "Jakarta",
    "Bandung",
    "Bogor",
    "Bekasi"
};

void tampilGraph() {

    cout << "\n=== CABANG RENTAL ===\n";

    for(int i=0;i<4;i++){

        cout << cabang[i] << " -> ";

        for(int j=0;j<4;j++){

            if(graph[i][j]==1)
                cout << cabang[j] << " ";
        }

        cout << endl;
    }
}

// =====================================
// SORTING BUBBLE
// =====================================
void bubbleSortHarga() {

    for(int i=0;i<jumlahKendaraan-1;i++){

        for(int j=0;j<jumlahKendaraan-i-1;j++){

            if(kendaraan[j].harga >
               kendaraan[j+1].harga)
            {
                swap(kendaraan[j],
                     kendaraan[j+1]);
            }
        }
    }

    cout<<"Data berhasil diurutkan\n";
}

// =====================================
// TAMBAH KENDARAAN
// =====================================
void tambahKendaraan() {

    Kendaraan k;

    cout<<"\nID Kendaraan : ";
    cin>>k.id;

    cin.ignore();

    cout<<"Nama Kendaraan : ";
    getline(cin,k.nama);

    cout<<"Plat Nomor : ";
    getline(cin,k.plat);

    cout<<"Jenis : ";
    getline(cin,k.jenis);

    cout<<"Tahun : ";
    cin>>k.tahun;

    cout<<"Harga Sewa : ";
    cin>>k.harga;

    kendaraan[jumlahKendaraan++] = k;

    root = insertBST(root,k);

    cout<<"\nData Berhasil Ditambahkan\n";
}

int cariIndexById(string id) {

    for(int i = 0; i < jumlahKendaraan; i++) {

        if(kendaraan[i].id == id)
            return i;
    }

    return -1;
}

// =====================================
// EDIT KENDARAAN
// =====================================
void editKendaraan() {

    string idEdit;

    cout << "\nMasukkan ID Kendaraan yang akan diedit : ";
    cin >> idEdit;

    int index = cariIndexById(idEdit);

    if(index == -1) {

        cout << "\nData Tidak Ditemukan!\n";
        return;
    }

    cin.ignore();

    cout << "\n=== EDIT DATA KENDARAAN ===\n";

    cout << "Nama Kendaraan Baru : ";
    getline(cin, kendaraan[index].nama);

    cout << "Plat Nomor : ";
    getline(cin, kendaraan[index].plat);

    cout << "Jenis : ";
    getline(cin, kendaraan[index].jenis);

    cout << "Tahun : ";
    cin >> kendaraan[index].tahun;

    cout << "Harga Sewa : ";
    cin >> kendaraan[index].harga;

    root = hapusBST(root, idEdit);
    root = insertBST(root, kendaraan[index]);

    cout << "\nData Berhasil Diubah\n";
}

// =====================================
// HAPUS KENDARAAN
// =====================================
void hapusKendaraan() {

    string idHapus;

    cout << "\nMasukkan ID Kendaraan yang akan dihapus : ";
    cin >> idHapus;

    int index = cariIndexById(idHapus);

    if(index == -1) {

        cout << "\nData Tidak Ditemukan!\n";
        return;
    }

    for(int i = index; i < jumlahKendaraan - 1; i++) {

        kendaraan[i] = kendaraan[i + 1];
    }

    jumlahKendaraan--;

    root = hapusBST(root, idHapus);

    cout << "\nData Berhasil Dihapus\n";
}

// =====================================
// CARI KENDARAAN
// =====================================
void cariBST() {

    string id;

    cout << "\nMasukkan ID Kendaraan : ";
    cin >> id;

    BSTNode* hasil = searchBST(root, id);

    if(hasil == NULL) {

        cout << "\nData Tidak Ditemukan\n";
        return;
    }

    cout << "\n===== DATA DITEMUKAN =====\n";
    cout << "ID     : " << hasil->data.id << endl;
    cout << "Nama   : " << hasil->data.nama << endl;
    cout << "Plat   : " << hasil->data.plat << endl;
    cout << "Jenis  : " << hasil->data.jenis << endl;
    cout << "Tahun  : " << hasil->data.tahun << endl;
    cout << "Harga  : " << hasil->data.harga << endl;
}

// =====================================
// TAMPIL DATA
// =====================================
void tampilKendaraan() {

    cout<<"\n==================================================================\n";
    cout<<left
        <<setw(8)<<"ID"
        <<setw(20)<<"Nama"
        <<setw(12)<<"Plat"
        <<setw(12)<<"Jenis"
        <<setw(8)<<"Tahun"
        <<setw(10)<<"Harga"
        <<endl;

    cout<<"==================================================================\n";

    for(int i=0;i<jumlahKendaraan;i++){

        cout<<left
            <<setw(8)<<kendaraan[i].id
            <<setw(20)<<kendaraan[i].nama
            <<setw(12)<<kendaraan[i].plat
            <<setw(12)<<kendaraan[i].jenis
            <<setw(8)<<kendaraan[i].tahun
            <<setw(10)<<kendaraan[i].harga
            <<endl;
    }
}

// =====================================
// SEWA KENDARAAN
// =====================================
void sewaKendaraan() {

string namaPenyewa;
string idKendaraan;

cin.ignore();

cout << "\nNama Penyewa : ";
getline(cin, namaPenyewa);

cout << "ID Kendaraan : ";
getline(cin, idKendaraan);

BSTNode* hasil = searchBST(root, idKendaraan);

if(hasil == NULL) {

    cout << "\nKendaraan Tidak Ditemukan!\n";
    return;
}

cout << "\n===== DATA KENDARAAN =====\n";
cout << "ID     : " << hasil->data.id << endl;
cout << "Nama   : " << hasil->data.nama << endl;
cout << "Plat   : " << hasil->data.plat << endl;
cout << "Jenis  : " << hasil->data.jenis << endl;
cout << "Tahun  : " << hasil->data.tahun << endl;
cout << "Harga  : " << hasil->data.harga << endl;

tambahRiwayat(
    namaPenyewa,
    hasil->data
);

push("Sewa Kendaraan");

cout << "\nTransaksi Berhasil\n";

}


void inisialisasiData() {

    kendaraan[0].id = "K001";
    kendaraan[0].nama = "Toyota Avanza";
    kendaraan[0].plat = "D1234AA";
    kendaraan[0].jenis = "Mobil";
    kendaraan[0].tahun = 2022;
    kendaraan[0].harga = 350000;

    kendaraan[1].id = "K002";
    kendaraan[1].nama = "Honda Brio";
    kendaraan[1].plat = "D5678BB";
    kendaraan[1].jenis = "Mobil";
    kendaraan[1].tahun = 2023;
    kendaraan[1].harga = 300000;

    kendaraan[2].id = "K003";
    kendaraan[2].nama = "Mitsubishi Xpander";
    kendaraan[2].plat = "D9012CC";
    kendaraan[2].jenis = "Mobil";
    kendaraan[2].tahun = 2022;
    kendaraan[2].harga = 400000;

    kendaraan[3].id = "K004";
    kendaraan[3].nama = "Yamaha NMAX";
    kendaraan[3].plat = "D3456DD";
    kendaraan[3].jenis = "Motor";
    kendaraan[3].tahun = 2024;
    kendaraan[3].harga = 150000;

    kendaraan[4].id = "K005";
    kendaraan[4].nama = "Honda PCX";
    kendaraan[4].plat = "D7890EE";
    kendaraan[4].jenis = "Motor";
    kendaraan[4].tahun = 2023;
    kendaraan[4].harga = 175000;

    jumlahKendaraan = 5;

    for(int i = 0; i < jumlahKendaraan; i++) {
        root = insertBST(root, kendaraan[i]);
    }
}


// =====================================
// MAIN
// =====================================
int main() {

	inisialisasiData();
	
    int pilih;

    do {

        cout<<"\n";
        cout<<"===================================\n";
        cout<<" SISTEM RENTAL KENDARAAN\n";
        cout<<"===================================\n";

        cout<<"1.  Tambah Kendaraan\n";
        cout<<"2.  Edit Kendaraan\n";
        cout<<"3.  Hapus Kendaraan\n";
        cout<<"4.  Cari Kendaraan\n";
        cout<<"5.  Tampilkan Kendaraan\n";
        cout<<"6.  Urutkan Harga\n";
        cout<<"7.  Sewa Kendaraan\n";
        cout<<"8.  Riwayat Penyewaan\n";
        cout<<"9.  Undo Transaksi\n";
        cout<<"10. Cabang Rental\n";
        cout<<"0.  Keluar\n";

        cout<<"\nPilihan : ";
        cin>>pilih;

        switch(pilih){

        case 1:
            tambahKendaraan();
            break;

        case 2:
            editKendaraan();
            break;

        case 3:
            hapusKendaraan();
            break;
		
		case 4:
            cariBST();
            break;
            
        case 5:
            tampilKendaraan();
            break;
		
        case 6:
            bubbleSortHarga();
            break;

        case 7:
            sewaKendaraan();
            break;

        case 8:
            tampilRiwayat();
            break;

        case 9:
            popUndo();
            break;

        case 10:
            tampilGraph();
            break;
        }

    }while(pilih!=0);

    return 0;
}
