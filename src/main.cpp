#include <iostream>
#include <asio.hpp>
#include <memory>
#include "game/ShipBattleMain.h"
#include "utils/Helper.h"


int main(int argc, char* argv[]) {
    // CHANGE THIS TO YOUR OWN IMPLEMENTATION
    std::unique_ptr<IMain> main_app = std::make_unique<ShipBattleMain>();
    //////////// /\ UP /\ ///////////////////

    auto args = Helper::parseCommandLineArgs(argc, argv);
    main_app->process_cmd_args(args);
    int rc = main_app->run();
    return rc;
}
