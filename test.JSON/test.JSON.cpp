#include <iostream>
#include <iomanip>
#include <string>


#include "JSON.hpp"

using namespace std;

int main(int argc, char** argv)
{
    namespace ss_t = ss::types;
    {
        /*{"cmd": 103,"data": "BmcA0GkPBMv2Kpzu0V6W2kfDiNIGuM9iHDPxrCIOKfsdGoItzduC5oYBjrBAXMuW4enfWr2GJ/jd4PRET5/w9ovhX1U4o2MDSl9zzOpQi31yfzCKl5iDqcZ3H7lbOELq"}*/
        ss_t::string j_crypto{ "{\"cmd\": 103,\"data\": \"BmcA0GkPBMv2Kpzu0V6W2kfDiNIGuM9iHDPxrCIOKfsdGoItzduC5oYBjrBAXMuW4enfWr2GJ/jd4PRET5/w9ovhX1U4o2MDSl9zzOpQi31yfzCKl5iDqcZ3H7lbOELq\"}" };
        ss::lib::parse::json j(j_crypto);
        j();
        j.m_head;
    }
    {
        /*{"cmd": 103,"data": {"message": 335871,"reason": "Lock is open","Type": 14,"electricNum": 100,"lockState": 3}}*/
        ss_t::string j_str{"{\"cmd\": 103,\"data\": {\"message\": 335871,\"reason\": \"Lock is open\",\"Type\": 14,\"electricNum\": 100,\"lockState\": 3}}"};
    }
    return 0;
}
