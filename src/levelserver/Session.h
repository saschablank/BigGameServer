#include <asio.hpp>
#include <iostream>
#include <memory>
#include <set>

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket) : socket_(std::move(socket)) {}
   
    void start() {
        do_read();
    }
   
private:
    tcp::socket socket_;
    char data_[1024];
   
    void do_read() {
        auto self = shared_from_this();
        socket_.async_read_some(asio::buffer(data_, 1024),
            [this, self](std::error_code ec, std::size_t length) {
                if (!ec) {
                    do_write(length);
                }
            });
    }
   
    void do_write(std::size_t length) {
        auto self = shared_from_this();
        asio::async_write(socket_, asio::buffer(data_, length),
            [this, self](std::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    do_read();
                }
            });
    }
};