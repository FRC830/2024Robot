#pragma once

#include <networktables/NetworkTableInstance.h>
#include <networktables/DoubleTopic.h>
#include <networktables/BooleanTopic.h>

struct VisionConsumerConfig {
    nt::DoubleTopic aprilTagCoords;
    nt::BooleanTopic aprilTagVisible;
};

class VisionConsumer {

    public:
        void Configure(VisionConsumerConfig &config);

        explicit VisionConsumer() {

            Apriltag5X = aprilTagCoords.Subscribe(0.0);
            Apriltag5Y = aprilTagCoords.Subscribe(0.0);
            Apriltag5Z = aprilTagCoords.Subscribe(0.0);

            Apriltag6X = aprilTagCoords.Subscribe(0.0);
            Apriltag6Y = aprilTagCoords.Subscribe(0.0);
            Apriltag6Z = aprilTagCoords.Subscribe(0.0);

            Apriltag7X = aprilTagCoords.Subscribe(0.0);
            Apriltag7Y = aprilTagCoords.Subscribe(0.0);
            Apriltag7Z = aprilTagCoords.Subscribe(0.0);

            Apriltag5 = aprilTagVisible.Subscribe(false);            
            Apriltag6 = aprilTagVisible.Subscribe(false);
            Apriltag7 = aprilTagVisible.Subscribe(false);            
        } 

        void Periodic() {
            Apriltag5X.Get(-1.0);
            Apriltag5Y.Get(-1.0);
            Apriltag5Z.Get(-1.0);

            Apriltag6X.Get(-1.0);
            Apriltag6Y.Get(-1.0);
            Apriltag6Z.Get(-1.0);

            Apriltag7X.Get(-1.0);
            Apriltag7Y.Get(-1.0);
            Apriltag7Z.Get(-1.0);

            Apriltag5.Get();
            Apriltag6.Get();
            Apriltag7.Get();
        }

        private:            
            std::shared_ptr<nt::NetworkTable> table;
            nt::DoubleTopic aprilTagCoords = table->GetDoubleTopic("vision");
            nt::BooleanTopic aprilTagVisible = table->GetBooleanTopic("vision");

            nt::DoubleSubscriber Apriltag5X;
            nt::DoubleSubscriber Apriltag5Y;
            nt::DoubleSubscriber Apriltag5Z;

            nt::DoubleSubscriber Apriltag6X;
            nt::DoubleSubscriber Apriltag6Y;
            nt::DoubleSubscriber Apriltag6Z;

            nt::DoubleSubscriber Apriltag7X;
            nt::DoubleSubscriber Apriltag7Y;
            nt::DoubleSubscriber Apriltag7Z;

            nt::BooleanSubscriber Apriltag5;
            nt::BooleanSubscriber Apriltag6;
            nt::BooleanSubscriber Apriltag7;

};