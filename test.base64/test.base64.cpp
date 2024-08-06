#include <iostream>
#include <iomanip>
#include <string>

#include "base64.h"


using namespace std;

int main(int argc, char** argv)
{
    /*
    * https://www.base64encode.org/
    */
    {
        crypto::Base64 test("test", crypto::Base64::Encode);
        if (auto s = test.encode(); s == "dGVzdA==") cout << "Base64 encode - true" << endl;
        else cout << "Base64 encode - false" << endl;
    }
    {
        crypto::Base64 test("dGVzdA==", crypto::Base64::Decode);
        if (string s = (char*)test.decode(); s == "test") cout << "Base64 decode - true" << endl;
        else cout << "Base64 decode - false" << endl;
    }
    return 0;
}
