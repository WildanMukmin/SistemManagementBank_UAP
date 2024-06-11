#include "header.h"

// <------------------ Fungsi Fungsi Utama ------------------>

// class nasabah
class Nasabah{
    private:
    string nama, pin, noRek;
    unsigned long long int saldo;

    public:
    Nasabah(string nama, string pin, string noRek) : nama(nama), pin(pin), noRek(noRek) {
        string buatFile = "mkdir " + nama;
        system(buatFile.c_str());

        ofstream akun;
        akun.open("data/" + nama + "/userAkun.txt", ios::app);
        akun << nama;
        akun << pin;
        akun.close();

        ofstream nomorRekening;
        nomorRekening.open("data/" + nama + "/nomorRekening.txt", ios::app);
        nomorRekening << noRek;
        nomorRekening.close();
        
        ofstream saldo;
        saldo.open("data/" + nama + "/saldo.txt", ios::app);
        saldo << 0;
        saldo.close();
        
        ofstream riwayatTransaksiMasuk;
        riwayatTransaksiMasuk.open("data/" + nama + "/riwayatTransaksiMasuk.txt", ios::app);
        riwayatTransaksiMasuk << "Belum Ada Transaksi";
        riwayatTransaksiMasuk.close();
        
        ofstream riwayatTransaksiKeluar;
        riwayatTransaksiKeluar.open("data/" + nama + "/riwayatTransaksiKeluar.txt", ios::app);
        riwayatTransaksiKeluar << "Belum Ada Transaksi";
        riwayatTransaksiKeluar.close();

        // untuk masukin ke stack nya
        ofstream listPengguna;
        listPengguna.open("listPengguna.txt", ios::app);
        listPengguna << endl;
        listPengguna << nama;
        listPengguna.close();
        
    }
};

// pilihan buat akun
void createAkun() {
    string nama, pin;

    boxCreateAccount();

    linexy(71, 13); cin >> nama;
    linexy(71, 14); cin >> pin;

    deque<string> listPengguna = database();
    Nasabah(nama, pin, generateRandomNoRek(listPengguna.size()));

    listPengguna.push_back(nama);
    ofstream updateListPengguna("listPengguna.txt");
    for (size_t i = 0; i < listPengguna.size(); ++i) {
        updateListPengguna << listPengguna[i] << endl;
    }
    updateListPengguna.close();

    notifikasiAkunBerhasil(nama);
    getch();
}

// pilihan dari login
bool login(string nama, string pin){
	string output;

	ifstream verifikasi;
	verifikasi.open("data/" + nama + "/userAkun.txt"); // sesuain dengan lokasi
    verifikasi >> output;
    if (output == nama + pin) return true;
    verifikasi.close();
    return false;
}

// Generate Database
deque<string> database(){
    deque <string> listPengguna;
    ifstream checkListPengguna;
	checkListPengguna.open("listPengguna.txt");
    string data;
	while (!checkListPengguna.eof()){
		checkListPengguna >> data;
        listPengguna.push_back(data);
	}
	checkListPengguna.close();
    return listPengguna;
}
 
// Fungsi untuk menghasilkan nomor rekening acak
string generateRandomNoRek(int n){   
    for(int i = 0; i < n; i++){
        static random_device rd;
        static mt19937 gen(rd());
        static uniform_int_distribution<unsigned long long> dis(1000000000, 9999999999);

        // Menghasilkan nomor acak dan mengkonversinya ke string
        unsigned long long randomNumber = dis(gen);
        if(i == n - 1)return to_string(randomNumber);
    }
}

// Fungsi mengambil nomor rekening
string getNoRek(string nama){
	string output;

	ifstream verifikasi;
	verifikasi.open("data/" + nama + "/nomorRekening.txt"); // sesuain dengan lokasi
    verifikasi >> output;
    verifikasi.close();
    
    return output;
}

// Fungsi untuk mengambil saldo
long long unsigned int getSaldo(string nama){
	string output;

	ifstream verifikasi;
	verifikasi.open("data/" + nama + "/saldo.txt"); // sesuain dengan lokasi
    verifikasi >> output;
    verifikasi.close();
    
    return stoull(output);
}

// Funsgi untuk melakukan transfer
void transfer(string nama, deque<string> listPengguna){
      TRANSFER:
    system("cls");
    formTransfer();
    string noRekTujuan;
    linexy (35, 10); cin >> noRekTujuan;
    long long unsigned int nominalTransfer;
    linexy (35, 12);cin >> nominalTransfer;
    string namaTujuan;
    system("cls");


        ULANGIVERIFIKASIPIN:
    konfirTransfer();
    char konfirTransfer; 
    linexy (14, 6);cin >> konfirTransfer;
    if(konfirTransfer == 'y' || konfirTransfer == 'Y'){
        string pin;
        linexy(24,8); cin >> pin;
        system("cls");
        if(login(nama, pin)){
            strukPembayaran(nama, namaTujuan, nominalTransfer);
            system("cls");
        }else{
            salahPinTransfer();
            goto ULANGIVERIFIKASIPIN;
        }
    }else {
        batalTransfer();
        goto TRANSFER;
        return;
    }

    for(auto i : listPengguna){
        string output;
        
        ifstream verifikasi;
        verifikasi.open("data/" + i + "/nomorRekening.txt"); // sesuain dengan lokasi
        verifikasi >> output;
        verifikasi.close();

        if(output == noRekTujuan){
            namaTujuan = i;
            break;
        }
    }

    long long unsigned int saldoPengirim, saldoPenerima;
    saldoPengirim = getSaldo(nama);
    saldoPenerima = getSaldo(namaTujuan);

    saldoPengirim -= nominalTransfer;
    saldoPenerima += nominalTransfer;

    updateSaldo(nama, saldoPengirim);
    updateSaldo(namaTujuan, saldoPenerima);
    strukPembayaran(nama, namaTujuan, nominalTransfer);
    system("cls");
    updateRiwayatTransaksiKeluar(nama, namaTujuan, to_string(nominalTransfer));
    updateRiwayatTransaksiMasuk(namaTujuan, nama, to_string(nominalTransfer));
}

// Fungsi untuk mengupdate saldo
void updateSaldo(string nama, long long unsigned int saldoTerbaru){
    ofstream saldo;
    saldo.open("data/" + nama + "/saldo.txt");
    saldo << saldoTerbaru;
    saldo.close();
}

// update riwayat transaksi masuk
void updateRiwayatTransaksiMasuk(string nama, string namaPengirim, string nominal){
    ofstream updateRTM;
    
    (getStatusRiwayatTransaksiMasuk(nama) == "BelumAdaTransaksi") ? updateRTM.open("data/" + nama + "/riwayatTransaksiMasuk.txt") : updateRTM.open("data/" + nama + "/riwayatTransaksiMasuk.txt", ios::app);
    updateRTM << "Uang masuk dari : " << namaPengirim << " sebanyak " << nominal << endl;
    updateRTM.close();
}

// string namaPenerima update riwayat transaksi keluar
void updateRiwayatTransaksiKeluar(string nama, string namaPenerima, string nominal){
    ofstream updateRTK;

    (getStatusRiwayatTransaksiKeluar(nama) == "BelumAdaTransaksi") ? updateRTK.open("data/" + nama + "/riwayatTransaksiKeluar.txt") : updateRTK.open("data/" + nama + "/riwayatTransaksiKeluar.txt", ios::app);
    updateRTK << "Mengirim Uang ke : " << namaPenerima << " sebanyak " << nominal << endl;
    updateRTK.close();
}

// melihat status riswayat transasksi masuk saat ini
string getStatusRiwayatTransaksiMasuk(string nama){
    string output, temp;
    
	ifstream verifikasi;
	verifikasi.open("data/" + nama + "/riwayatTransaksiMasuk.txt"); // sesuain dengan lokasi
    while(!verifikasi.eof()){
    verifikasi >> temp;
    output += temp;
    }
    verifikasi.close();
    
    return output;
}

// melihat status riswayat transasksi keluar saat ini
string getStatusRiwayatTransaksiKeluar(string nama){
    string output, temp;
    
	ifstream verifikasi;
	verifikasi.open("data/" + nama + "/riwayatTransaksiKeluar.txt"); // sesuain dengan lokasi
    while(!verifikasi.eof()){
    verifikasi >> temp;
    output += temp;
    }
    verifikasi.close();
    
    return output;
}

// tampilan menu riwayat transaksi
void menuRiwayatTransaksi(string nama){
    system("cls");
    formRiwayatTransaksi();
    char pilihanMenuRiwayatTransaksi;
    linexy(29,17);
    cin >> pilihanMenuRiwayatTransaksi;
    //(pilihanMenuRiwayatTransaksi == '1') ? readFile(nama, "riwayatTransaksiMasuk") : readFile(nama, "riwayatTransaksiKeluar");
    //linexy(16,12);
    int y = 12;
    if(pilihanMenuRiwayatTransaksi == '1'){
        formRiwayatTransaksiMasuk();
        vector<string>listRiwayatTransaksi = readFileVersiReturn(nama, "riwayatTransaksiMasuk");
        for(auto i : listRiwayatTransaksi){
            linexy(16,y);
            cout<<i<<endl;
            y++;
        }
        char pilihSort;
        linexy(17,10); cin>>pilihSort;
        if(pilihSort == '1') {
            y = 12;
            formRiwayatTransaksiMasuk();
            stack<string> riwayatTransaksiMasukSort = sortByDuitAscending(listRiwayatTransaksi);
            while (!riwayatTransaksiMasukSort.empty()) {
                linexy(16, y);
                cout << riwayatTransaksiMasukSort.top() << endl;
                riwayatTransaksiMasukSort.pop();
                y++;
            }
        }
        else if (pilihSort == '2') {
            y = 12;
            formRiwayatTransaksiMasuk();
            queue<string> riwayatTransaksiMasukSort = sortByDuitDescending(listRiwayatTransaksi);
            while (!riwayatTransaksiMasukSort.empty()) {
                linexy(16, y);
                cout << riwayatTransaksiMasukSort.front() << endl;
                riwayatTransaksiMasukSort.pop();
                y++;
            }
        }
    }else{
        formRiwayatTransaksiKeluar();
        vector<string>listRiwayatTransaksi = readFileVersiReturn(nama, "riwayatTransaksiKeluar");
        for(auto i : listRiwayatTransaksi){
            linexy(16,y);
            cout<<i<<endl;
            y++;
        }
        char pilihSort;
        linexy(17,10); cin>>pilihSort;
        if(pilihSort == '1') {
            y = 12;
            formRiwayatTransaksiKeluar();
            stack<string> riwayatTransaksiKeluarSort = sortByDuitAscending(listRiwayatTransaksi);
            while (!riwayatTransaksiKeluarSort.empty()) {
                linexy(16, y);
                cout << riwayatTransaksiKeluarSort.top() << endl;
                riwayatTransaksiKeluarSort.pop();
                y++;
            }
        }
        else if (pilihSort == '2') {
            y = 12;
            formRiwayatTransaksiKeluar();
            queue<string> riwayatTransaksiKeluarSort = sortByDuitDescending(listRiwayatTransaksi);
            while (!riwayatTransaksiKeluarSort.empty()) {
                linexy(16, y);
                cout << riwayatTransaksiKeluarSort.front() << endl;
                riwayatTransaksiKeluarSort.pop();
                y++;
            }
        }

    }
}

// Untuk baca isi dari file secara loop
void readFile(string nama, string fileTujuan){
    ifstream file("data/" + nama + "/" + fileTujuan + ".txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// konversi dari string ngambil bagian angkanya aja biar bisa di sortting
int extractNominal(const string& str) {
    size_t pos = str.rfind("sebanyak ");
    if (pos != string::npos) {
        return stoi(str.substr(pos + 9));
    }
    return 0;
}

// Fungsi untuk menggabungkan dua subvektor yang telah diurutkan
void merge(vector<string>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<string> L(n1);
    vector<string> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (extractNominal(L[i]) <= extractNominal(R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Fungsi rekursif untuk melakukan merge sort
void mergeSort(vector<string>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ini baca file juga beda nya dia bakal di simpen ke vector
vector <string> readFileVersiReturn(string nama, string fileTujuan){
    ifstream file("data/" + nama + "/" + fileTujuan + ".txt");
    vector <string> result;
    string line;
    while (getline(file, line)) {
        result.push_back(line);
    }
    file.close();
    return result;
}

// ini hasil sorting yang dari kecil ke besar
stack <string> sortByDuitAscending(vector <string> arr){
    stack <string> result;
    mergeSort(arr, 0, arr.size() - 1);
    // Menampilkan hasil urutan
    for (const auto& i : arr) {result.push(i);}
    return result;
}

// ini hasil sorting yang dari besar ke kecil
queue <string> sortByDuitDescending(vector <string> arr){
    queue <string> result;
    mergeSort(arr, 0, arr.size() - 1);
    // Menampilkan hasil urutan
    for (const auto& i : arr) {result.push(i);}
    return result;
}

// <------------------ End Fungsi Fungsi Utama ------------------>