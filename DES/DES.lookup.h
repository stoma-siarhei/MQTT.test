#ifndef _DES_LOOKUP_H_
#define _DES_LOOKUP_H_


#include <array>

#include <stdint.h>


using namespace std;

namespace crypto::stable
{

constexpr const uint32_t c_lb32_mask{ 0x00000001 };

constexpr const uint32_t c_l32_mask{ 0x0fffffff };

constexpr const uint64_t c_lb64_mask{ 0x0000000000000001 };

constexpr const uint64_t c_l64_mask{ 0x00000000ffffffff };

constexpr const uint64_t c_h64_mask{ 0xffffffff00000000 };

using permutation64_t = array<char, 64>;

using extension48_t = array<char, 48>;

using pbox_t = array<char, 32>;

using sbox_t = char[8][64];

struct tables
{
	static permutation64_t init;

	static permutation64_t finaly;

	static extension48_t extension_e;

	static pbox_t p_box;

	static sbox_t s_box;
}; // struct tables

} // namespace crypto::stable

#endif // _DES_LOOKUP_H_
