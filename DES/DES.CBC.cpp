#include "DES.CBC.h"


namespace crypto
{

DESCBC::DESCBC(uint64_t key, uint64_t iv) 
	: m_des(key), m_iv(iv), m_last_block(iv)
{
}

uint64_t DESCBC::encrypt(uint64_t block)
{
	m_last_block = m_des.encrypt(block ^ m_last_block);
	return m_last_block;
}

uint64_t DESCBC::decrypt(uint64_t block)
{
	uint64_t result = m_des.decrypt(block) ^ m_last_block;
	m_last_block = block;
	return result;
}

void DESCBC::reset()
{
	m_last_block = m_iv;
}

} // namespace crypto
