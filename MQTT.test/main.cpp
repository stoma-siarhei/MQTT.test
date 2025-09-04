#include "pch.h"

#include "client.h"
#include "server.h"


using namespace std;

int main(int argc, char** argv)
{
    if (argc == 1) return 1;

    string s_type{ argv[1] };
    if (s_type == "server")
    {
        try
        {
            mqtt::subscription::subscribe sub;
            cout << "Connect to " << c_address << endl;
            do
            {
                cout << "Enter the name of channel" << endl;
                string channel;
                cin >> channel;
                try
                {
                    sub(channel);
                }
                catch (system_error& e)
                {
                    cout << "Error - " << e.what() << ": code - " << e.code() << endl;
                }
                cout << "q - quit, any key - continue" << endl;
                string command;
                cin >> command;
                if (command == "q") break;
            } while (true);
        }
        catch (system_error& e)
        {
            cout << "Error - " << e.what() << ": code - " << e.code() << endl;
        }
    }
    else if (s_type == "client")
    {
        try
        {
            mqtt::publication::publisher pub;
            cout << "Connect to " << c_address << endl;
            do
            {
                cout << "Enter the name of channel and message" << endl;
                string channel, message;
                cin >> channel >> message;
                try
                {
                    pub(channel, message);
                }
                catch (system_error& e)
                {
                    cout << "Error - " << e.what() << ": code - " << e.code() << endl;
                }
                cout << "q - quit, any key - continue" << endl;
                string command;
                cin >> command;
                if (command == "q") break;
            } while (true);
        }
        catch (system_error& e)
        {
            cout << "Error - " << e.what() << ": code - " << e.code() << endl;
        }
    }
    else return 2;
    return 0;
}
