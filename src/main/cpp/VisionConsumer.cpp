#include "VisionConsumer.h"
#include <networktables/NetworkTableInstance.h>

void VisionConsumer::Configure(VisionConsumerConfig &config) {
    auto inst = nt::NetworkTableInstance::GetDefault();
    table = inst.GetTable("SmartDashboard")->GetSubTable("vision");
    aprilTagCoords = table->GetDoubleTopic("vision");
    aprilTagVisible = table->GetBooleanTopic("vision");
};
