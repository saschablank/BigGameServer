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
    virtual void startWebserver(int webserver_port=443) {

        Webserver Webserver;
        RestEndpointController rest_endpoint_controller;
        registerEndpoints(rest_endpoint_controller);
        Webserver.start(webserver_port, rest_endpoint_controller);
    };
    virtual void startGameserver(int gameserver_port=7000){
        asio::io_context io_context;
        GameServer server(io_context, gameserver_port);
        io_context.run();
    };

    virtual int run() = 0;
};