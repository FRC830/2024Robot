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

struct XYZCoords {
    double x;
    double y;
    double z;
    double xCorrected;
    double yCorrected;
    double zCorrected;
    double id;
    std::vector<nt::DoubleSubscriber> GetXYZCoords;

    XYZCoords GetXYZ(int id) {
        
      
    }

};

class VisionConsumer {

    public:
        VisionConsumer();
        void Periodic();
        void Subscribe();
        struct PolarCoords toPolar(double x, double y);
    
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

        std::map<int, XYZCoords> GetXYZCoords;
};