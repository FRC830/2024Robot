#pragma once
// ONLY INCLUDE THIS IN CPP FILES

#include <vector>

#include <rev/CANSparkMax.h>

#define BURN_FLASH(spark_max)\
{\
    rev::REVLibError error = spark_max->BurnFlash();\
    if (error != rev::REVLibError::kOk)\
    {\
        SparkMaxFlashBurner::GetInstance().AddToRetryList(spark_max);\
    }\
}\

class SparkMaxFlashBurner
{
public:
    static SparkMaxFlashBurner& GetInstance();

    void AddToRetryList(rev::CANSparkMax* spark_max);
    void RetryBurnFlash();

    // Ban copy and move constructor and assignment operator
    SparkMaxFlashBurner(const SparkMaxFlashBurner&) = delete;
    SparkMaxFlashBurner(SparkMaxFlashBurner&&) = delete;
    SparkMaxFlashBurner& operator=(const SparkMaxFlashBurner&) = delete;
    SparkMaxFlashBurner& operator=(SparkMaxFlashBurner&&) = delete;

private:
    SparkMaxFlashBurner() = default;
    ~SparkMaxFlashBurner() = default;

    struct RetryEntry
    {
        bool burned_flashed_succesfully;
        rev::CANSparkMax* spark_max;
    };

    std::vector<RetryEntry> _retry_list;
};