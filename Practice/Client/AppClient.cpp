#define _CRT_SECURE_NO_WARNINGS
#include "AppClient.h"
#include "helpers/SocketClient.h"
#include "helpers/UtilString.h"
#include "helpers/UtilFile.h"
#include <map>
#include <chrono>
#include <thread>

bool Client::send(const std::string& url, const std::string& msg)
{
    SocketClient s;
    bool connected = false;

    while (!connected) {
       // printf("Attempting to connect to the server...\n");

        if (s.init() && s.connect(url)) {
            printf("Connected to the server\n");
            connected = true;
        }
        else {
            printf("Failed to connect to the server. Retrying in 3 seconds...\n");
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }

    printf("sending text message \"%s\"\n", msg.c_str());
    int len = s.sendStr(msg);

    printf("sent %d bytes\n", len);
    return len > 0;
}