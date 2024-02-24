#include "VisionConsumer.h"
#include <iostream>

VisionConsumer::VisionConsumer() {

    for (int i = 0; i < 16; i++){

        x.emplace_back(frc::SmartDashboard::GetNumber("vision/Apriltag " + std::to_string(i + 1) + " X: ", 0.0));
        y.emplace_back(frc::SmartDashboard::GetNumber("vision/Apriltag " + std::to_string(i + 1) + " Y: ", 0.0));
        z.emplace_back(frc::SmartDashboard::GetNumber("vision/Apriltag " + std::to_string(i + 1) + " Z: ", 0.0));
        v.emplace_back(frc::SmartDashboard::GetBoolean("vision/Apriltag " + std::to_string(i + 1) + "Detected", false));

    }

    fps = frc::SmartDashboard::GetNumber("vision/FPS", 0.0);

}

void VisionConsumer::Periodic() {

    for (int i = 0; i<16; i++){

        x.at(i) = frc::SmartDashboard::GetNumber("vision/Apriltag " + std::to_string(i + 1) + " X: ", 0.0);
        x.at(i) = frc::SmartDashboard::GetNumber("vision/Apriltag " + std::to_string(i + 1) + " Y: ", 0.0);
        x.at(i) = frc::SmartDashboard::GetNumber("vision/Apriltag " + std::to_string(i + 1) + " Z: ", 0.0);
        x.at(i) = frc::SmartDashboard::GetBoolean("vision/Apriltag " + std::to_string(i + 1) + "Detected", false);

    }

    fps = frc::SmartDashboard::GetNumber("FPS", 0.0);

}

PolarCoords VisionConsumer::toPolar(double x, double y) {

    double r = sqrt(pow(x, 2) + pow(y, 2));
    double theta = atan2(y, x);
    struct PolarCoords currentCoords = {r, theta};
    return currentCoords;

}

PolarCoords VisionConsumer::GetPolarCoordForTagX(int id) {

    return toPolar(x.at(id), y.at(id));

}

PolarCoords VisionConsumer::GetRobotToSpeaker(PolarCoords a, PolarCoords b, double rot) {

    // double dist = frc::DriverStation::GetAlliance().value() == frc::DriverStation::Alliance::kRed ? 22.25 : -22.25;

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
    frc::SmartDashboard::PutString("error", std::to_string(error.x) + "," + std::to_string(error.y));
    struct CartCoords correction = {error.x / 2, error.y / 2};

    struct PolarCoords ret = toPolar(Ax + correction.x, Ay + correction.y);
    ret.theta += rot;
    ret.theta *= (180.0 / 3.14159265358979323846);

    return ret;
}
