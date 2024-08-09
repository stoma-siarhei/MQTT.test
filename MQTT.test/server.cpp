#include "server.h"


namespace mqtt::subscription
{

subscribe::subscribe() 
	: subscribe(c_address, c_client_id)
{
}

subscribe::subscribe(const char* addr) 
	: subscribe(addr, c_client_id)
{
}

subscribe::subscribe(const string_view addr) 
	: subscribe(addr.data())
{
}

subscribe::subscribe(const char* addr, const char* id) 
	: mqtt_impl(addr, id)
{
    if (auto r = MQTTClient_setCallbacks(get(), nullptr, subscribe::connection_lost, subscribe::message_arrived, subscribe::delivery_complete); r != MQTTCLIENT_SUCCESS)
    {
        throw system_error(error_code(r, system_category()), "Error setup callback function");
    }
    if (auto r = MQTTClient_connect(get(), &options()); r != MQTTCLIENT_SUCCESS)
    {
        throw system_error(error_code(r, system_category()), "Failed connect");
    }
    m_connected = true;
}

subscribe::subscribe(const string_view addr, const string_view id) 
	: subscribe(addr.data(), id.data())
{
}

subscribe::~subscribe() noexcept
{
    for (auto&& it : m_list_s)
    {
        MQTTClient_unsubscribe(get(), it.data());
    }
    if (m_connected)
    {
        MQTTClient_disconnect(get(), c_interval);
    }
}

void subscribe::operator()()
{
    operator()(c_channel_s);
}

void subscribe::operator()(const string_view msg)
{
    if (auto r = MQTTClient_subscribe(get(), msg.data(), c_qos); r != MQTTCLIENT_SUCCESS)
    {
        string str{ "Error subscribe channel - " };
        str += c_channel_s;
        throw system_error(error_code(r, system_category()), str);
    }
    m_list_s.push_back(string{ msg });
}

void subscribe::connection_lost(void* context, char* cause)
{
}

int subscribe::message_arrived(void* context, char* topic_name, int topic_len, MQTTClient_message* message)
{
	return 0;
}

void subscribe::delivery_complete(void* context, MQTTClient_deliveryToken dt)
{
}

} // namespace mqtt::subscription
