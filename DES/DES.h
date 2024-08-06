#ifndef _DES_H_
#define _DES_H_


#include <stdint.h>

#include "DES.key.h"
#include "DES.lookup.h"


namespace crypto
{

class DES
{
public:
    DES();

    DES(uint64_t key);

    uint64_t operator()(uint64_t block, bool mode);

    uint64_t encrypt(uint64_t block);

    uint64_t decrypt(uint64_t block);

    static uint64_t encrypt(uint64_t block, uint64_t key);

    static uint64_t decrypt(uint64_t block, uint64_t key);

protected:
    void keygen(uint64_t key);

    uint64_t init(uint64_t block);

    uint64_t finaly(uint64_t block);

    void feistel(uint32_t& _l, uint32_t& _r, uint32_t _f);

    uint32_t operator()(uint32_t _r, uint64_t _k);

private:
    uint64_t m_sub_key[16]{ 0 };
}; // class DES

} // namespace crypto


#endif // _DES_H_
