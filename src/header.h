#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

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


// <------------------ Prototype Header ------------------>

void linexy(int x, int y);
void loading(int x, int y);
void createLineX(int x, int toX, int y, int tahan, char sytle);
void createLineY(int y, int toY, int x, int tahan, char sytle);
void createText(int x, int y, string text, int tahan);
template <class T> void warna(T kata);
void boxOpsiLogin();
void selamatdatang();
void boxCreateAccount();
void notifikasiAkunBerhasil(string nama);
void infoAkun(string nama);
void strukPembayaran(string nama, string namaTujuan, long long unsigned int nominalTransfer);
void formLogin();
void salahPinLogin();
void formCreateAkun();
void boxBeranda();
void formRiwayatTransaksi();
void formRiwayatTransaksiMasuk();
void formRiwayatTransaksiKeluar();
void formTransfer();
void konfirTransfer();
void salahPinTransfer();
void batalTransfer();

// <------------------ Prototype Fungsi Utama ------------------>

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
vector <string> readFileVersiReturn(string nama, string fileTujuan);
void mergeSort(vector<string>& arr, int left, int right);
void merge(vector<string>& arr, int left, int mid, int right);
int extractNominal(const string& str);
vector <string> readFileVersiReturn(string nama, string fileTujuan);
stack <string> sortByDuitAscending(vector <string> arr);
queue <string> sortByDuitDescending(vector <string> arr);
void notifikasiAkunBerhasil(string nama);
class Nasabah;

// <------------------ End Prototype ------------------>

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
	char load[] = {'L', ' ', 'O', ' ', 'A', ' ', 'D', ' ', 'I', ' ', 'N', ' ', 'G', '\0'};

	linexy(x, y);
	for (int i = 0; i <= 12; i++)
	{
		cout << CYAN_LIGHT << load[i] << RESET;
		Sleep(50);
	}

	for (int i = 0; i <= 100; i++)
	{
		linexy(x + 13, y);
		cout << CYAN_LIGHT << " " << i << " %" << RESET; // 13
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

// tampilan untuk form login

// box opsi login
void boxOpsiLogin()
{
	cout << CYAN;
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
	cout << RESET;
}

// tampilan selamat datang
void selamatdatang()
{
	cout << CYAN;
    createText(20, 1, "  ____       _                       _     ____        _                    _ ");
    createText(20, 2, " / ___|  ___| | __ _ _ __ ___   __ _| |_  |  _ \\  __ _| |_ __ _ _ __   __ _| |");
    createText(20, 3, " \\___ \\ / _ \\ |/ _` | '_ ` _ \\ / _` | __| | | | |/ _` | __/ _` | '_ \\ / _` | |");
    createText(20, 4, "  ___) |  __/ | (_| | | | | | | (_| | |_  | |_| | (_| | || (_| | | | | (_| |_|");
    createText(20, 5, " |____/ \\___|_|\\__,_|_| |_| |_|\\__,_|\\__| |____/ \\__,_|\\__\\__,_|_| |_|\\__, (_)");
    createText(20, 6, "                                                                       |___/   ");
	cout << RESET;
}

// tampilan untuk membuat akun
void boxCreateAccount(){
    int W = 42;
    int V = 7;

    cout << CYAN;
    linexy(W, V); cout << "   .'_________________________________________  '."; V++;
    linexy(W, V); cout << "  : .'                                         '. :"; V++;
    linexy(W, V); cout << "  | |    ____________________________________   | |"; V++;
    linexy(W, V); cout << "  | |  .:____________________________________:. | |"; V++;
    linexy(W, V); cout << "  | |  |             CREATE ACCOUNT             | |"; V++;
    linexy(W, V); cout << "  | |  |                                        | |"; V++;
    linexy(W, V); cout << "  | |  |  Masukan Nama     :                    | |"; V++;
    linexy(W, V); cout << "  | |  |  Masukan Pin      :                    | |"; V++;
    linexy(W, V); cout << "  | |  |                                        | |"; V++;
    linexy(W, V); cout << "  | |  '.______________________________________.' |"; V++;
    linexy(W, V); cout << "  | |                                           | |"; V++;
    linexy(W, V); cout << "  : '._________________________________________.' :"; V++;
    linexy(W, V); cout << "   .____________________\\__/____________________."; V++;
    cout << RESET;
}

// tampilan notfiikasi
void notifikasiAkunBerhasil(string nama) {
	string* orang = &nama;
    cout << CYAN;
	linexy(52,6);
	cout << "Akun berhasil dibuat untuk " << *orang << "!" << endl;
    cout << RESET;
}

// Fungsi Menampilkan Detail Informasi Akun
void infoAkun(string nama) {
    cout << CYAN;
    cout << "    _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._" << endl;
    cout << "  ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`." << endl;
    cout << " ( (                                                         ) )" << endl;
    cout << setw(5) <<") )" << "          Nomor Rekening Anda : " << getNoRek(nama) << "             ( (" << endl;
    cout << " ( (" << "           Saldo Anda          : " << fixed << setprecision(2) << getSaldo(nama) << "                       ) )" << endl;
    cout << "  ) )                                                       ( (" << endl;
    cout << " ( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )" << endl;
    cout << " `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,-.'" << endl;
    cout << RESET;
}

// tampilan untuk struk pembayaran
void strukPembayaran(string nama, string namaTujuan, long long unsigned int nominalTransfer){
    cout << CYAN;
    cout << "     _______________________________________________________" << endl;
    cout << "    //                                                       \\ " << endl;
    cout << "(O)===)><><><><><><><><><><><><><><><><><><><><><><><><><><><)==(O)" << endl;
    cout << "    \\/''''''''''''''''''''''''''''''''''''''''''''''''''''''/ " << endl;
    cout << "    (                                                      ( " << endl;
    cout << "     )                                                      )" << endl;
    cout << "    (        Transfer Berhasil Dari " << setw(20) << left << nama << "   (" << endl;
    cout << "     )       ke " << setw(20) << left << namaTujuan << "                        )" << endl;
    cout << "    (        sejumlah " << setw(20) << left << nominalTransfer << "                 ( " << endl;
    cout << "     )                                                      )" << endl;
    cout << "    (                                                      ( " << endl;
    cout << "     )                                                      )" << endl;
    cout << "    /\''''''''''''''''''''''''''''''''''''''''''''''''''''''\\ " << endl;
    cout << "(O)===)><><><><><><><><><><><><><><><><><><><><><><><><><><><)==(O)" << endl;
    cout << "    \\/______________________________________________________/ " << endl;
    cout << RESET;
}

//tampilan login
void formLogin()
{
	createText(1, 1, "   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._");
    createText(1, 2, " ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.");
    createText(1, 3, "( (                                                                         ) )");
    createText(1, 4, " ) )                                                                       ( (");
    createText(1, 5, "( (                                                                         ) )");
    createText(1, 6, " ) )                               Log In                                  ( (");
    createText(1, 7, "( (                                                                         ) )");
    createText(1, 8, " ) )                                                                       ( (");
    createText(1, 9, "( (                                                                         ) )");
    createText(1, 10, " ) )                                                                       ( (");
    createText(1, 11, "( (            Masukkan Nama Anda :                                         ) )");
    createText(1, 12, " ) )                                                                       ( (");
    createText(1, 13, "( (            Buat PIN Anda      :                                         ) )");
    createText(1, 14, " ) )                                                                       ( (");
    createText(1, 15, "( (                                                                         ) )");
    createText(1, 16, " ) )                                                                       ( (");
    createText(1, 17, "( (                                                                         ) )");
    createText(1, 18, " ) )                                                                       ( (");
    createText(1, 19, "( (                                                                         ) )");
    createText(1, 20, " ) )                                                                       ( (");
    createText(1, 21, "( (                                                                         ) )");
    createText(1, 22, " ) )                                                                       ( (");
    createText(1, 23, "( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )");
    createText(1, 24, " `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'");
}

// tampilan untuk form salah pin login
void salahPinLogin()
{
	createText(1, 1, "   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._");
    createText(1, 2, " ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.");
    createText(1, 3, "( (                                                                         ) )");
    createText(1, 4, " ) )                                                                       ( (");
    createText(1, 5, "( (                                                                         ) )");
    createText(1, 6, " ) )                               Log In                                  ( (");
    createText(1, 7, "( (                                                                         ) )");
    createText(1, 8, " ) )                                                                       ( (");
    createText(1, 9, "( (            Proses login Anda gagal, karena Nama atau PIN yang           ) )");
    createText(1, 10, " ) )           Anda masukan salah.                                         ( (");
    createText(1, 11, "( (            Silakan lakukan log in ulang atau buat akun.                 ) )");
    createText(1, 12, " ) )                                                                       ( (");
    createText(1, 13, "( (            1. Log in                                                    ) )");
    createText(1, 14, " ) )           2. Buat Akun                                                ( (");
    createText(1, 15, "( (            Pilih Opsi :                                                 ) )");
    createText(1, 16, " ) )                                                                       ( (");
    createText(1, 17, "( (                                                                         ) )");
    createText(1, 18, " ) )                                                                       ( (");
    createText(1, 19, "( (                                                                         ) )");
    createText(1, 20, " ) )                                                                       ( (");
    createText(1, 21, "( (                                                                         ) )");
    createText(1, 22, " ) )                                                                       ( (");
    createText(1, 23, "( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )");
    createText(1, 24, " `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'");
}

//tampilan beranda
void boxBeranda()
{
    createText(1, 1, "   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._");
    createText(1, 2, " ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.");
    createText(1, 3, "( (                                                                         ) )");
    createText(1, 4, " ) )             __  __   ____              _    _                         ( (");
    createText(1, 5, "( (             |  \\/  | | __ )  __ _ _ __ | | _(_)_ __   __ _              ) )");
    createText(1, 6, " ) )            | |\\/| | |  _ \\ / _` | '_ \\| |/ / | '_ \\ / _` |            ( (");
    createText(1, 7, "( (             | |  | | | |_) | (_| | | | |   <| | | | | (_| |             ) )");
    createText(1, 8, " ) )            |_|  |_| |____/ \\__,_|_| |_|_|\\_\\_|_| |_|\\__, |            ( (");
    createText(1, 9, "( (                                                      |___/              ) )");
    createText(1, 10, " ) )                                                                       ( (");
    createText(1, 11, "( (                                                                         ) )");
    createText(1, 12, " ) )            1. Log In                                                  ( (");
    createText(1, 13, "( (             2. Buat Akun                                                ) )");
    createText(1, 14, " ) )            3. Keluar                                                  ( (");
    createText(1, 15, "( (             Pilih Opsi :                                                ) )");
    createText(1, 16, " ) )                                                                       ( (");
    createText(1, 17, "( (                                                                         ) )");
    createText(1, 18, " ) )                                                                       ( (");
    createText(1, 19, "( (                                                                         ) )");
    createText(1, 20, " ) )                                                                       ( (");
    createText(1, 21, "( (                                                                         ) )");
    createText(1, 22, " ) )                                                                       ( (");
    createText(1, 23, "( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )");
    createText(1, 24, " `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'");
}

//tampilan riwayat transaksi
void formRiwayatTransaksi()
{
	createText(1, 1, "   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._");
    createText(1, 2, " ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.");
    createText(1, 3, "( (                                                                         ) )");
    createText(1, 4, " ) )                                                                       ( (");
    createText(1, 5, "( (                                                                         ) )");
    createText(1, 6, " ) )                          Riwayat Transaksi                            ( (");
    createText(1, 7, "( (                                                                         ) )");
    createText(1, 8, " ) )                                                                       ( (");
    createText(1, 9, "( (                                                                         ) )");
    createText(1, 10, " ) )                                                                       ( (");
    createText(1, 11, "( (            Jenis Transaksi                                              ) )");
    createText(1, 12, " ) )                                                                       ( (");
    createText(1, 13, "( (            1. Transaksi Masuk                                           ) )");
    createText(1, 14, " ) )                                                                       ( (");
    createText(1, 15, "( (            2. Transaksi Keluar                                          ) )");
    createText(1, 16, " ) )                                                                       ( (");
    createText(1, 17, "( (            3. Kembali                                                   ) )");
    createText(1, 18, " ) )                                                                       ( (");
    createText(1, 19, "( (            Pilih Opsi :                                                 ) )");
    createText(1, 20, " ) )                                                                       ( (");
    createText(1, 21, "( (                                                                         ) )");
    createText(1, 22, " ) )                                                                       ( (");
    createText(1, 23, "( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )");
    createText(1, 24, " `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'");
}

//tampilan urutan transaksi masuk
void formRiwayatTransaksiMasuk()
{
	createText(1, 1, "   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._");
    createText(1, 2, " ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.");
    createText(1, 3, "( (                                                                         ) )");
    createText(1, 4, " ) )                                                                       ( (");
    createText(1, 5, "( (                                                                         ) )");
    createText(1, 6, " ) )                     Riwayat Transaksi Masuk                           ( (");
    createText(1, 7, "( (                                                                         ) )");
    createText(1, 8, " ) )            1. Terbesar -> Kecil                                       ( (");
    createText(1, 9, "( (             2. Terkecil -> Besar                                        ) )");
    createText(1, 10, " ) )               :                                                       ( (");
    createText(1, 11, "( (                                                                         ) )");
    createText(1, 12, " ) )                                                                       ( (");
    createText(1, 13, "( (                                                                         ) )");
    createText(1, 14, " ) )                                                                       ( (");
    createText(1, 15, "( (                                                                         ) )");
    createText(1, 16, " ) )                                                                       ( (");
    createText(1, 17, "( (                                                                         ) )");
    createText(1, 18, " ) )                                                                       ( (");
    createText(1, 19, "( (                                                                         ) )");
    createText(1, 20, " ) )                                                                       ( (");
    createText(1, 21, "( (                                                                         ) )");
    createText(1, 22, " ) )                                                                       ( (");
    createText(1, 23, "( (                                                                         ) )");
}

//tampilan urutan transaksi keluar
void formRiwayatTransaksiKeluar()
{
	createText(1, 1, "   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._");
    createText(1, 2, " ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.");
    createText(1, 3, "( (                                                                         ) )");
    createText(1, 4, " ) )                                                                       ( (");
    createText(1, 5, "( (                                                                         ) )");
    createText(1, 6, " ) )                     Riwayat Transaksi Keluar                          ( (");
    createText(1, 7, "( (                                                                         ) )");
    createText(1, 8, " ) )            1. Terbesar -> Kecil                                       ( (");
    createText(1, 9, "( (             2. Terkecil -> Besar                                        ) )");
    createText(1, 10, " ) )               :                                                       ( (");
    createText(1, 11, "( (                                                                         ) )");
    createText(1, 12, " ) )                                                                       ( (");
    createText(1, 13, "( (                                                                         ) )");
    createText(1, 14, " ) )                                                                       ( (");
    createText(1, 15, "( (                                                                         ) )");
    createText(1, 16, " ) )                                                                       ( (");
    createText(1, 17, "( (                                                                         ) )");
    createText(1, 18, " ) )                                                                       ( (");
    createText(1, 19, "( (                                                                         ) )");
    createText(1, 20, " ) )                                                                       ( (");
    createText(1, 21, "( (                                                                         ) )");
    createText(1, 22, " ) )                                                                       ( (");
    createText(1, 23, "( (                                                                         ) )");
}

//tampilan awal transfer
void formTransfer()
{
	createText(1, 1, "   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._");
    createText(1, 2, " ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.");
    createText(1, 3, "( (                                                                         ) )");
    createText(1, 4, " ) )                                                                       ( (");
    createText(1, 5, "( (                                                                         ) )");
    createText(1, 6, " ) )                                M-Transfer                             ( (");
    createText(1, 7, "( (                                                                         ) )");
    createText(1, 8, " ) )           Dari Rekening   :                                           ( (");
    createText(1, 9, "( (                                                                         ) )");
    createText(1, 10, " ) )           Rekening Tujuan :                                           ( (");
    createText(1, 11, "( (                                                                         ) )");
    createText(1, 12, " ) )           Nominal         :                                           ( (");
    createText(1, 13, "( (                                                                         ) )");
    createText(1, 14, " ) )                                                                       ( (");
    createText(1, 15, "( (                                                                         ) )");
    createText(1, 16, " ) )                                                                       ( (");
    createText(1, 17, "( (                                                                         ) )");
    createText(1, 18, " ) )                                                                       ( (");
    createText(1, 19, "( (                                                                         ) )");
    createText(1, 20, " ) )                                                                       ( (");
    createText(1, 21, "( (                                                                         ) )");
    createText(1, 22, " ) )                                                                       ( (");
    createText(1, 23, "( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )");
    createText(1, 24, " `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'");
}

//tampilan awal transfer
void konfirTransfer()
{
    createText(1, 1, " __| |____________________________________________| |__");
    createText(1, 2, "(__   ____________________________________________   __)");
    createText(1, 3, "   | |                                            | |");
    createText(1, 4, "   | |       Apakah Rekening dan Nominal          | |");
    createText(1, 5, "   | |       Sudah sesuai ? (Y/N)                 | |");
    createText(1, 6, "   | |                                            | |");
    createText(1, 7, "   | |                                            | |");
    createText(1, 8, "   | |       PIN Anda :                           | |");
    createText(1, 9, " __| |____________________________________________| |__");
    createText(1, 10, "(__   ____________________________________________   __)");
    createText(1, 11, "   | |                                            | |");
}

//tampilan awal transfer
void salahPinTransfer()
{
    createText(1, 1, " __| |____________________________________________| |__");
    createText(1, 2, "(__   ____________________________________________   __)");
    createText(1, 3, "   | |                                            | |");
    createText(1, 4, "   | |                                            | |");
    createText(1, 5, "   | |                                            | |");
    createText(1, 6, "   | |         PIN yang Anda Masukkan Salah       | |");
    createText(1, 7, "   | |                                            | |");
    createText(1, 8, "   | |                                            | |");
    createText(1, 9, " __| |____________________________________________| |__");
    createText(1, 10, "(__   ____________________________________________   __)");
    createText(1, 11, "   | |                                            | |");
}
//tampilan awal transfer
void batalTransfer()
{
    createText(1, 1, " __| |____________________________________________| |__");
    createText(1, 2, "(__   ____________________________________________   __)");
    createText(1, 3, "   | |                                            | |");
    createText(1, 4, "   | |                                            | |");
    createText(1, 5, "   | |                                            | |");
    createText(1, 6, "   | |           Transaksi Dibatalkan!            | |");
    createText(1, 7, "   | |                                            | |");
    createText(1, 8, "   | |                                            | |");
    createText(1, 9, " __| |____________________________________________| |__");
    createText(1, 10, "(__   ____________________________________________   __)");
    createText(1, 11, "   | |                                            | |");
}