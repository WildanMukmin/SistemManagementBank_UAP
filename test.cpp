#include "src/project.h"


int main(){
    vector <string> arr = readFileVersiReturn("wildan", "riwayatTransaksiKeluar");
    deque <string> sorted_arr1 = sortByDuitAscending(arr);
    deque <string> sorted_arr2= sortByDuitDescending(arr);
    for(auto i : sorted_arr1)
        cout << i << endl;

    cout << "--------------------------------------" << endl;
    cout << "--------------------------------------" << endl;
    cout << "--------------------------------------" << endl;
    
    for(auto i : sorted_arr2)
        cout << i << endl;


    return 0;
}