#include <bits/stdc++.h>
using namespace std;

void createAkun();
bool login(string nama, string kataSandi);
void infoAkun(string nama);
void transfer(string nama, deque<string> listPengguna);
string noRek(string nama);
long long unsigned int saldo(string nama);
void updateSaldo(string nama, long long unsigned int saldoTerbaru);
string generateRandomNoRek(int n);
class Nasabah;

int main(){
    string nama, kataSandi;

    cout << "selamat datang" << endl;
    
    GATEWAY:
    cout << "pilih opsi" << endl;
    cout << "1. login" << endl;
    cout << "2. buat akun" << endl;
    
    char pilihan;cin >> pilihan;
    if(pilihan == '1'){
        FORM:
        cout << "Masukan Nama Anda : ";cin >> nama;
        cout << "Masukan kata sandi Anda : ";cin >> kataSandi;
        bool valid = login(nama, kataSandi);
        if(valid){
            goto HOME;
        }else{
            cout << endl;
            cout << "Nama atau Kata sandi salah!" << endl;
            cout << "Mohon masukan dengan benar!" << endl;

            cout << endl;
            cout << endl;
            PERINTAHSALAH:
            cout << "Coba lagi atau buat akun?"<<endl;
            cout << "1. untuk coba lagi"<<endl;
            cout << "2. untuk buat akun"<<endl;
            char pilihan2; cin >> pilihan2;
            if(pilihan2 == '1') goto FORM;
            else if(pilihan2 == '2') goto FORMCREATEAKUN;
            else goto PERINTAHSALAH;
            
        }
    }else if(pilihan == '2'){
        FORMCREATEAKUN:
        createAkun();
        goto GATEWAY;
    }

    HOME:
    // <---------------- pengecekan data yang sudah ada ---------------->
    deque <string> listPengguna;
    ifstream checkListPengguna;
	checkListPengguna.open("listPengguna.txt");
    string data;
	while (!checkListPengguna.eof()){
		checkListPengguna >> data;
        listPengguna.push_back(data);
	}
	checkListPengguna.close();
    // <---------------- end pengecekan data yang sudah ada ---------------->

    cout << "login berhasil" << endl << endl;
    
    cout << "Masukan Pilihan Anda" << endl;
    cout << "1. Info Akun" << endl;
    cout << "2. Transfer" << endl;
    cout << "3. Riwayat Transaksi" << endl;
    cout << "4. Log Out" << endl;
    char pilihanHome; cin >> pilihanHome;

    if(pilihanHome == '1') infoAkun(nama);
    else if(pilihanHome == '2') transfer(nama, listPengguna);


    return 0;
}

// class nasabah
class Nasabah
{
    private:
    string nama, kataSandi, noRek;
    unsigned long long int saldo;

    public:
    Nasabah(string nama, string kataSandi, string noRek) : nama(nama), kataSandi(kataSandi), noRek(noRek) {
        string buatFile = "mkdir " + nama;
        system(buatFile.c_str());

        ofstream akun;
        akun.open(nama + "/userAkun.txt", ios::app);
        akun << nama;
        akun << kataSandi;
        akun.close();

        ofstream nomorRekening;
        nomorRekening.open(nama + "/nomorRekening.txt", ios::app);
        nomorRekening << noRek;
        nomorRekening.close();
        
        ofstream saldo;
        saldo.open(nama + "/saldo.txt", ios::app);
        saldo << 0;
        saldo.close();
        
        ofstream riwayatTransaksi;
        riwayatTransaksi.open(nama + "/riwayatTransaksi.txt", ios::app);
        riwayatTransaksi << "Belum Ada Transaksi";
        riwayatTransaksi.close();

        // untuk masukin ke stack nya
        ofstream listPengguna;
        listPengguna.open("listPengguna.txt", ios::app);
        listPengguna << endl;
        listPengguna << nama;
        listPengguna.close();
        
    }


};

// pilihan buat akun
void createAkun()
{   
	string nama;
	cin >> nama;
	string kataSandi;
	cin >> kataSandi;
    deque <string> listPengguna;
    ifstream checkListPengguna;
	checkListPengguna.open("listPengguna.txt");
    string data;
	while (!checkListPengguna.eof()){
		checkListPengguna >> data;
        listPengguna.push_back(data);
	}
	checkListPengguna.close();
    Nasabah(nama, kataSandi, generateRandomNoRek(listPengguna.size() + 1));
}

// pilihan dari login
bool login(string nama, string kataSandi)
{
	string output;

	ifstream verifikasi;
	verifikasi.open(nama + "/userAkun.txt"); // sesuain dengan lokasi
    verifikasi >> output;
    if (output == nama + kataSandi) return true;
    verifikasi.close();
    return false;
}

// Fungsi untuk menghasilkan nomor rekening acak
string generateRandomNoRek(int n)
{   
    for(int i = 0; i < n; i++){
        static random_device rd;
        static mt19937 gen(rd());
        static uniform_int_distribution<unsigned long long> dis(1000000000, 9999999999);

        // Menghasilkan nomor acak dan mengkonversinya ke string
        unsigned long long randomNumber = dis(gen);
        if(i == n-1)return to_string(randomNumber);
    }
}

void infoAkun(string nama){
    cout << "Nomor Rekening Anda : " << noRek(nama) << endl;
    cout << "Saldo Anda : " << saldo(nama) << endl;
}

string noRek(string nama){
	string output;

	ifstream verifikasi;
	verifikasi.open(nama + "/nomorRekening.txt"); // sesuain dengan lokasi
    verifikasi >> output;
    verifikasi.close();
    
    return output;
}

long long unsigned int saldo(string nama){
	string output;

	ifstream verifikasi;
	verifikasi.open(nama + "/saldo.txt"); // sesuain dengan lokasi
    verifikasi >> output;
    verifikasi.close();
    
    return stoull(output);
}

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
    saldoPengirim = saldo(nama);
    saldoPenerima = saldo(namaTujuan);

    saldoPengirim -= nominalTransfer;
    saldoPenerima += nominalTransfer;

    updateSaldo(nama, saldoPengirim);
    updateSaldo(namaTujuan, saldoPenerima);

    cout << "Transfer Berhasil Dari " << nama << " ke " << namaTujuan << endl;
    cout << "sejumlah " << nominalTransfer << endl;
}

void updateSaldo(string nama, long long unsigned int saldoTerbaru){
    ofstream saldo;
    saldo.open(nama + "/saldo.txt");
    saldo << saldoTerbaru;
    saldo.close();
}
