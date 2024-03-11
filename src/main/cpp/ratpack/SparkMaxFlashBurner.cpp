#include "include/ratpack/SparkMaxFlashBurner.h"

#include <iostream>

SparkMaxFlashBurner& SparkMaxFlashBurner::GetInstance()
{
    static SparkMaxFlashBurner FLASH_BURNER;
    return FLASH_BURNER;
}

void SparkMaxFlashBurner::AddToRetryList(rev::CANSparkMax* spark_max)
{
    _retry_list.emplace_back(RetryEntry{false, spark_max});

    std::cout << "Spark Max #" << spark_max->GetDeviceId() << " added to retry list" << std::endl;
}

void SparkMaxFlashBurner::RetryBurnFlash()
{
    int num_unsucessfully_flashed = _retry_list.size();

    for (int i = 0; i < _retry_list.size(); ++i)
    {
        if (!_retry_list[i].burned_flashed_succesfully)
        {
            rev::REVLibError error = _retry_list[i].spark_max->BurnFlash();
            _retry_list[i].burned_flashed_succesfully = error == rev::REVLibError::kOk;
        
            if (_retry_list[i].burned_flashed_succesfully)
            {
                std::cout << "Successfully burned flash for Spark Max #" << _retry_list[i].spark_max->GetDeviceId() << std::endl;
                --num_unsucessfully_flashed;
            }
        }
        else
        {
            --num_unsucessfully_flashed;
        }
    }

    // TODO: print out number to still flash to dashboard + a boolean type
}