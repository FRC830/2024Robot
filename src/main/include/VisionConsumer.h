#pragma once

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include <cmath>
#include <vector>
#include <map>


struct PolarCoords {

    double r;
    double theta;

};

struct CartCoords {

    double x;
    double y;

};

class VisionConsumer {

    public:
        VisionConsumer() = default;
        ~VisionConsumer() = default;

        struct PolarCoords GetPolarCoordForTagX(int tagId);
        struct PolarCoords toPolar(double x, double y);
        struct PolarCoords GetRobotToSpeaker(double rot);
        bool getVisible(int id);
        

        
    
    private:            



};