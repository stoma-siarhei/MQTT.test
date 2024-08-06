#ifndef _BASE64_H_
#define _BASE64_H_


#include <string>


using namespace std;

namespace crypto
{

class Base64
{
public:
    enum mode { Encode = 1, Decode = 2 };

    Base64(string a_source, mode a_mode = Base64::Encode)
    {
        input_mode = a_mode;
        if (a_mode == Base64::Decode) {
            base64_string = a_source;
        }
        else if (a_mode == Base64::Encode) {
            source_string = a_source;
        }
    }

    string encode();

    unsigned char* decode();

    unsigned int b64(char a_char)
    {
        if (a_char >= 0x30 && a_char <= 0x39)
        {
            return (a_char - 0x30 + 0x34);
        }
        else if (a_char >= 0x41 && a_char <= 0x5A)
        {
            return (a_char - 0x41);
        }
        else if (a_char >= 0x61 && a_char <= 0x7A)
        {
            return (a_char - 0x61 + 0x1A);
        }
        else if (a_char == '+')
        {
            return 0x3E;
        }
        else if (a_char == '/')
        {
            return 0x3F;
        }
        else
        {
            return 0xFF;
        }
    }

private:
    size_t buffer_size{ 0 };
    string source_string;
    string base64_string;
    unsigned char* buffer{ nullptr };

    int input_mode;
}; // class Base64

} // namespace crypto


#endif // _BASE64_H_
