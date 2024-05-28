#include <header.h>

// <------------------ Prototype ------------------>

void createAkun();
bool login(string nama, string pin);
deque<string> database();
void infoAkun(string nama);
void transfer(string nama, deque<string> listPengguna);
string getNoRek(string nama);
long long unsigned int getSaldo(string nama);
void updateSaldo(string nama, long long unsigned int saldoTerbaru);
string generateRandomNoRek(int n);
string getStatusRiwayatTransaksiMasuk(string nama);
void updateRiwayatTransaksiMasuk(string nama, string namaPengirim, string nominal);
string getStatusRiwayatTransaksiKeluar(string nama);
void updateRiwayatTransaksiKeluar(string nama, string namaPenerima, string nominal);
void menuRiwayatTransaksi(string nama);
void readFile(string nama, string fileTujuan);
class Nasabah;

// <------------------ End Prototype ------------------>


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
        akun.open(nama + "/userAkun.txt", ios::app);
        akun << nama;
        akun << pin;
        akun.close();

        ofstream nomorRekening;
        nomorRekening.open(nama + "/nomorRekening.txt", ios::app);
        nomorRekening << noRek;
        nomorRekening.close();
        
        ofstream saldo;
        saldo.open(nama + "/saldo.txt", ios::app);
        saldo << 0;
        saldo.close();
        
        ofstream riwayatTransaksiMasuk;
        riwayatTransaksiMasuk.open(nama + "/riwayatTransaksiMasuk.txt", ios::app);
        riwayatTransaksiMasuk << "Belum Ada Transaksi";
        riwayatTransaksiMasuk.close();
        
        ofstream riwayatTransaksiKeluar;
        riwayatTransaksiKeluar.open(nama + "/riwayatTransaksiKeluar.txt", ios::app);
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
void createAkun(){   
	string nama;
	cin >> nama;
	string pin;
	cin >> pin;
    deque <string> listPengguna;
    ifstream checkListPengguna;
	checkListPengguna.open("listPengguna.txt");
    string data;
	while (!checkListPengguna.eof()){
		checkListPengguna >> data;
        listPengguna.push_back(data);
	}
	checkListPengguna.close();
    Nasabah(nama, pin, generateRandomNoRek(listPengguna.size()));
}

// pilihan dari login
bool login(string nama, string pin){
	string output;

	ifstream verifikasi;
	verifikasi.open(nama + "/userAkun.txt"); // sesuain dengan lokasi
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

// Fungsi Menampilkan Detail Informasi Akun
void infoAkun(string nama){
    cout << "Nomor Rekening Anda : " << getNoRek(nama) << endl;
    cout << "Saldo Anda : " << getSaldo(nama) << endl;
}

// Fungsi mengambil nomor rekening
string getNoRek(string nama){
	string output;

	ifstream verifikasi;
	verifikasi.open(nama + "/nomorRekening.txt"); // sesuain dengan lokasi
    verifikasi >> output;
    verifikasi.close();
    
    return output;
}

// Fungsi untuk mengambil saldo
long long unsigned int getSaldo(string nama){
	string output;

	ifstream verifikasi;
	verifikasi.open(nama + "/saldo.txt"); // sesuain dengan lokasi
    verifikasi >> output;
    verifikasi.close();
    
    return stoull(output);
}

// Funsgi untuk melakukan transfer
void transfer(string nama, deque<string> listPengguna){
    cout << "Masukan Nomor Rekening Tujuan : ";
    string noRekTujuan;cin >> noRekTujuan;
    cout << "Masukan Nominal Transfer : ";
    long long unsigned int nominalTransfer;cin >> nominalTransfer;
    string namaTujuan;

    cout << "Apakah Rekening dan Nominal Sudah Sesuai? (y/n)" << endl;
    char konfirTransfer; cin >> konfirTransfer;
    if(konfirTransfer == 'y' || konfirTransfer == 'Y'){
        ULANGIVERIFIKASIPIN:
        cout << "Masukan PIN Anda : ";
        string pin;cin >> pin;
        if(login(nama, pin)){
            cout << "Transfer Berhasil" << endl;
        }else{
            cout << "PIN anda Salah" << endl;
            goto ULANGIVERIFIKASIPIN;
        }
    }else {
        cout << "Transaksi dibatalkan!" << endl;
        return;
    }

    for(auto i : listPengguna){
        string output;
        
        ifstream verifikasi;
        verifikasi.open(i + "/nomorRekening.txt"); // sesuain dengan lokasi
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

    cout << "Transfer Berhasil Dari " << nama << " ke " << namaTujuan << endl;
    cout << "sejumlah " << nominalTransfer << endl;
    updateRiwayatTransaksiKeluar(nama, namaTujuan, to_string(nominalTransfer));
    updateRiwayatTransaksiMasuk(namaTujuan, nama, to_string(nominalTransfer));
}

// Fungsi untuk mengupdate saldo
void updateSaldo(string nama, long long unsigned int saldoTerbaru){
    ofstream saldo;
    saldo.open(nama + "/saldo.txt");
    saldo << saldoTerbaru;
    saldo.close();
}

// update riwayat transaksi masuk
void updateRiwayatTransaksiMasuk(string nama, string namaPengirim, string nominal){
    ofstream updateRTM;
    
    (getStatusRiwayatTransaksiMasuk(nama) == "BelumAdaTransaksi") ? updateRTM.open(nama + "/riwayatTransaksiMasuk.txt") : updateRTM.open(nama + "/riwayatTransaksiMasuk.txt", ios::app);
    updateRTM << "Uang masuk dari : " << namaPengirim << " sebanyak " << nominal << endl;
    updateRTM.close();
}

// string namaPenerima update riwayat transaksi keluar
void updateRiwayatTransaksiKeluar(string nama, string namaPenerima, string nominal){
    ofstream updateRTK;

    (getStatusRiwayatTransaksiKeluar(nama) == "BelumAdaTransaksi") ? updateRTK.open(nama + "/riwayatTransaksiKeluar.txt") : updateRTK.open(nama + "/riwayatTransaksiKeluar.txt", ios::app);
    updateRTK << "Mengirim Uang ke : " << namaPenerima << " sebanyak " << nominal << endl;
    updateRTK.close();
}

// melihat status riswayat transasksi masuk saat ini
string getStatusRiwayatTransaksiMasuk(string nama){
    string output, temp;
    
	ifstream verifikasi;
	verifikasi.open(nama + "/riwayatTransaksiMasuk.txt"); // sesuain dengan lokasi
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
	verifikasi.open(nama + "/riwayatTransaksiKeluar.txt"); // sesuain dengan lokasi
    while(!verifikasi.eof()){
    verifikasi >> temp;
    output += temp;
    }
    verifikasi.close();
    
    return output;
}

// tampilan menu riwayat transaksi
void menuRiwayatTransaksi(string nama){
    cout << "1. riwayat transaksi masuk" << endl;
    cout << "2. riwayat transaksi keluar" << endl;
    
    cout << "masukan pilihan anda : ";
    char pilihanMenuRiwayatTransaksi; cin >> pilihanMenuRiwayatTransaksi;
    (pilihanMenuRiwayatTransaksi == '1') ? readFile(nama, "riwayatTransaksiMasuk") : readFile(nama, "riwayatTransaksiKeluar");
}

void readFile(string nama, string fileTujuan){
    ifstream file(nama + "/" + fileTujuan + ".txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// <------------------ End Fungsi Fungsi Utama ------------------>