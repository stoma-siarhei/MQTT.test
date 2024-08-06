#include <iostream>
#include <iomanip>
#include <string>

#include "DES.CBC.h"


using namespace std;

int main(int argc, char** argv)
{
    /*
    * https://the-x.cn/en-us/cryptography/Des.aspx
    */
    {
        crypto::DES des(0x8000000000000000);
        if (auto _r = des.encrypt(0); _r == 0x95a8d72813daa94d) cout << "Encrypt - True" << endl;
        else cout << "Encrypt - False" << endl;
    }
    {
        if (auto _r = crypto::DES::decrypt(0x95a8d72813daa94d, 0x8000000000000000); _r == 0) cout << "Decrypt - True" << endl;
        else cout << "Decrypt - False" << endl;
    }
    {
        string str{ "texttext" };
        uint64_t block = *((uint64_t*)str.data());
        if (auto _r = crypto::DES::encrypt(block, block); _r == 0x6d3df7e513a79f66) cout << "Encrypt - True" << endl;
        else cout << "Encrypt - False" << endl;
    }
    return 0;
}
