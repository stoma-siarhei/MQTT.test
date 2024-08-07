#ifndef _JSON_HPP_
#define _JSON_HPP_


#include <vector>
#include <tuple>
#include <unordered_map>

#include <stdint.h>

#include "primitive.hpp"
#include "utils.hpp"


namespace ss::lib
{

struct c_json
{
#ifdef _UNICODE
	static wchar_t open_record;
	static wchar_t close_record;

	static wchar_t open_array;
	static wchar_t close_array;

	static wchar_t delimiter;

	static wchar_t quota_1;
	static wchar_t quota_2;
#else
	static char open_record;
	static char cose_record;

	static char open_array;
	static char cose_array;

	static char deimiter;

	static char quota_1;
	static char quota_2;
#endif // _UNICODE
}; // struct c_json

namespace parse 
{

namespace ss_t = ss::types;

struct range_pair
{
	using lrange_t = ss_t::mass_pos_t;
	using rrange_t = ss_t::mass_pos_t;

	using pair_t = std::tuple<ss_t::position_t, ss_t::position_t>;

	using vector_pair_t = std::vector<pair_t>;

	range_pair() = delete;

	range_pair(const lrange_t& l, const rrange_t& r, ss_t::bracket_t o, ss_t::bracket_t c);

	vector_pair_t operator()();

private:
	const lrange_t& m_l;
	const rrange_t& m_r;
	ss_t::bracket_t m_open, m_close;
	vector_pair_t m_vector;
}; // struct range_pair

struct json_data
{
	json_data() = delete;

	explicit json_data(const ss_t::string_view json, ss_t::position_t l, ss_t::position_t r) noexcept;

	inline bool operator==(const json_data& r) const noexcept;

	inline bool operator!=(const json_data& r) const noexcept;
	
	inline bool operator<(const json_data& r) const noexcept;

	inline bool operator>(const json_data& r) const noexcept;

	ss_t::string_view m_json;
	ss_t::position_t m_left, m_right;
}; // struct json_data

struct node_data
{
	node_data() = delete;

	explicit node_data(const json_data& data) noexcept;

	inline bool operator==(const node_data& r) const noexcept;

	inline bool operator!=(const node_data& r) const noexcept;

	inline bool operator<(const node_data& r) const noexcept;

	inline bool operator>(const node_data& r) const noexcept;

	json_data m_json_data;
}; // struct node_data

struct node
{
	using node_ptr_t = struct node*;

	using pair_list_t = std::tuple<node_ptr_t, node_ptr_t>;

	using map_data_t = std::unordered_map<ss_t::string, ss_t::string>;

	node() = delete;

	explicit node(const node_data& data) noexcept;

	explicit node(node_ptr_t p, const node_data& data) noexcept;

	explicit node(node_ptr_t p, node_ptr_t b, const node_data& data) noexcept;

	node_ptr_t parent{ nullptr }, next{ nullptr }, back{ nullptr }, child{ nullptr };

	bool add(const node_data& data);

	void del();

private:
	node_ptr_t get_end() noexcept;

	pair_list_t get_pair_end() noexcept;

	void parse() noexcept;

	node_data m_node_data;

	sequence& m_sequence{ sequence::instance() };

	size_t m_id{ 0 };
	ss_t::string_view m_name;
	map_data_t m_map_data;
}; // struct node

class json
{
public:
	using open_rec_t = ss_t::mass_pos_t;
	using close_rec_t = ss_t::mass_pos_t;

	using open_arr_t = ss_t::mass_pos_t;
	using close_arr_t = ss_t::mass_pos_t;

	using delimiter_t = ss_t::mass_pos_t;

	using mass_node_t = std::vector<node_data>;

	using node_ptr_t = node::node_ptr_t;
public:
	json();

	json(const ss_t::string& j);

	~json();

	bool operator()();

	bool operator()(const ss_t::string& j);
#ifndef _DEBUG
protected:
#endif // _DEBUG
	bool parse();

	bool check_parse();
#ifndef _DEBUG
private:
#endif // _DEBUG
	ss_t::string m_json;
	open_rec_t m_open_rec;
	close_rec_t m_close_rec;
	open_arr_t m_open_arr;
	close_arr_t m_close_arr;
	delimiter_t m_delimiter;

	mass_node_t m_mass_node;

	node_ptr_t m_head{ nullptr };
}; // class json

} // namespace parse

} // namespace ss::lib


#endif // _JSON_HPP_
