#ifndef _SERVER_H_
#define _SERVER_H_


#include "pch.h"

#include "mqtt_impl.h"


using namespace std;

namespace mqtt::subscription
{

class subscribe : public mqtt_impl
{
public:
	using subscribe_list_t = list<string>;
public:
	explicit subscribe();

	explicit subscribe(const char* addr);

	explicit subscribe(const string_view addr);

	explicit subscribe(const char* addr, const char* id);

	explicit subscribe(const string_view addr, const string_view id);

	~subscribe() noexcept;

	void operator()();

	void operator()(const string_view msg);
protected:
	// void MQTTClient_connectionLost(void* context, char* cause);
	static void connection_lost(void* context, char* cause);

	// int MQTTClient_messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message);
	static int message_arrived(void* context, char* topic_name, int topic_len, MQTTClient_message* message);

	// void MQTTClient_deliveryComplete(void* context, MQTTClient_deliveryToken dt);
	static void delivery_complete(void* context, MQTTClient_deliveryToken dt);

private:
	bool m_connected{ false };
	subscribe_list_t m_list_s;
}; // class class subscribe


} // namespace mqtt::subscription


#endif // _SERVER_H_
