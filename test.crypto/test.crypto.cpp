#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "base64.h"
#include "DES.CBC.h"


using namespace std;

int main(int argc, char** argv)
{
    {
        /*mTkvFxOd/NH9MEkOxY7czmeTu3OqTRgPRkdIwmUFHhfiO6eLEMud8k3Uc0XE4w==*/
        string s{ "mTkvFxOd/NH9MEkOxY7czmeTu3OqTRgPRkdIwmUFHhfiO6eLEMud8k3Uc0XE4w==" };
        crypto::Base64 base(s, crypto::Base64::Decode);
        uint8_t* ptr = base.decode();
        size_t size = base.size();
        vector<uint64_t> v(size / 8 + 1);
        vector<uint64_t> res;
        memcpy((void*)v.data(), (void*)ptr, size);
        string key{ "12345678" };
        uint64_t* pkey = (uint64_t*)key.data();
        crypto::DESCBC des(*pkey, *pkey);
        for (auto&& it : v)
        {
            res.push_back(des.decrypt(it));
        }
        string str((char*)res.data());
        cout << str << endl;
    }
    {
        /*b5tdXnn7oyuXB22UG8WKFB0/5pXmyoZzKC8HgL5xL55y90vhl2gxLJ9KzCvLVL3yA14ABkr1gwYu2LFhb7J3AAfX+G/PP9kQG6BsJtWE412Riwu7H+k/BQ==*/
    }
    {
        /*BmcA0GkPBMv2Kpzu0V6W2kfDiNIGuM9iHDPxrCIOKfsdGoItzduC5oYBjrBAXMuW4enfWr2GJ/jd4PRET5/w9ovhX1U4o2MDSl9zzOpQi31yfzCKl5iDqcZ3H7lbOELq*/
    }
    return 0;
}
