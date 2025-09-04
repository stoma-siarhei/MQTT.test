#include <iostream>
#include <iomanip>
#include <string>


using namespace std;

int main(int argc, char** argv)
{
    auto parse_data = [](string_view str)
        {
            if (size_t _1 = str.find("data"); _1 != string::npos) 
            { 
                if (size_t _2 = str.find(":", _1); _2 != string::npos)
                { 
                    if (auto _p = make_tuple(str.find("\"", _2), str.rfind("\"")); _p != make_tuple(string::npos, string::npos))
                    { 
                        return string{ str.begin() + get<0>(_p) + 1, str.begin() + get<1>(_p) };
                    }
                }
            }
            return string{ "" }; 
        };

    auto parse_cmd = [](string_view str)
        {
            if (size_t _1 = str.find("cmd"); _1 != string::npos)
            {
                if (auto _p = make_tuple(str.find_first_of("1234567890"), str.find_last_of("1234567890")); _p != make_tuple(string::npos, string::npos))
                {
                    return stoi(string{ str.begin() + get<0>(_p), str.begin() + get<1>(_p) });
                }
            }
            return -1;
        };

    auto parse_102 = [](string_view str)
        {
            if (size_t _1 = str.find("codersn"); _1 != string::npos)
            {
                if (size_t _2 = str.find(":", _1); _2 != string::npos)
                {
                    if (auto _p = make_tuple(str.find_first_not_of("\": ", _1 + 7), str.find(",", _1)); _p != make_tuple(string::npos, string::npos))
                    {
                        return string{ str.begin() + get<0>(_p) + 1, str.begin() + get<1>(_p) - 1 };
                    }
                }
            }
            return string{ "" };
        };

    auto parse_103 = [](string_view str)
        {
            if (size_t _1 = str.find("reason"); _1 != string::npos)
            {
                if (size_t _2 = str.find(":", _1); _2 != string::npos)
                {
                    if (auto _p = make_tuple(str.find_first_not_of("\": ", _1 + 6), str.find(",", _1)); _p != make_tuple(string::npos, string::npos))
                    {
                        return string{ str.begin() + get<0>(_p), str.begin() + get<1>(_p) - 1 };
                    }
                }
            }
            return string{ "" };
        };

    {
        /*{"cmd": 103,"data": "BmcA0GkPBMv2Kpzu0V6W2kfDiNIGuM9iHDPxrCIOKfsdGoItzduC5oYBjrBAXMuW4enfWr2GJ/jd4PRET5/w9ovhX1U4o2MDSl9zzOpQi31yfzCKl5iDqcZ3H7lbOELq"}*/
        string j_crypto{ "{\"cmd\": 103,\"data\": \"BmcA0GkPBMv2Kpzu0V6W2kfDiNIGuM9iHDPxrCIOKfsdGoItzduC5oYBjrBAXMuW4enfWr2GJ/jd4PRET5/w9ovhX1U4o2MDSl9zzOpQi31yfzCKl5iDqcZ3H7lbOELq\"}" };
        cout << parse_cmd(j_crypto) << endl;
        cout << parse_data(j_crypto) << endl;
    }
    {
        /*{“cmd”: 102,“data”: {“codersn”: MNR632D5647EC0,“operator”: "Админ","Mac": "0cec80f97055","Type": 5}}*/
        string j_str{ "{\"cmd\": 102,\"data\": {\"codersn\": MNR632D5647EC0,\"operator\": \"Админ\",\"Mac\": \"0cec80f97055\",\"Type\": 5}}" };
        cout << parse_cmd(j_str) << endl;
        cout << parse_102(j_str) << endl;
    }
    {
        /*{"cmd": 103,"data": {"message": 335871,"reason": "Lock is open","Type": 14,"electricNum": 100,"lockState": 3}}*/
        string j_str{ "{\"cmd\": 103,\"data\": {\"message\": 335871,\"reason\": \"Lock is open\",\"Type\": 14,\"electricNum\": 100,\"lockState\": 3}}" };
        cout << parse_cmd(j_str) << endl;
        cout << parse_103(j_str) << endl;
    }
    return 0;
}
