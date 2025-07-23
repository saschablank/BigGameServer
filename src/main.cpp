#include <iostream>
#include <asio.hpp>
#include <memory>
#include "game/ShipBattleMain.h"
#include "utils/Helper.h"
#include "tests/BGSTestExecutor.h"

int run_tests() {
    BGSTestExecutor tests;
    tests.instantiateTests();
    return tests.runTests();

}


int main(int argc, char* argv[]) {
    // CHANGE THIS TO YOUR OWN IMPLEMENTATION
    std::unique_ptr<IMain> main_app = std::make_unique<ShipBattleMain>(); // <---------- YEA THIS !!! implement your own IMain class
    //////////// /\ UP /\ ///////////////////
    int rc = 1;
    auto args = Helper::parseCommandLineArgs(argc, argv);
    if( args.find("runtests") != args.end()) { // run unit tests for BGS
           rc = run_tests();
            if( rc == 0 ){
                std::cout << "ALL TESTS PASSED CONGRATULATIONS NERD" << std::endl;
            }
    } else {
        main_app->process_cmd_args(args);
        rc = main_app->run();
    }
    return rc;
}
