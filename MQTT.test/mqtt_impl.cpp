#include "mqtt_impl.h"


using namespace std;

namespace mqtt
{

mqtt_impl::mqtt_impl() 
	: mqtt_impl(c_address, c_client_id)
{
}

mqtt_impl::mqtt_impl(const char* addr) 
	: mqtt_impl(addr, c_client_id)
{
}

mqtt_impl::mqtt_impl(const string_view addr) 
	: mqtt_impl(addr.data())
{
}

mqtt_impl::mqtt_impl(const char* addr, const char* id)
{
	if (auto r = MQTTClient_create(&m_client, addr, id, MQTTCLIENT_PERSISTENCE_NONE, nullptr); r != MQTTCLIENT_SUCCESS) 
	{
		m_client = 0;
		throw system_error(error_code(r, system_category()), "Failed create client");
	}
	m_options.keepAliveInterval = c_interval;
	m_options.cleansession = c_clean_session;
}

mqtt_impl::mqtt_impl(const string_view addr, const string_view id) 
	: mqtt_impl(addr.data(), id.data())
{
}

mqtt_impl::~mqtt_impl() noexcept
{
	if (m_client) MQTTClient_destroy(&m_client);
}

mqtt_impl::mqtt_t& mqtt_impl::get() const noexcept
{
	return add_lvalue_reference_t<mqtt_t>(m_client);
}

mqtt_impl::options_t& mqtt_impl::options() const noexcept
{
	return add_lvalue_reference_t<options_t>(m_options);
}

} // namespace mqtt
