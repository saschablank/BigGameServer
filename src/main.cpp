#include <iostream>
#include <asio.hpp>
#include "HttpClient.h"
#include "levelserver/GameServer.h"
#include "webserver/RestEndpointController.h"
#include "webserver/Webserver.h"
#include "utils/SqlQueryExecutor.h"
#include "game/AuthRestEndpoint.h"
#include "game/AvailabilityEndpoint.h"
#include "game/GetKeyEndpoint.h"


using asio::ip::tcp;
using asio::io_context;
static asio::io_context io_context;

std::map<std::string, std::string> parseCommandLineArgs(int argc, char* argv[]) {
    std::map<std::string, std::string> args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("--") == 0) {
            size_t pos = arg.find('=');
            if (pos != std::string::npos) {
                std::string key = arg.substr(2, pos - 2);
                std::string value = arg.substr(pos + 1);
                args[key] = value;
            } else {
                args[arg.substr(2)] = ""; // No value provided
            }
        }
    }
    return args;
}

std::map<std::string, std::string> get_env_variables() {
    std::map<std::string, std::string> env_vars;
    return env_vars;
}


void printHelp() {
    std::cout << "Usage: BigGameServer [options]\n"
              << "This is a multi-purpose game server application which acts as framework for different game servers.\n"
              << "For "
              << "Options:\n"
              << "  --type=<type>       Specify the type of server\n"
              << "Options for --type:  controller, game, webserver\n"
              << "  --help              Show this help message\n";
}

int main(int argc, char* argv[]) {
    std::map<std::string, std::string> cmd_args = parseCommandLineArgs(argc, argv);
    if (cmd_args.find("help") != cmd_args.end()) {
        printHelp();
        return 0;
    }
    if(cmd_args.find("type") == cmd_args.end()){
        std::cerr << "Error: --type argument is required." << std::endl;
        printHelp();
        return 1;
    }
    
    std::cout << "Starting ShipBattleServer..." << std::endl;
   
    RestEndpointController rest_endpoint_controller;

    
    AuthRestEndpoint auth_endpoint;
    rest_endpoint_controller.register_endpoint(&auth_endpoint);
    
    AvailabilityEndpoint availability_endpoint;
    rest_endpoint_controller.register_endpoint(&availability_endpoint);
    
    GetKeyEndpoint get_key_endpoint;
    rest_endpoint_controller.register_endpoint(&get_key_endpoint);


    asio::io_context io_context;
    GameServer server(io_context, 12345);
    io_context.run();

    //HttpClient client = HttpClient();
    //if(client.sendRegisterRequest("aeDaiziesohooch2CahTh1eed5Oof6bi") == true) {
    //    std::cout << "Registration successful." << std::endl;
    //    if(client.sendGetLevelsRequest("aeDaiziesohooch2CahTh1eed5Oof6bi") == true){
    //        std::cout << "Get levels request successful." << std::endl;
    //        short port = 7000;
    //        GameServer gameserver = GameServer(io_context, port);
    //        
    //        std::cout << "Server started on port 7000\n";
    //        io_context.run();
    //    } else {
    //        std::cerr << "Failed to get levels." << std::endl;
    //    }
    //} else {
    //    std::cerr << "Registration failed." << std::endl;
    //}

    
    return 0;
}
