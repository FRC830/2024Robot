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

PolarCoords VisionConsumer::toPolar(double x, double y) {
    double r = sqrt(pow(x, 2) + pow(y, 2));
    double theta = atan2(y, x);

    struct PolarCoords currentCoords;
    currentCoords.r = r;
    currentCoords.theta = theta;
    return currentCoords; 
}

PolarCoords VisionConsumer::GetPolarCoordForTagX(int id) {

    return toPolar(x.at(id), y.at(id));

}

PolarCoords VisionConsumer::GetRobotToSpeaker(PolarCoords a, PolarCoords b, double rot) {

    // measured in inches
    double dist = 22.25;

    rot = rot * ( 3.14159265358979323846 / 180.0);

    struct PolarCoords A = {a.r, a.theta - rot};
    struct PolarCoords B = {b.r, b.theta - rot};

    double Ax = A.r * cos(A.theta);
    double Ay = A.r * sin(A.theta);
    double Bx = B.r * cos(B.theta);
    double By = B.r * sin(B.theta);

    double Bxa = Ax;
    double Bya = Ay - dist; 

    struct CartCoords error = {Bxa - Bx, Bya - By};
    struct CartCoords correction = {error.x / 2, error.y / 2};

    struct PolarCoords ret = toPolar(Ax + correction.x, Ay + correction.y);
    ret.theta += rot;
    ret.theta *= (180.0 / 3.14159265358979323846);
    
    return ret;
}
