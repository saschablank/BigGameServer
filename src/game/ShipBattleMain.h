#pragma once
#include "../utils/IMain.h"
#include "AuthRestEndpoint.h"
#include "AvailabilityEndpoint.h"
#include "GetKeyEndpoint.h"
#include "../utils/MariaDbSqlQueryExecutor.h"


class ShipBattleMain : public IMain {
public:
    ShipBattleMain() = default;
    virtual ~ShipBattleMain() = default;

    void process_cmd_args(std::map<std::string, std::string>& cmd_args) override {
        _cmd_args = cmd_args;
    }
    void registerEndpoints(RestEndpointController& endpoint_controller) override {
        AuthRestEndpoint* auth_endpoint = new AuthRestEndpoint();
        endpoint_controller.register_endpoint(auth_endpoint);
        
        AvailabilityEndpoint* availability_endpoint = new AvailabilityEndpoint();
        endpoint_controller.register_endpoint(availability_endpoint);
        
        GetKeyEndpoint* get_key_endpoint = new GetKeyEndpoint();
        endpoint_controller.register_endpoint(get_key_endpoint);
    
    }
    void printHelp() {
        std::cout << "Usage: BigGameServer [options]\n"
                  << "This is a multi-purpose game server application which acts as framework for different game servers.\n"
                  << "For "
                  << "Options:\n"
                  << "  --type=<type>       Specify the type of server\n"
                  << "Options for --type:  controller, game, web\n"
                  << "  --web-port=<port>  Specify the port for the web server if type is controller or web\n"
                  << "  --game-port=<port> Specify the port for the game server if type is controller game\n"
                  << "  --help              Show this help message\n";
    }

    int run() override {
        if(_cmd_args.find("help") != _cmd_args.end()) {
            printHelp();
            return 0;
        }
        if (_cmd_args.find("type") == _cmd_args.end()) {
            std::cerr << "Error: --type argument is required." << std::endl;
            printHelp();
            return 1;
        }
        if( _cmd_args["type"] == "controller" || _cmd_args["type"] == "web") {
            if (_cmd_args.find("web-port") == _cmd_args.end()) {
                std::cerr << "Error: --web-port argument is required for controller or web type." << std::endl;
                printHelp();
                return 1;
            }
        } else if (_cmd_args["type"] == "controller"  || _cmd_args["type"] == "game") {
            if (_cmd_args.find("game-port") == _cmd_args.end()) {
                std::cerr << "Error: --game-port argument is required for game type." << std::endl;
                printHelp();
                return 1;
            }
        } else {
            std::cerr << "Error: Invalid type specified. Use 'controller', 'game', or 'web'." << std::endl;
            printHelp();
            return 1;
        }
        _app_type = _cmd_args["type"];
        if( _app_type == "controller" || this->_app_type == "web") {
            if (_cmd_args.find("web-port") != _cmd_args.end()) {
                this->_web_port = std::stoi(_cmd_args["web-port"]);
                startWebserver(this->_web_port);
                MariaDbSqlQueryExecutor::set_connection_details("172.18.02.2", 3306, "shipbattle","fu0zi2ooT6ahshei9LeoDi7puiL2ieX4", "shipbattle" );
                
            }
        }
        if (_app_type == "controller" || _app_type == "game") {
            if (_cmd_args.find("game-port") != _cmd_args.end()) {
                this->_game_port = std::stoi(_cmd_args["game-port"]);
                startGameserver(this->_game_port);
            }
        }
        return 0;
    }

private:
    std::map<std::string, std::string> _cmd_args{};
    std::string _app_type = "controller";
    int _web_port = 443;
    int _game_port = 7000;

};