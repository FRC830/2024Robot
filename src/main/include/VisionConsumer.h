#pragma once

#include <networktables/NetworkTableInstance.h>
#include <networktables/DoubleTopic.h>
#include <networktables/BooleanTopic.h>

struct VisionConsumerConfig {
    nt::DoubleTopic aprilTagCoords;
};

class VisionConsumer {

    public:
        void Configure(VisionConsumerConfig &config);
        void GetVisionInfoFromNetworkTabe();

        explicit VisionConsumer() {
            
            AprilTag5X = aprilTagCoords.Subscribe(0.0);
            AprilTag5Y = aprilTagCoords.Subscribe(0.0);
            AprilTag5Z = aprilTagCoords.Subscribe(0.0);

            AprilTag6X = aprilTagCoords.Subscribe(0.0);
            AprilTag6Y = aprilTagCoords.Subscribe(0.0);
            AprilTag6Z = aprilTagCoords.Subscribe(0.0);

            AprilTag7X = aprilTagCoords.Subscribe(0.0);
            AprilTag7Y = aprilTagCoords.Subscribe(0.0);
            AprilTag7Z = aprilTagCoords.Subscribe(0.0);
        } 

        void Periodic() {
            AprilTag5X.Get(-1.0);
            AprilTag5Y.Get(-1.0);
            AprilTag5Z.Get(-1.0);

            AprilTag6X.Get(-1.0);
            AprilTag6Y.Get(-1.0);
            AprilTag6Z.Get(-1.0);

            AprilTag7X.Get(-1.0);
            AprilTag7Y.Get(-1.0);
            AprilTag7Z.Get(-1.0);
        }

        private:            
            std::shared_ptr<nt::NetworkTable> table;
            nt::DoubleTopic aprilTagCoords = table->GetDoubleTopic("vision");

            nt::DoubleSubscriber AprilTag5X;
            nt::DoubleSubscriber AprilTag5Y;
            nt::DoubleSubscriber AprilTag5Z;

            nt::DoubleSubscriber AprilTag6X;
            nt::DoubleSubscriber AprilTag6Y;
            nt::DoubleSubscriber AprilTag6Z;

            nt::DoubleSubscriber AprilTag7X;
            nt::DoubleSubscriber AprilTag7Y;
            nt::DoubleSubscriber AprilTag7Z;


};