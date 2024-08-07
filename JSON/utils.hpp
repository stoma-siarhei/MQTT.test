#ifndef _UTILS_HPP_
#define _UTILS_HPP_


#include <algorithm>

#include "primitive.hpp"


namespace ss_t = ss::types;

namespace ss::lib
{

struct c_mass
{
	static ss_t::string numbers;
}; // struct c_mass

template <typename _In, typename _Out>
void transform(const _In& in, _Out& out, ss::types::bracket_t br)
{
	size_t step = out.size();
	out.resize(step + in.size());
	std::transform(in.begin(), in.end(), out.begin() + step,
		[=](auto& elem) -> _Out::value_type
		{
			return { elem, br };
		});
}

template <typename _Mass>
void sort(_Mass& v)
{
	std::sort(v.begin(), v.end(),
		[](auto& a, auto& b)
		{
			auto& [a1, a2] = a;
			auto& [b1, b2] = b;
			return a1 < b1;
		});
}

bool is_number_str(const ss_t::string_view str);

ss_t::string_view get_number_str(const ss_t::string_view str);

class sequence
{
public:
	static sequence& instance();

	size_t operator()() noexcept;
private:
	sequence();
	sequence(const sequence&) = delete;
	sequence& operator=(const sequence&) = delete;

	size_t m_number{ 0 };
}; // class sequence

} // namespace ss::lib


#endif // _UTILS_HPP_
