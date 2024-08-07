#include "JSON.hpp"


using namespace std;

namespace ss::lib
{

#ifdef _UNICODE
wchar_t c_json::open_record = L'{';
wchar_t c_json::close_record = L'}';

wchar_t c_json::open_array = L'[';
wchar_t c_json::close_array = L']';

wchar_t c_json::delimiter = L':';

wchar_t c_json::quota_1 = L'\"';
wchar_t c_json::quota_2 = L'\'';
#else
char c_json::open_record = '{';
char c_json::cose_record = '}';

char c_json::open_array = '[';
char c_json::cose_array = ']';

char c_json::deimiter = ':';

char c_json::quota_1 = '\"';
char c_json::quota_2 = '\'';
#endif // _UNICODE

}

namespace ss::lib::parse
{

namespace ss_t = ss::types;

parse::range_pair::range_pair(const lrange_t& l, const rrange_t& r, ss_t::bracket_t o, ss_t::bracket_t c)
	: m_l(l), m_r(r), m_open(o), m_close(c)
{
}

range_pair::vector_pair_t ss::lib::parse::range_pair::operator()()
{
	ss_t::mass_pos_type_t mt;

	ss::lib::transform(m_l, mt, m_open);
	ss::lib::transform(m_r, mt, m_close);
	ss::lib::sort(mt);

	for (auto it{ begin(mt) }; it != end(mt); it++)
	{
		auto&& [_pos1, _type1] = *it;
		if (_type1 == m_close) continue;

		auto _open{ 1 };
		for (auto itt{ it + 1 }; itt != end(mt); itt++)
		{
			auto&& [_pos2, _type2] = *itt;
			if (_type2 == m_open) _open++;
			else _open--;
			if (_open != 0) continue; 
			m_vector.push_back({ _pos1, _pos2 });
			break;
		}
	}
	
	return m_vector;
}

ss::lib::parse::json_data::json_data(const ss_t::string_view json, ss_t::position_t l, ss_t::position_t r) noexcept
	: m_json(json.begin() + l + 1, json.begin() + r), m_left(l), m_right(r)
{
}

inline bool json_data::operator==(const json_data& r) const noexcept
{
	return (r.m_left == m_left) && (r.m_right == m_right);
}

inline bool json_data::operator!=(const json_data& r) const noexcept
{
	return !operator==(r);
}

inline bool json_data::operator<(const json_data& r) const noexcept
{
	return r.m_left < m_left;
}

inline bool json_data::operator>(const json_data& r) const noexcept
{
	return r.m_right > m_right;
}

node_data::node_data(const json_data& data) noexcept
	: m_json_data(data)
{
}

inline bool node_data::operator==(const node_data& r) const noexcept
{
	return m_json_data == r.m_json_data;
}

inline bool node_data::operator!=(const node_data& r) const noexcept
{
	return m_json_data != r.m_json_data;
}

inline bool node_data::operator<(const node_data& r) const noexcept
{
	return m_json_data < r.m_json_data;
}

inline bool node_data::operator>(const node_data& r) const noexcept
{
	return r.m_json_data > m_json_data;
}

node::node(const node_data& data) noexcept
	: m_node_data(data), m_id(m_sequence())
{
	parse();
}

node::node(node_ptr_t p, const node_data& data) noexcept
	: parent(p), m_node_data(data), m_id(m_sequence())
{
	parse();
}

node::node(node_ptr_t p, node_ptr_t b, const node_data& data) noexcept
	: node(p, data)
{
	b->next = this;
	back = b;
}

bool node::add(const node_data& data)
{
	node_ptr_t _node{ this };
	for (_node = this; _node->next != nullptr; _node = _node->next);
	if ((data < _node->m_node_data) && (_node->m_node_data > data))
	{
		if (node_ptr_t _n = _node->child; _n == nullptr)
		{
			_node->child = new node(_node, data);
			if (_node->child == nullptr) return false;
		}
		else _n->add(data);
	}
	else
	{ 
		if (node_ptr_t _n = new node(_node, get_end(), data); _n == nullptr) return false;
	}
	return true;
}

void node::del()
{
	if (node_ptr_t _node = this->child; _node != nullptr)
	{
		_node->del();
		delete _node;
	}
	for (auto&& _pair = get_pair_end(); get<0>(_pair) != this; _pair = get_pair_end())
	{
		auto&& [_node, _back] = _pair;
		_node->del();
		_back->next = nullptr;
		delete _node;
	}
}

node::node_ptr_t node::get_end() noexcept
{
	auto&& [_node, _b] = get_pair_end();
	return _node;
}

node::pair_list_t node::get_pair_end() noexcept
{
	node_ptr_t _node{ this }, _back{ nullptr };
	for (; _node->next != nullptr; _back = _node, _node = _node->next);
	return { _node, _back };
}

void node::parse() noexcept
{
	auto str{ m_node_data.m_json_data.m_json };

	auto end_parse = [&]() -> size_t { return min(str.find(c_json::open_record), str.find(c_json::open_array)); };

	auto begin_parse = [&]() -> size_t { return min(str.find(c_json::quota_1), str.find(c_json::quota_2)); };

	if (auto&& [_1, _2] = make_tuple(begin_parse(), end_parse()); (_1 == ss_t::string::npos) || (_1 > _2)) return;

	str = str.substr(0, end_parse());
	ss_t::char_t ch{ c_json::quota_1 };

	if (auto&& [_1, _2] = make_tuple(str.find(c_json::quota_1), str.find(c_json::quota_2)); (_1 != ss_t::string::npos) && (_2 != ss_t::string::npos)) return;
	else if (_2 != ss_t::string::npos) ch = c_json::quota_2;

	vector<tuple<size_t, size_t>> v;
	for (size_t _pos = 0; _pos != ss_t::string::npos; _pos++)
		if (_pos = str.find(ch, _pos); _pos != ss_t::string::npos)
		{
			auto _1{ _pos++ };
			if (_pos = str.find(ch, _pos); _pos != ss_t::string::npos) v.push_back({ _1, _pos });
			else return;
		}
		else break;

	for (size_t i = 0; i < v.size() - 1;)
	{
		auto&& [s1, e1] = v[i];
		auto&& [s2, e2] = v[i + 1];
		ss_t::string _key{ str.begin() + s1 + 1, str.begin() + e1 }, _val{ str.begin() + e1 + 1, str.begin() + s2 };
		if (is_number_str(_val))
		{
			_val = get_number_str(_val);
			i += 1;
		}
		else
		{
			_val = str.substr(s2 + 1, e2 - s2 - 1);
			i += 2;
		}
		m_map_data.insert({ _key, _val });
	}
}

json::json() 
{
}

json::json(const ss_t::string& j) 
	: m_json(j)
{
}

json::~json()
{
	m_head->del();
	delete m_head;
}

bool json::operator()()
{
	return parse();
}

bool json::operator()(const ss_t::string& j)
{
	m_json = j;
	return parse();
}

bool json::parse()
{
	if (check_parse() == false) return false;

	if (m_head != nullptr) delete m_head;

	auto v_rec = range_pair(m_open_rec, m_close_rec, ss_t::bracket_t::open_rec, ss_t::bracket_t::close_rec)();
	auto v_arr = range_pair(m_open_arr, m_close_arr, ss_t::bracket_t::open_arr, ss_t::bracket_t::close_arr)();

	for (auto index{ 0 }; auto&& [l, r] : v_rec)
	{
		m_mass_node.push_back(node_data(json_data(m_json, l, r)));
		if (index == 0)
		{
			m_head = new node(m_mass_node[index++]);
			if (m_head == nullptr) return false;
		}
		else if (bool b = m_head->add(m_mass_node[index++]); b == false) return false;
	}

	return true;
}

bool json::check_parse()
{	
	auto f = [&](ss_t::mass_pos_t& mass, ss_t::char_t ch) {
		for (size_t _pos = 0; _pos != ss_t::string::npos; _pos++)
			if (_pos = m_json.find(ch, _pos); _pos != ss_t::string::npos)
				mass.push_back(static_cast<uint32_t>(_pos));
			else
				break;
		return true;
		};

	f(m_open_rec, ss::lib::c_json::open_record);
	f(m_close_rec, ss::lib::c_json::close_record);
	f(m_open_arr, ss::lib::c_json::open_array);
	f(m_close_arr, ss::lib::c_json::close_array);
	f(m_delimiter, ss::lib::c_json::delimiter);

	return (m_open_rec.size() == m_close_rec.size()) && (m_open_arr.size() == m_close_arr.size());
}

} // namespace ss::lib::parse
