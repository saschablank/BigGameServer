#include "WebSession.h"

std::shared_ptr<UserDataBase> WebSession::getUserData()
{
    if (!user_data) {
        user_data = std::make_shared<UserDataBase>();
    }
    return user_data;
}