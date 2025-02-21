#pragma once
#include <string>
namespace network
{
    // type[0-data,1-connect,2-disconnect]
    typedef std::string TCPServerCallbackFun(int tpye, 
        std::string client_ip, 
        int cilent_port, 
        std::string tcp_data, 
        void* ptr_userdata);

    struct TCPServerParam
    {
        int listen_port_ = 0;
        TCPServerCallbackFun* tcp_server_callback;
        void* ptr_userdata = nullptr;
    };

    struct TCPClientParam
    {

    };
}
