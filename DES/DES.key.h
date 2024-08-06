#ifndef _DES_KEY_H_
#define _DES_KEY_H_


#include <array>

#include <stdint.h>


using namespace std;

namespace crypto::key
{

constexpr const uint64_t c_key = 12345678;

using key56_t = array<char, 56>;

using key48_t = array<char, 48>;

using shift_t = array<char, 16>;

struct tables
{
    static key56_t pc_key_a;

    static key48_t pc_key_b;

    static shift_t shift;
}; // struct tables

} // namespace crypto::key


#endif // _DES_KEY_H_
