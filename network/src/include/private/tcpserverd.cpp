#include "tcpserverd.h"
#include "../tcpserver_api.h"
using namespace boost::asio::ip;
namespace network
{
class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket, const TCPServerParam& tcp_server_param) 
        : socket_(std::move(socket)) 
        {
            tcp_server_param_ = tcp_server_param;
            tcp_server_param_.tcp_server_callback(1, "12", 12, std::string(), tcp_server_param_.ptr_userdata);
        }

        void start() {
            do_read();
        }
    
    private:
        void do_read() {
            auto self(shared_from_this());
            socket_.async_read_some(boost::asio::buffer(data_),
                [this, self](boost::system::error_code ec, std::size_t length) {
                    if (!ec) {
                        std::string str_receive;
                        str_receive.assign(data_, length);
                        std::string reply = tcp_server_param_.tcp_server_callback(0, "12", 12, 
                            str_receive, 
                            tcp_server_param_.ptr_userdata);
                        do_write(reply);
                        do_read();
                    }
                    else{
                        tcp_server_param_.tcp_server_callback(2, 
                            "12", 
                            12, std::string(), 
                        tcp_server_param_.ptr_userdata);
                    }
                });
        }
    
        void do_write(const std::string& write_data) {
            if (write_data.empty())
            {
                return;
            }
            
            auto self(shared_from_this());
            boost::asio::async_write(socket_, boost::asio::buffer(write_data.c_str(), write_data.length()),
                [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                    if (!ec) {
                    }
                });
        }
    
        tcp::socket socket_;
        enum { max_length = 1024 };
        char data_[max_length];
        TCPServerParam tcp_server_param_;
    };

    CTCPServerd::CTCPServerd()
    {
        
    }
    CTCPServerd::~CTCPServerd()
    {

    }
    bool CTCPServerd::StartServer(const TCPServerParam& tcp_server_param)
    {
        tcp_server_param_ = tcp_server_param;
        if (ptr_io_context_ == nullptr)
        {
            ptr_io_context_ = new boost::asio::io_context();

            ptr_acceptor_ = new boost::asio::ip::tcp::acceptor(*ptr_io_context_,  
                tcp::endpoint(tcp::v4(), tcp_server_param.listen_port_));

            do_accept();

            t1_ = std::thread([&]{
                ptr_io_context_->run();
            });
        }
        
        return true;
    }
    bool CTCPServerd::StopServer()
    {
        if (ptr_io_context_)
        {
            ptr_io_context_->stop();
            delete ptr_io_context_;
            ptr_io_context_ = nullptr;

            delete ptr_acceptor_;
            ptr_acceptor_ = nullptr;
            /* code */
        }
        return true;
    }

    void CTCPServerd::do_accept() {
        ptr_acceptor_->async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<Session>(std::move(socket), tcp_server_param_)->start();
                }
                do_accept();
            });
    }

    CTCPServerd* ptr_global = nullptr;
    int StartTCPServer(const network::TCPServerParam& tcp_server_param)
    {
        if (ptr_global)
        {
            ptr_global->StopServer();
            delete ptr_global;
            ptr_global = nullptr;
        }
        ptr_global = new CTCPServerd();
        ptr_global->StartServer(tcp_server_param);
        return 0;
    }

    void StopTcpServer(int handle)
    {
        if (ptr_global)
        {
            ptr_global->StopServer();
            delete ptr_global;
            ptr_global = nullptr;
        }
    }
}

