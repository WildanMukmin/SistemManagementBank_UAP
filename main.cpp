#include <bits/stdc++.h>
using namespace std;

void createAkun();
bool login(string nama, string kataSandi);
string generateRandomNoRek();
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
            cout << "Nama atau Kata sandi salah!" << endl;
            cout << "Mohon masukan dengan benar!" << endl;
            goto FORM;
        }
    }else if(pilihan == '2'){
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

    Nasabah(nama, kataSandi, generateRandomNoRek());
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
string generateRandomNoRek()
{
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<unsigned long long> dis(1000000000, 9999999999);

        // Menghasilkan nomor acak dan mengkonversinya ke string
        unsigned long long randomNumber = dis(gen);
        return to_string(randomNumber);
    }