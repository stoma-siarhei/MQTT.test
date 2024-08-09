#ifndef _CLIENT_H_
#define _CLIENT_H_


#include "pch.h"

#include "mqtt_impl.h"


namespace mqtt::publication
{

class publisher : public mqtt_impl
{
public:
	explicit publisher();

	explicit publisher(const char* addr);

	explicit publisher(const string_view addr);

	explicit publisher(const char* addr, const char* id);

	explicit publisher(const string_view addr, const string_view id);

	~publisher() noexcept;

	void operator()(const string_view msg) const;
protected:
	// void MQTTClient_connectionLost(void* context, char* cause);
	static void connection_lost(void* context, char* cause);

	// int MQTTClient_messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message);
	static int message_arrived(void* context, char* topic_name, int topic_len, MQTTClient_message* message);

	// void MQTTClient_deliveryComplete(void* context, MQTTClient_deliveryToken dt);
	static void delivery_complete(void* context, MQTTClient_deliveryToken dt);

private:
	bool m_connected{ false };
}; // class publisher

} // namespace mqtt::publication


#endif // _CLIENT_H_
