#include "DES.CBC.h"


namespace crypto
{

static uint64_t swap_bytes(const uint64_t num) 
{
	uint64_t result = num;
	uint8_t* _l = (uint8_t*)&result, * _r = (uint8_t*)&result;
	for (int i = 0; i < 4; i++) std::swap(*(_l + i), *(_r + 7 - i));
	return result;
}

DESCBC::DESCBC(uint64_t key, uint64_t iv) 
	: m_des(swap_bytes(key))
{
	m_iv = swap_bytes(iv);
	reset();
}

uint64_t DESCBC::encrypt(uint64_t block)
{
	m_last_block = m_des.encrypt(block ^ m_last_block);
	return m_last_block;
}

uint64_t DESCBC::decrypt(uint64_t block)
{
	uint64_t b = swap_bytes(block);
	uint64_t result = swap_bytes(m_des.decrypt(b) ^ m_last_block);
	m_last_block = b;
	return result;
}

void DESCBC::reset()
{
	m_last_block = m_iv;
}

} // namespace crypto
