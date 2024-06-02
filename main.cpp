#include "project.h"

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

    // <---------------- pengecekan data yang sudah ada ---------------->

    HOME:
    deque <string> listPengguna = database();

    // <---------------- end pengecekan data yang sudah ada ---------------->


    // <---------------- Menu Home ---------------->
    system("cls");
    loading(10, 10);
    system("cls");


    PILIHANOPSI:
    cout << "Masukan Pilihan Anda" << endl;
    cout << "1. Info Akun" << endl;
    cout << "2. Transfer" << endl;
    cout << "3. Riwayat Transaksi" << endl;
    cout << "4. Log Out" << endl;
    char pilihanHome; cin >> pilihanHome;

    if(pilihanHome == '1') {
        infoAkun(nama); 
        goto PILIHANOPSI;
    }
    else if(pilihanHome == '2') {
        transfer(nama, listPengguna);
        goto PILIHANOPSI;
    }
    else if(pilihanHome == '3') {
        menuRiwayatTransaksi(nama);
        goto PILIHANOPSI;
    }

    // <---------------- End Menu Home ---------------->

    return 0;
}
