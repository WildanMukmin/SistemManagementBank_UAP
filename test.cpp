#include "src/project.h"


int main(){
    system("g++ main.cpp -lwinmm");
    system("a");

    // PlaySound(TEXT("music/transfer.wav"), NULL, SND_SYNC);

    // deque <string> listPengguna = database();
    // string namaTujuan;
    // string noRekTujuan = "9226319897";

    // for(auto i : listPengguna){
    //     string output;
        
    //     ifstream verifikasi;
    //     verifikasi.open("data/" + i + "/nomorRekening.txt"); // sesuain dengan lokasi
    //     verifikasi >> output;
    //     verifikasi.close();

    //     cout << i << endl;
    //     if(output == noRekTujuan){
    //         namaTujuan = i;
    //         break;
    //     }
    // }

    return 0;
}