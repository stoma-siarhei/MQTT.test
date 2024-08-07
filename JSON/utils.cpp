#include "utils.hpp"


namespace ss::lib
{

ss_t::string c_mass::numbers =
#ifdef _UNICODE
		L"1234567890";
#else
		"1234567890";
#endif // _UNICODE

bool is_number_str(const ss_t::string_view str)
{
#ifdef _UNICODE
	if (size_t p = wcscspn(str.data(), c_mass::numbers.data()); p >= str.size()) return false;
#else
	if (size_t p = strcspn(str.data(), c_mass::numbers.data()); p >= str.size()) return false;
#endif // _UNICODE

	return true;
}

ss_t::string_view get_number_str(const ss_t::string_view str)
{
	size_t _begin, _end;

#ifdef _UNICODE
	_begin = wcscspn(str.data(), c_mass::numbers.data());
	_end = wcsspn(str.data() + _begin, c_mass::numbers.data()) + _begin;
#else
	_begin = strcspn(str.data(), c_mass::numbers.data());
	_end = strspn(str.data() + _begin, c_mass::numbers.data()) + _begin;
#endif // _UNICODE

	if ((_begin == _end) || (_end > str.size())) return ss_t::string_view();

	return ss_t::string_view(str.begin() + _begin, str.begin() + _end);
}

sequence::sequence()
{
}

sequence& sequence::instance()
{
	static sequence _sequence;
	return _sequence;
}

size_t sequence::operator()() noexcept
{
	return ++m_number;
}

} // namespace ss::lib
