#pragma once

#include <networktables/NetworkTableInstance.h>
#include <networktables/DoubleTopic.h>
#include <networktables/BooleanTopic.h>
#include <map>

struct PolarCoords {
    double r;
    double theta;
};

struct XYZCoords {
    double x;
    double y;
    double z;
};

struct XYZCoordsCurrent {
    double x;
    double y;
    double z;
};

struct AprilTagSubscriber {
    nt::DoubleSubscriber X;
    nt::DoubleSubscriber Y;
    nt::DoubleSubscriber Z;
    nt::BooleanSubscriber visible;
    nt::DoubleSubscriber correctedX;
    nt::DoubleSubscriber correctedY;
    nt::DoubleSubscriber correctedZ;

    void Subscribe(std::shared_ptr<nt::NetworkTable> table, int id) {
        X = table->GetDoubleTopic("Apriltag " + std::to_string(id) + " X").Subscribe(0.0);
        Y = table->GetDoubleTopic("Apriltag " + std::to_string(id) + " Y").Subscribe(0.0);
        Z = table->GetDoubleTopic("Apriltag " + std::to_string(id) + " Z").Subscribe(0.0);
        visible = table->GetBooleanTopic("Apriltag " + std::to_string(id)).Subscribe(false);
        correctedX = table->GetDoubleTopic("ApriltagCorrected " + std::to_string(id) + " X").Subscribe(0.0);
        correctedY = table->GetDoubleTopic("ApriltagCorrected " + std::to_string(id) + " Y").Subscribe(0.0);
        correctedZ = table->GetDoubleTopic("ApriltagCorrected " + std::to_string(id) + " Z").Subscribe(0.0);
    }

    XYZCoords GetXYZ() {
         
    }

    XYZCoordsCurrent GetXYZCurrent() {

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

        nt::DoubleSubscriber Apriltag3X;
        nt::DoubleSubscriber Apriltag3Y;
        nt::DoubleSubscriber Apriltag3Z;

        nt::DoubleSubscriber Apriltag5X;
        nt::DoubleSubscriber Apriltag5Y;
        nt::DoubleSubscriber Apriltag5Z;

        nt::DoubleSubscriber Apriltag6X;
        nt::DoubleSubscriber Apriltag6Y;
        nt::DoubleSubscriber Apriltag6Z;

        nt::DoubleSubscriber Apriltag7X;
        nt::DoubleSubscriber Apriltag7Y;
        nt::DoubleSubscriber Apriltag7Z;

        nt::BooleanSubscriber Apriltag3;
        nt::BooleanSubscriber Apriltag5;
        nt::BooleanSubscriber Apriltag6;
        nt::BooleanSubscriber Apriltag7;

        nt::DoubleSubscriber ApriltagCorrected3X;
        nt::DoubleSubscriber ApriltagCorrected3Y;
        nt::DoubleSubscriber ApriltagCorrected3Z;

        nt::DoubleSubscriber ApriltagCorrected5X;
        nt::DoubleSubscriber ApriltagCorrected5Y;
        nt::DoubleSubscriber ApriltagCorrected5Z;

        nt::DoubleSubscriber ApriltagCorrected6X;
        nt::DoubleSubscriber ApriltagCorrected6Y;
        nt::DoubleSubscriber ApriltagCorrected6Z;

        nt::DoubleSubscriber ApriltagCorrected7X;
        nt::DoubleSubscriber ApriltagCorrected7Y;
        nt::DoubleSubscriber ApriltagCorrected7Z;

        nt::DoubleSubscriber FPS;
        std::map<int, AprilTagSubscriber> AprilTagSubscribers;
};