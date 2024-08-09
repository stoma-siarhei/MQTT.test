#include "pch.h"

#include "client.h"
#include "server.h"


using namespace std;

int main(int argc, char** argv)
{
	cout << "Program test MQTT protocol" << endl;
	try
	{
		mqtt::publication::publisher pub;
		pub("Hello");
	}
	catch (system_error& e)
	{
		cout << "Error - " << e.what() << ": code - " << e.code() << endl;
	}
    return 0;
}
