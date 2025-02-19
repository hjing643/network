#pragma once
#include "networkcom.h"
namespace network
{
    int StartTCPServer(const network::TCPServerParam& tcp_server_param);

    void StopTcpServer(int handle);

}