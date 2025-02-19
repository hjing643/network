#include <stdio.h>
#include "include/includeall.h"
#include "include/tcpserver_api.h"
#include "include/networkcom.h"

std::string TCPServerCallback(int type, 
    std::string client_ip, 
    int client_port, 
    std::string tcp_data, 
    void* ptr_userdata)
    {
        std::string str_ret;
        if (type == 1)
        {
            std::cout<< "receive connect:" << client_ip << ":"<<client_port << std::endl;
            /* code */
        }
        else if (type == 1)
        {
            std::cout<< "receive disconnect:" << client_ip << ":"<<client_port << std::endl;
            /* code */
        }
        else if (type == 0)
        {
            /* code */
            std::cout<< "receive data:" << tcp_data << std::endl;
            str_ret = "I am server ack";
        }
        return str_ret;
        
    }
int main() {
    try {
		int tcp_port = 8888;
		std::cout << "my first linux network demo from vscode ssh. port: " << tcp_port << std::endl;

        network::TCPServerParam tcp_server_param;
        tcp_server_param.listen_port_ = tcp_port;
        tcp_server_param.tcp_server_callback = TCPServerCallback;
        network::StartTCPServer(tcp_server_param);

        //network::CTCPServerd* ptr_global = new network::CTCPServerd();
        //ptr_global->StartServer(tcp_server_param);

        getchar();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}