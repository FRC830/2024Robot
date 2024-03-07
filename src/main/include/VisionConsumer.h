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
        bool getVisible(PolarCoords aOrB, bool isA);
        

        
    
    private:            
        struct PolarCoords lastA; 
        struct PolarCoords lastB;

        int m_a_count;
        int m_b_count;



};