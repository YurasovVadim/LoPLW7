#include <iostream>
#include <fstream>
#include <string>
#include "crypt.h"
#include <algorithm>
#include <thread>
#include <mutex>
using namespace std;

void findPass(string pass, const string& hash)
{
    static mutex mtx;
    crypt_data *pCryptData = new crypt_data;
    size_t pos = hash.find_last_of('$');
    string hashHead = hash.substr(0,pos);
    do {
        string newHash(crypt_r(pass.data(),hashHead.data(),pCryptData));
        if (newHash == hash) {
            mtx.lock();
            cout<<"Hash: "<<hash<<endl<<"Pass: "<<pass<<endl;
            mtx.unlock();
            break;
        }
    } while ( next_permutation( pass.begin(), pass.end() ) );
    delete pCryptData;
}

int main(int argc, char **argv)
{
    string hash;
    string hashes[8];
    thread thread_array[8];
    ifstream f1;
    int x =0;
    f1.open("/home/student/hash.txt");
    while(!f1.eof()) {
        f1 >> hashes[x];
        x++;
    }
    for (int i=0; i<8; i++) {
        hash = hashes[i];
        thread_array[i] = thread(findPass, "123456789", hash);
    }
    for (int i=0; i<8; i++) {
        if (thread_array[i].joinable()) {
            thread_array[i].join();
        }
    }
    return 0;
}