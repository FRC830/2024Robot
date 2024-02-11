#include "VisionConsumer.h"

VisionConsumer::VisionConsumer() {
    auto inst = nt::NetworkTableInstance::GetDefault();
    table = inst.GetTable("SmartDashboard")->GetSubTable("vision");
    aprilTagCoords = table->GetDoubleTopic("vision");
    aprilTagVisible = table->GetBooleanTopic("vision");  
    nt::DoubleSubscriber X;
    nt::DoubleSubscriber Y;
    nt::DoubleSubscriber Z;
    nt::BooleanSubscriber visible;


    for (int i = 0; i < 16; i++){

        xSub.push_back(table->GetDoubleTopic("Apriltag " + std::to_string(i+1) + " X").Subscribe(0.0));
        ySub.push_back(table->GetDoubleTopic("Apriltag " + std::to_string(i+1) + " y").Subscribe(0.0));
        zSub.push_back(table->GetDoubleTopic("Apriltag " + std::to_string(i+1) + " z").Subscribe(0.0));        
        vSub.push_back(table->GetBooleanTopic("Apriltag " + std::to_string(i+1) + "Detected").Subscribe(false));
    
    }
    
    FPS = table->GetDoubleTopic("FPS").Subscribe(0.0);
}       

void VisionConsumer::Periodic() {
    
    for (int i = 0; i<16; i++){
        
        x.push_back(xSub.at(i).Get());
        y.push_back(ySub.at(i).Get());
        z.push_back(zSub.at(i).Get());
        v.push_back(vSub.at(i).Get());
    }

    fps = FPS.Get();

}

struct PolarCoords toPolar(double x, double y) {
    double r = sqrt(pow(x, 2) + pow(y, 2));
    double theta = atan2(y, x);

    struct PolarCoords currentCoords;
    currentCoords.r = r;
    currentCoords.theta = theta;
    return currentCoords; 
}
