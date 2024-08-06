#include "DES.h"


namespace crypto
{

DES::DES() 
	: DES(key::c_key)
{
}

DES::DES(uint64_t key)
{
	keygen(key);
}

uint64_t DES::operator()(uint64_t block, bool mode)
{
    block = init(block);

    uint32_t _l = (uint32_t)(block >> 32) & stable::c_l64_mask;
    uint32_t _r = (uint32_t)(block & stable::c_l64_mask);

    for (uint8_t i = 0; i < 16; i++)
        feistel(_l, _r, (mode) ? (this->operator()(_r, m_sub_key[15 - i])) : (this->operator()(_r, m_sub_key[i])));

    block = (((uint64_t)_r) << 32) | (uint64_t)_l;

    return finaly(block);
}

uint64_t DES::encrypt(uint64_t block)
{
    return this->operator()(block, false);
}

uint64_t DES::decrypt(uint64_t block)
{
    return this->operator()(block, true);
}

uint64_t DES::encrypt(uint64_t block, uint64_t key)
{
    return DES(key)(block, false);
}

uint64_t DES::decrypt(uint64_t block, uint64_t key)
{
    return DES(key)(block, true);
}

void DES::keygen(uint64_t key)
{
    uint64_t _1 = 0; 
    for (auto&& it : key::tables::pc_key_a) 
    {
        _1 <<= 1;
        _1 |= (key >> (64 - it)) & stable::c_lb64_mask;
    }

    uint32_t _c = (uint32_t)((_1 >> 28) & stable::c_l64_mask);
    uint32_t _d = (uint32_t)(_1 & stable::c_l64_mask);

    for (uint8_t i = 0; i < key::tables::shift.size(); i++) 
    {
        for (uint8_t j = 0; j < key::tables::shift[i]; j++)
        {
            _c = (stable::c_l32_mask & (_c << 1)) | (stable::c_lb32_mask & (_c >> 27));
            _d = (stable::c_l32_mask & (_d << 1)) | (stable::c_lb32_mask & (_d >> 27));
        }

        uint64_t _2 = (((uint64_t)_c) << 28) | (uint64_t)_d;

        m_sub_key[i] = 0; 
        for (auto&& it : key::tables::pc_key_b) 
        {
            m_sub_key[i] <<= 1;
            m_sub_key[i] |= (_2 >> (56 - it)) & stable::c_lb64_mask;
        }
    }
}

uint64_t DES::init(uint64_t block)
{
    uint64_t result = 0;

    for (auto&& it : stable::tables::init) 
    {
        result <<= 1;
        result |= (block >> (64 - it)) & stable::c_lb64_mask;
    }

    return result;
}

uint64_t DES::finaly(uint64_t block)
{
    uint64_t result = 0;

    for (auto&& it : stable::tables::finaly) 
    {
        result <<= 1;
        result |= (block >> (64 - it)) & stable::c_lb64_mask;
    }

    return result;
}

void DES::feistel(uint32_t& _l, uint32_t& _r, uint32_t _f)
{
    uint32_t temp = _r;
    _r = _l ^ _f;
    _l = temp;
}

uint32_t DES::operator()(uint32_t _r, uint64_t _k)
{
    uint64_t _in = 0;
    for (auto&& it : stable::tables::extension_e) 
    {
        _in <<= 1;
        _in |= (uint64_t)((_r >> (32 - it)) & stable::c_lb32_mask);
    }

    _in ^= _k;

    uint32_t _out = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        char row = (char)((_in & (0x0000840000000000 >> 6 * i)) >> (42 - 6 * i));
        row = (row >> 4) | (row & 0x01);

        char column = (char)((_in & (0x0000780000000000 >> 6 * i)) >> (43 - 6 * i));

        _out <<= 4;
        _out |= (uint32_t)(stable::tables::s_box[i][16 * row + column] & 0x0f);
    }

    uint32_t result = 0;
    for (auto&& it : stable::tables::p_box)
    {
        result <<= 1;
        result |= (_out >> (32 - it)) & stable::c_lb32_mask;
    }

    return result;
}

} // namespace crypto
