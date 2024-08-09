#ifndef _MQTT_IMPL_H_ 
#define _MQTT_IMPL_H_


#include "pch.h"

#include "default.param.hpp"


namespace mqtt
{

class mqtt_impl
{
public:
	using mqtt_t = MQTTClient;

	using options_t = MQTTClient_connectOptions;

public:
	explicit mqtt_impl();

	explicit mqtt_impl(const char* addr);

	explicit mqtt_impl(const string_view addr);

	explicit mqtt_impl(const char* addr, const char* id);

	explicit mqtt_impl(const string_view addr, const string_view id);

	~mqtt_impl() noexcept;

	mqtt_t& get() const noexcept;

	options_t& options() const noexcept;
protected:

private:
	mqtt_t m_client{};
#if MQTT_VER == 5
	option_t m_options = MQTTClient_connectOptions_initializer5
#else
	options_t m_options = MQTTClient_connectOptions_initializer;
#endif // MQTT_VER == 5
}; // class mqtt_impl

} // namespace mqtt


#endif // _MQTT_IMPL_H_
