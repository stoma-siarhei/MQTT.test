#ifndef _DES_CBC_H_
#define _DES_CBC_H_


#include "stdint.h"

#include "DES.h"


namespace crypto
{

class DESCBC 
{
public:
    DESCBC(uint64_t key, uint64_t iv);

    uint64_t encrypt(uint64_t block);

    uint64_t decrypt(uint64_t block);

    void reset();

private:
    DES m_des;
    uint64_t m_iv;
    uint64_t m_last_block;
}; // class DESCBC 

} // namespace crypto


#endif // _DES_CBC_H_
