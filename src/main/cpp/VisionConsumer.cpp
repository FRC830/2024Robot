#include "VisionConsumer.h"
#include <iostream>


struct PolarCoords VisionConsumer::toPolar(double x, double y) {

    double r = sqrt(pow(x, 2) + pow(y, 2));
    double theta = atan2(y, x);
    struct PolarCoords currentCoords = {r, theta};
    return currentCoords;

}

struct PolarCoords VisionConsumer::GetPolarCoordForTagX(int id) {

    double x = frc::SmartDashboard::GetNumber("Apriltag " + std::to_string(id) + " X: ", 0.0);
    double y = frc::SmartDashboard::GetNumber("Apriltag " + std::to_string(id) + " Y: ", 0.0);


    return toPolar(x, y);

}

bool VisionConsumer::getVisible(PolarCoords cur, bool isA) {
    
    if (isA) {

        if (lastA.r == 0.0) {

            return false;

        } else if (cur.r - lastA.r <= 0.00001){

            return false;

        } else {return true;}

    } else {

        if (lastB.r == 0.0) {

            return false;

        } else if (cur.r - lastB.r <= 0.00001){

            return false;

        } else {return true;}

    }

}

PolarCoords VisionConsumer::GetRobotToSpeaker(double rot) {

    struct PolarCoords a; 
    struct PolarCoords b; 
    double dist;
    bool AisVisible; 
    bool BisVisible;

    // get A, B

    if (frc::DriverStation::GetAlliance().value() == frc::DriverStation::Alliance::kRed) {

        dist = -22.25;

        a = GetPolarCoordForTagX(4);
        b = GetPolarCoordForTagX(3);
        
        AisVisible = getVisible(a, true);
        BisVisible = getVisible(b, false);
        

    } else {

        dist = 22.25;
        
        a = GetPolarCoordForTagX(7);
        b = GetPolarCoordForTagX(8);

        AisVisible = getVisible(a, true);
        BisVisible = getVisible(b, false);
    }

    

    rot = (rot > 180) ? rot - 360 : rot;

    rot = rot * ( 3.14159265358979323846 / 180.0);

    lastA = a;
    lastB = b;

    if (AisVisible && BisVisible) {

        struct PolarCoords A = {a.r, a.theta - rot};
        struct PolarCoords B = {b.r, b.theta - rot};

        double Ax = A.r * cos(A.theta);
        double Ay = A.r * sin(A.theta);
        double Bx = B.r * cos(B.theta);
        double By = B.r * sin(B.theta);

        double Bxa = Ax;
        double Bya = Ay - dist;

        struct CartCoords error = {Bxa - Bx, Bya - By};
        frc::SmartDashboard::PutString("error", std::to_string(error.x) + "," + std::to_string(error.y));
        struct CartCoords correction = {error.x / 2, error.y / 2};

        struct PolarCoords ret = toPolar(Ax + correction.x, Ay + correction.y);
        ret.theta += rot;
        ret.theta *= (180.0 / 3.14159265358979323846);

        return ret;

    } else if(AisVisible && !BisVisible) {

        a.theta *= (180.0 / 3.14159265358979323846);
        return a;

    } else if (!AisVisible && BisVisible) {

        struct PolarCoords B = {b.r, b.theta - rot};
        double Bx = B.r * cos(B.theta);
        double By = B.r * sin(B.theta);   
        struct PolarCoords A = toPolar(Bx, By + dist);
        a.theta += rot;
        a.theta *= (180.0 / 3.14159265358979323846);

        return a; 


    } else {

        return PolarCoords{0.0, 0.0};

    }
}
