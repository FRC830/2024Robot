#pragma once

#include <iostream>

#define START_RETRYING(config_name) \
{\
    bool successful = false;\
    int retries = 0;\
    rev::REVLibError error;\
    while(retries <=10 && !successful)\
    {\
        std::cout << "Trying to set: " << #config_name << std::endl;\
        retries++;\
        error = 

#define END_RETRYING \
        successful = error == rev::REVLibError::kOk;\
    }\
    if (error != rev::REVLibError::kOk)\
    {\
        std::cout << "Unable to set config item" << std::endl;\
    }\
    else\
    {\
        std::cout << "Set config item in " << retries << "retries" << std::endl;\
    }\
}
