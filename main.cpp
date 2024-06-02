#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

// #include "mmsystem.h"

// #pragma comment(lib, "winmm.lib")

using namespace std;

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


//-------------------------- Tempat Warna --------------------------//
#define RESET "\033[0m"

// MAKRO WARNA TEKS
#define GRAY "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// MAKRO WARNA TEKS CERAH
#define GRAY_LIGHT "\033[1;30m"
#define RED_LIGHT "\033[1;31m"
#define GREEN_LIGHT "\033[1;32m"
#define YELLOW_LIGHT "\033[1;33m"
#define BLUE_LIGHT "\033[1;34m"
#define MAGENTA_LIGHT "\033[1;35m"
#define CYAN_LIGHT "\033[1;36m"
#define WHITE_LIGHT "\033[1;37m"

// MAKRO WARNA BACKGROUND
#define GRAY_BG "\033[40m"
#define RED_BG "\033[41m"
#define GREEN_BG "\033[42m"
#define YELLOW_BG "\033[43m"
#define BLUE_BG "\033[44m"
#define MAGENTA_BG "\033[45m"
#define CYAN_BG "\033[46m"
#define WHITE_BG "\033[47m"

// MAKRO WARNA BACKGROUND CERAH
#define GRAY_BG_LIGHT "\033[1;40m"
#define RED_BG_LIGHT "\033[1;41m"
#define GREEN_BG_LIGHT "\033[1;42m"
#define YELLOW_BG_LIGHT "\033[1;43m"
#define BLUE_BG_LIGHT "\033[1;44m"
#define MAGENTA_BG_LIGHT "\033[1;45m"
#define CYAN_BG_LIGHT "\033[1;46m"
#define WHITE_BG_LIGHT "\033[1;47m"

//----------------------- Akhir Tempat Warna -----------------------//

// MAKRO GAYA TEKS
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define HIDDEN "\033[8m"
#define CORET "\033[9m"

// set koordinat
void linexy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// loading animation
void loading(int x, int y)
{
	char load[] = "L O A D I N G";

	linexy(x, y);
	for (int i = 0; i <= 12; i++)
	{
		cout << load[i];
		Sleep(50);
	}

	for (int i = 0; i <= 100; i++)
	{
		linexy(x + 13, y);
		cout << " " << i << " %" ; // 13
		Sleep(10);
	}
}

// make a line x (koordinat x = 0-191)
void createLineX(int x, int toX, int y, int tahan = 0, char style = '#')
{

	if (style == '-')
	{
		for (int i = x; i <= toX; i++)
		{
			linexy(i, y);
			printf("-");
			Sleep(tahan);
		}
	}
	else
	{
		for (int i = x; i <= toX; i++)
		{
			linexy(i, y);
			printf("#");
			Sleep(tahan);
		}
	}
}

// make a line y
void createLineY(int y, int toY, int x, int tahan = 0, char style = '#')
{
	if (style == '|')
	{
		for (int i = y; i <= toY; i++)
		{
			linexy(x, i); // 13
			printf("|");
			Sleep(tahan);
		}
	}
	else
	{
		for (int i = y; i <= toY; i++)
		{
			linexy(x, i); // 13
			printf("#");
			Sleep(tahan);
		}
	}
}

// create text
void createText(int x, int y, string text, int tahan = 0)
{
	linexy(x, y);
	for (int i = 0; i <= text.length(); i++)
	{
		cout << text[i];
		Sleep(tahan);
	}
}

// singkatan cout
template <class T> void warna(T kata){
	cout << kata << endl;
}


//------------tempat tempat void tampilan------------//

// box opsi login
void boxOpsiLogin()
{
	createText(54, 1, "                     ,---.           ,---.");
	createText(54, 2, "                    / /'`.'..''''--./,''\\ \\");
	createText(54, 3, "                    \\ \\    _       _    / /");
	createText(54, 4, "                     `.'  ' __   __ `  `,'");
	createText(54, 5, "                      /    /_O)_(_O\\    \\");
	createText(54, 6, "                      |  .-'  ___  `-.  |");
	createText(54, 7, "                   .--|       \\_/       |--.");
	createText(54, 8, "                 ,'    `   \\   |   /   /    `.");
	createText(54, 9, "                /       `.  `--^--'  ,'       `");
	createText(54, 10, "             .-''''..    ` ...___...'      .-''''-.");
	createText(54, 11, ".-----------/         `------------------/         `--------------.");
	createText(54, 12, "| .---------`         /------------------`         /------------. |");
	createText(54, 13, "| |          `.`..`..'                    `.'...'.'             | |");
	createText(54, 14, "| |                        B E R A N D A                        | |");
	createText(54, 15, "| |                                                             | |");
	createText(54, 16, "| |                                                             | |");
	createText(54, 17, "| |     1. LOGIN                                                | |");
	createText(54, 18, "| |     2. BUAT AKUN                                            | |");
	createText(54, 19, "| |     3. KELUAR                                               | |");
	createText(54, 20, "| |                                                             | |");
	createText(54, 21, "| |                        JAWABAN ANDA :                       | |");
	createText(54, 22, "| |                                                             | |");
	createText(54, 23, "| |                                                             | |");
	createText(54, 24, "| |_____________________________________________________________| |");
	createText(54, 25, "|_________________________________________________________________|");
	createText(54, 26, "                   )__________|__|__________(");
	createText(54, 27, "                  |            ||            |");
	createText(54, 28, "                  |____________||____________|");
	createText(54, 29, "                    ),-----.(      ),-----.(");
	createText(54, 30, "                  ,'   ..   `     '    ..   `.");
	createText(54, 31, "                 /            )  (           '");
	createText(54, 32, "                 `..........'    `...........'");
}

// tampilan untuk form login
void formLogin(){
    createLineX(10, 60, 10);
    createLineX(10, 60, 30);
    createLineY(10, 30, 10);
    createLineY(10, 30, 60);

    linexy(12,12); cout << "Masukan Nama Anda : ";
    linexy(12,14); cout << "Masukan PIN Anda : ";
}


int main(){
    string nama, pin;

    cout << "selamat datang" << endl;
    getch();
    GATEWAY:
    system("cls");
    boxOpsiLogin();
    
    linexy(96,21);
    char pilihan;cin >> pilihan;
    if(pilihan == '1'){
        FORM:
        system("cls");
        formLogin();
        linexy (33, 12); cin >> nama;
        linexy (33, 14); cin >> pin;
        bool valid = login(nama, pin);
        if(valid){
            goto HOME;
        }else{
            cout << endl;
            cout << "Nama atau PIN salah!" << endl;
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

    deque <string> listPengguna = database();

    // <---------------- end pengecekan data yang sudah ada ---------------->


    // <---------------- Menu Home ---------------->
    system("cls");
    loading(10, 10);
    system("cls");

    cout << "Masukan Pilihan Anda" << endl;
    cout << "1. Info Akun" << endl;
    cout << "2. Transfer" << endl;
    cout << "3. Riwayat Transaksi" << endl;
    cout << "4. Log Out" << endl;
    char pilihanHome; cin >> pilihanHome;

    if(pilihanHome == '1') infoAkun(nama);
    else if(pilihanHome == '2') transfer(nama, listPengguna);
    else if(pilihanHome == '3') menuRiwayatTransaksi(nama);

    // <---------------- End Menu Home ---------------->

    return 0;
}

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