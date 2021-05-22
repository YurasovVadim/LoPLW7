#include <iostream>
#include <fstream>
#include <string>
#include "crypt.h"
#include <algorithm>
using namespace std;

void findPass(string pass, const string& hash)
{
    crypt_data *pCryptData = new crypt_data;
    size_t pos = hash.find_last_of('$');
    string hashHead = hash.substr(0,pos);
    do {
        string newHash(crypt_r(pass.data(),hashHead.data(),pCryptData));
        if (newHash == hash) {
            cout<<"Hash: "<<hash<<endl<<"Pass: "<<pass<<endl;
            break;
        }
    } while ( next_permutation( pass.begin(), pass.end() ) );
    delete pCryptData;
}


int main(int argc, char **argv)
{
    string hash;
    string pass = "123456789";
    ifstream f1("/home/student/hash.txt");
    while (getline(f1, hash)) {
        findPass(pass,hash);
    }
    f1.close();
    return 0;
}