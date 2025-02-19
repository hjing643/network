#pragma once
#include "../includeall.h"
#include "../networkcom.h"
namespace network
{
    class CTCPServerd
    {
    public:
        CTCPServerd();
        ~CTCPServerd();
        bool StartServer(const network::TCPServerParam& tcp_server_param);
        bool StopServer();
    private:
        void do_accept();
    private:
        network::TCPServerParam tcp_server_param_;
        boost::asio::io_context* ptr_io_context_ = nullptr;
        boost::asio::ip::tcp::acceptor* ptr_acceptor_;
        std::thread t1_;
    };
}
