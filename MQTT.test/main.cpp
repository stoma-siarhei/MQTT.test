#include "pch.h"

#include "MQTTClient.h"


#define ADDRESS "tcp://213.33.180.130:1885"
#define CLIENTID "ExampleClientPub"
#define TOPIC "MQTT Examples"
#define PAYLOAD "Hello World!"
#define QOS 1
#define TIMEOUT 10000L


using namespace std;

int main(int argc, char** argv)
{
	cout << "Program test MQTT protocol" << endl;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to create client, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    //setup variables 
    char* topicName = NULL;
    int topicLen;
    MQTTClient_message* m = NULL;
    //start infinite loop
    while (1)
    {
        //2 is the timeout which is 2 milliseconds
        MQTTClient_receive(client, &topicName, &topicLen, &m, 2);
        if (topicName)
        {
            printf("Message received on topic %s is %.*s.\n", topicName, m->payloadlen, (char*)(m->payload));
            MQTTClient_free(topicName);
            MQTTClient_freeMessage(&m);
        }
    }
    //pubmsg.payload = (void*)PAYLOAD;
    //pubmsg.payloadlen = (int)strlen(PAYLOAD);
    //pubmsg.qos = QOS;
    //pubmsg.retained = 0;
    //if ((rc = MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
    //{
    //    printf("Failed to publish message, return code %d\n", rc);
    //    exit(EXIT_FAILURE);
    //}

    //printf("Waiting for up to %d seconds for publication of %s\n"
    //    "on topic %s for client with ClientID: %s\n",
    //    (int)(TIMEOUT / 1000), PAYLOAD, TOPIC, CLIENTID);
    //rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    //printf("Message with delivery token %d delivered\n", token);

    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
        printf("Failed to disconnect, return code %d\n", rc);
    MQTTClient_destroy(&client);
    return rc;
}
