#ifndef _PRIMITIVE_HPP_
#define _PRIMITIVE_HPP_


#include <string>
#include <string_view>
#include <vector>
#include <tuple>

#include <stdint.h>


namespace ss::types
{

#if defined(_UNICODE) && !defined(_USE_CHAR)
using char_t = wchar_t;
using string = std::wstring;
using string_view = std::wstring_view;
#else
using char_t = char;
using string = std::string;
using string_view = std::string_view;
#endif // defined(_UNICODE) && !defined(_USE_CHAR)

enum class bracket_t : uint8_t
{
	open_rec = 0,
	close_rec = 1,
	open_arr = 2,
	close_arr = 3
}; // enum class bracket_t

using namespace std;

using key_level_t = uint16_t;

using position_t = uint32_t;

using mass_pos_t = vector<position_t>;

using position_type_t = tuple<position_t, bracket_t>;

using mass_pos_type_t = vector<position_type_t>;

} // namespace ss::types


#endif // _PRIMITIVE_HPP_
