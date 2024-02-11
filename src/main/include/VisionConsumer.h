#pragma once

#include <networktables/NetworkTableInstance.h>
#include <networktables/DoubleTopic.h>
#include <networktables/BooleanTopic.h>
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
        void Subscribe();

        PolarCoords GetPolarCoordForTagX(int tagId);
        PolarCoords toPolar(double x, double y);
        PolarCoords GetRobotToSpeaker(PolarCoords a, PolarCoords b, double rot);
        
    
    private:            
        std::shared_ptr<nt::NetworkTable> table;
        nt::DoubleTopic aprilTagCoords = table->GetDoubleTopic("vision");
        nt::BooleanTopic aprilTagVisible = table->GetBooleanTopic("vision");

        nt::DoubleSubscriber FPS;
        std::vector<nt::DoubleSubscriber> xSub; 
        std::vector<nt::DoubleSubscriber> ySub; 
        std::vector<nt::DoubleSubscriber> zSub;
        std::vector<nt::BooleanSubscriber> vSub; 
        std::vector<double> x; 
        std::vector<double> y; 
        std::vector<double> z; 
        std::vector<bool> v;
        double fps;

};