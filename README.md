# BigGameServer
BigGameServer is an application designed to serve as a modular server framework for multiplayer games.
The server currently supports TCP only, with a UDP implementation planned for future releases.

BigGameServer consists of three main components:

##  Web Server with REST Endpoints
A built-in web server can be accessed via REST endpoints.

For database access, an MariaDB implementation is available using the official C++ connector:
MariaDB C++ Connector Documentation

REST endpoints can be implemented as C++ classes, allowing clear and structured API development.

## TCP Game Server
Provides boilerplate code for building a TCP-based game server, including:
* Session and match management
* Abstractions for integrating game-specific logic
* this allows developers to focus on gameplay implementation without dealing with low-level network handling.

## Lightweight Container Orchestration (Controller)
A built-in controller is capable of starting additional TCP game server instances in Docker containers
once a defined number of matches has been reached.
The responsibility for connecting to new instances is delegated to the client.

## Dependencies
* httplib -> https://github.com/yhirose/cpp-httplib
* asio -> https://think-async.com/Asio/
* mariadb connector -> https://mariadb.com/docs/connectors/mariadb-connector-cpp/install-mariadb-connector-cpp

## 🔧 Integration Guide

- **Implement the interface defined in `/utils/IMain.h`.**  
  A default implementation is provided for the `startWebserver` and `startGameServer` functions, which can be extended or overridden as needed.

- **To add a new REST endpoint:**  
  - Create a class that inherits from `webserver/RestEndpoint.h`.
  - Define the `endpoint_path` using a regular expression, e.g. `R"(/login)"`.  
    This allows for flexible and precise route matching.

- **Register your endpoints:**  
  - Within the `registerEndpoints` function (which should be invoked inside your `startWebserver` method), instantiate your endpoint classes.
  - Use the `RestEndpointController` to register these instances for handling incoming requests.
