#include <asio.hpp>
#include <iostream>
#include <memory>
#include <set>
#include "Session.h"

using asio::ip::tcp;


class GameServer {
    public:
    GameServer(asio::io_context& io_context, short port)
            : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
            do_accept();
        }
    
    private:
        tcp::acceptor acceptor_;
    
        void do_accept() {
            acceptor_.async_accept(
                [this](std::error_code ec, tcp::socket socket) {
                    if (!ec) {
                        std::make_shared<Session>(std::move(socket))->start();
                    }
                    do_accept();  // accept next connection
                });
        }
 };
