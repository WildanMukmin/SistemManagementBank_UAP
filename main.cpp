#include "src/project.h"

int main(){
    string nama, pin;
    char greeting [] = "Masukan Pilihan Anda";
    system("cls");
    selamatdatang();
    getch();
    GATEWAY:
    system("cls");
    boxBeranda();
    
    linexy(30,15);
    char pilihan;cin >> pilihan;
    if(pilihan == '1'){
        FORM:
        system("cls");
        formLogin();
        linexy (37, 11); cin >> nama;
        linexy (37, 13); cin >> pin;
        bool valid = login(nama, pin);
        if(valid){
            goto HOME;
        }else{
            salahPinLogin();
            char pilihan2; 
            linexy(29, 15); cin >> pilihan2;
            if(pilihan2 == '1') goto FORM;
            else if(pilihan2 == '2') goto FORMCREATEAKUN;
            
        }
    }else if(pilihan == '2'){
        FORMCREATEAKUN:
        system("cls");
        createAkun();
        system("cls");
        goto GATEWAY;
    }else if(pilihan == '3'){
        main();
    }
    else exit(0);

    // <---------------- pengecekan data yang sudah ada ---------------->

    HOME:
    deque <string> listPengguna = database();

    // <---------------- end pengecekan data yang sudah ada ---------------->


    // <---------------- Menu Home ---------------->
    system("cls");
    loading(10, 10);
    system("cls");


    PILIHANOPSI:
        system("cls") ;
    menuHome();
    char pilihanHome; 
    linexy(19,17);
    cin >> pilihanHome;

    if(pilihanHome == '1') {
        system("cls") ;
        infoAkun(nama);
        getch();
        goto PILIHANOPSI;
    }
    else if(pilihanHome == '2') {
        transfer(nama, listPengguna);
        goto PILIHANOPSI;
    }
    else if(pilihanHome == '3') {
        menuRiwayatTransaksi(nama);
        goto PILIHANOPSI;
    }else if(pilihanHome == '4'){
        goto GATEWAY;
    }
    system("cls");

    // <---------------- End Menu Home ---------------->

    return 0;
}
