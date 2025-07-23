#include "UserController.h"

UserController::UserController()
{
    _query.readTableColumns(_table);
}

const int UserController::createNewUser(const std::string &player_name)
{
    return 0;
}

bool UserController::deleteUser(const int id)
{
    return false;
}

bool UserController::updateUserData(std::shared_ptr<UserDataBase> user_data)
{
    return false;
}
