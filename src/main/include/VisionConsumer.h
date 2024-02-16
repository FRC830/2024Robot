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
        VisionConsumer();
        void Periodic();

        PolarCoords GetPolarCoordForTagX(int tagId);
        PolarCoords toPolar(double x, double y);
        PolarCoords GetRobotToSpeaker(PolarCoords a, PolarCoords b, double rot);
        
    
    private:            

        std::vector<double> x; 
        std::vector<double> y; 
        std::vector<double> z; 
        std::vector<bool> v;
        double fps;
        double dist = 0.43; 

};