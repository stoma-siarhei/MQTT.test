#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "base64.h"
#include "DES.CBC.h"


using namespace std;

int main(int argc, char** argv)
{
    /*
    * https://the-x.cn/en-us/cryptography/Des.aspx
    */
    {
        /*mTkvFxOd/NH9MEkOxY7czmeTu3OqTRgPRkdIwmUFHhfiO6eLEMud8k3Uc0XE4w==*/
        string data{ "mTkvFxOd/NH9MEkOxY7czmeTu3OqTRgPRkdIwmUFHhfiO6eLEMud8k3Uc0XE4w==" };
        crypto::Base64 b{ data, crypto::Base64::Decode };
        uint8_t* p_data = b.decode();
        [[like]] if (auto size = b.size() - 1; size % 8 == 0)
        {
            vector<uint64_t> v_data(size / 8), v_res(size / 8);
            v_res[v_res.size() - 1] = 0;
            memcpy((void*)v_data.data(), (void*)p_data, size);
            string key{ "87654321" };
            uint64_t* p_key = (uint64_t*)key.data();
            crypto::DESCBC des(*p_key, *p_key);
            for (size_t i = 0; auto && it : v_data)
            {
                if (i == v_res.size()) break;
                uint64_t b = it;
                uint8_t* _l = (uint8_t*)&b, * _r = (uint8_t*)&b;
                for (int i = 0; i < 4; i++)
                {
                    std::swap(*(_l + i), *(_r + 7 - i));
                }
                b = des.decrypt(b);
                for (int i = 0; i < 4; i++)
                {
                    std::swap(*(_l + i), *(_r + 7 - i));
                }
                v_res[i++] = b;
            }
            string result{ (char*)&v_res[0] };
            cout << result << endl;
        }
        else
        {
            cout << "Error decode base64" << endl;
        }
    }
    {
        /*b5tdXnn7oyuXB22UG8WKFB0/5pXmyoZzKC8HgL5xL55y90vhl2gxLJ9KzCvLVL3yA14ABkr1gwYu2LFhb7J3AAfX+G/PP9kQG6BsJtWE412Riwu7H+k/BQ==*/
        string data{ "b5tdXnn7oyuXB22UG8WKFB0/5pXmyoZzKC8HgL5xL55y90vhl2gxLJ9KzCvLVL3yA14ABkr1gwYu2LFhb7J3AAfX+G/PP9kQG6BsJtWE412Riwu7H+k/BQ==" };
        crypto::Base64 b{ data, crypto::Base64::Decode };
        uint8_t* p_data = b.decode();
        [[like]] if (auto size = b.size() - 1; size % 8 == 0)
        {
            vector<uint64_t> v_data(size / 8), v_res(size / 8);
            v_res[v_res.size() - 1] = 0;
            memcpy((void*)v_data.data(), (void*)p_data, size);
            string key{ "87654321" };
            uint64_t* p_key = (uint64_t*)key.data();
            crypto::DESCBC des(*p_key, *p_key);
            for (size_t i = 0; auto && it : v_data)
            {
                if (i == v_res.size()) break;
                uint64_t b = it;
                uint8_t* _l = (uint8_t*)&b, * _r = (uint8_t*)&b;
                for (int i = 0; i < 4; i++)
                {
                    std::swap(*(_l + i), *(_r + 7 - i));
                }
                b = des.decrypt(b);
                for (int i = 0; i < 4; i++)
                {
                    std::swap(*(_l + i), *(_r + 7 - i));
                }
                v_res[i++] = b;
            }
            string result{ (char*)&v_res[0] };
            cout << result << endl;
        }
        else
        {
            cout << "Error decode base64" << endl;
        }
    }
    {
        /*BmcA0GkPBMv2Kpzu0V6W2kfDiNIGuM9iHDPxrCIOKfsdGoItzduC5oYBjrBAXMuW4enfWr2GJ/jd4PRET5/w9ovhX1U4o2MDSl9zzOpQi31yfzCKl5iDqcZ3H7lbOELq*/
        string data{ "BmcA0GkPBMv2Kpzu0V6W2kfDiNIGuM9iHDPxrCIOKfsdGoItzduC5oYBjrBAXMuW4enfWr2GJ/jd4PRET5/w9ovhX1U4o2MDSl9zzOpQi31yfzCKl5iDqcZ3H7lbOELq" };
        crypto::Base64 b{ data, crypto::Base64::Decode };
        uint8_t* p_data = b.decode();
        [[like]] if (auto size = b.size() - 1; size % 8 == 0)
        {
            vector<uint64_t> v_data(size / 8), v_res(size / 8);
            v_res[v_res.size() - 1] = 0;
            memcpy((void*)v_data.data(), (void*)p_data, size);
            string key{ "87654321" };
            uint64_t* p_key = (uint64_t*)key.data();
            crypto::DESCBC des(*p_key, *p_key);
            for (size_t i = 0; auto && it : v_data)
            {
                if (i == v_res.size()) break;
                uint64_t b = it;
                uint8_t* _l = (uint8_t*)&b, * _r = (uint8_t*)&b;
                for (int i = 0; i < 4; i++)
                {
                    std::swap(*(_l + i), *(_r + 7 - i));
                }
                b = des.decrypt(b);
                for (int i = 0; i < 4; i++)
                {
                    std::swap(*(_l + i), *(_r + 7 - i));
                }
                v_res[i++] = b;
            }
            string result{ (char*)&v_res[0] };
            cout << result << endl;
        }
        else
        {
            cout << "Error decode base64" << endl;
        }
    }
    return 0;
}
