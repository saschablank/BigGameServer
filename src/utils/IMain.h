#include <string>
#include <map>
#include <asio.hpp>
#include "../webserver/Webserver.h"
#include "../webserver/RestEndpointController.h"
#include "../levelserver/GameServer.h"

class IMain {
public:
    virtual ~IMain() = default;
    virtual void printHelp() = 0;
    virtual void process_cmd_args(std::map<std::string, std::string >& cmd_args) = 0;
    virtual void registerEndpoints(RestEndpointController& endpoint_controller) = 0;


    virtual int run() = 0;
protected:
    virtual void startWebserver(int webserver_port=443) {

        _webserver = std::make_unique<Webserver>();
        registerEndpoints(rest_endpoint_controller);
        _webserver->start(webserver_port, rest_endpoint_controller);
    };
    virtual void startGameserver(int gameserver_port=7000){
        
        _gameserver = std::make_unique<GameServer>(io_context, gameserver_port);
        io_context.run();
    };
    RestEndpointController rest_endpoint_controller;
    std::unique_ptr<Webserver> _webserver;
    std::unique_ptr<GameServer>_gameserver;
    asio::io_context io_context;
};