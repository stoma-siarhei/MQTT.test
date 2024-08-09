#include "client.h"


namespace mqtt::publication
{

publisher::publisher()
    : publisher(c_address, c_client_id)
{
}

publisher::publisher(const char* addr) 
    : publisher(addr, c_client_id)
{
}

publisher::publisher(const string_view addr) 
    : publisher(addr.data())
{
}

publisher::publisher(const char* addr, const char* id) 
    : mqtt_impl(addr, id)
{
    if (auto r = MQTTClient_setCallbacks(get(), nullptr, publisher::connection_lost, publisher::message_arrived, publisher::delivery_complete); r != MQTTCLIENT_SUCCESS)
    {
        throw system_error(error_code(r, system_category()), "Error setup callback function");
    }
#if MQTT_VER == 5
#else
    if (auto r = MQTTClient_connect(get(), &options()); r != MQTTCLIENT_SUCCESS) 
    {
        throw system_error(error_code(r, system_category()), "Failed connect");
    }
    m_connected = true;
#endif // MQTT_VER == 5
}

publisher::publisher(const string_view addr, const string_view id) 
    : publisher(addr.data(), id.data())
{
}

publisher::~publisher() noexcept
{
    if (m_connected)
#if MQTT_VER == 5
        MQTTClient_disconnect5()
#else
        MQTTClient_disconnect(get(), c_interval);
#endif // MQTT_VER == 5
}

static MQTTClient_deliveryToken token = 0;

void publisher::operator()(const string_view msg) const
{
    MQTTClient_message _m = MQTTClient_message_initializer;
    MQTTClient_deliveryToken _t;
    _m.payload = (void*)msg.data();
    _m.payloadlen = msg.size();
    _m.qos = c_qos;
    _m.retained = 0;
    if (auto r = MQTTClient_publishMessage(get(), c_channel_p, &_m, &_t); r != MQTTCLIENT_SUCCESS)
    {
        throw system_error(error_code(r, system_category()), "Error public message");
    }
    else
    {
        while (token != _t)
        {
            Sleep(1000);
        }
    }
}

void publisher::connection_lost(void* context, char* cause)
{
}

int publisher::message_arrived(void* context, char* topic_name, int topic_len, MQTTClient_message* message)
{
    return 0;
}

void publisher::delivery_complete(void* context, MQTTClient_deliveryToken dt)
{
    token = dt;
}

} // namespace mqtt::publication
