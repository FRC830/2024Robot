#include "VisionConsumer.h"

VisionConsumer::VisionConsumer() {
    auto inst = nt::NetworkTableInstance::GetDefault();
    table = inst.GetTable("SmartDashboard")->GetSubTable("vision");
    aprilTagCoords = table->GetDoubleTopic("vision");
    aprilTagVisible = table->GetBooleanTopic("vision");  
}

void VisionConsumer::Periodic() {

    Apriltag3X.Get(-1.0);    
    Apriltag3Y.Get(-1.0);
    Apriltag3Z.Get(-1.0);    

    Apriltag5X.Get(-1.0);
    Apriltag5Y.Get(-1.0);
    Apriltag5Z.Get(-1.0);

    Apriltag6X.Get(-1.0);
    Apriltag6Y.Get(-1.0);
    Apriltag6Z.Get(-1.0);

    Apriltag7X.Get(-1.0);
    Apriltag7Y.Get(-1.0);
    Apriltag7Z.Get(-1.0);

    Apriltag3.Get();
    Apriltag5.Get();
    Apriltag6.Get();
    Apriltag7.Get();

    ApriltagCorrected3X.Get(-1.0);
    ApriltagCorrected3Y.Get(-1.0);
    ApriltagCorrected3Z.Get(-1.0);

    ApriltagCorrected5X.Get(-1.0);
    ApriltagCorrected5Y.Get(-1.0);
    ApriltagCorrected5Z.Get(-1.0);

    ApriltagCorrected6X.Get(-1.0);
    ApriltagCorrected6Y.Get(-1.0);
    ApriltagCorrected6Z.Get(-1.0);

    ApriltagCorrected7X.Get(-1.0);
    ApriltagCorrected7Y.Get(-1.0);
    ApriltagCorrected7Z.Get(-1.0);

    FPS.Get(-1.0);
}

void VisionConsumer::Subscribe() {

    AprilTagSubscribers[3].Subscribe(table, 3);
    AprilTagSubscribers[5].Subscribe(table, 5);
    AprilTagSubscribers[6].Subscribe(table, 6);
    AprilTagSubscribers[7].Subscribe(table, 7);


    FPS = aprilTagCoords.Subscribe(0.0);
}

struct PolarCoords toPolar(double x, double y) {
    double r = sqrt(pow(x, 2) + pow(y, 2));
    double theta = atan2(y, x);

    struct PolarCoords currentCoords;
    currentCoords.r = r;
    currentCoords.theta = theta;
    return currentCoords; 
}
