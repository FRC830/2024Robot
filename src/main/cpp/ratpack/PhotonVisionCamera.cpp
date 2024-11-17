#include "ratpack/PhotonVisionCamera.h"

#include <string>


PhotonVisionCamera::PhotonVisionCamera(std::string name, frc::Transform3d robotToCamera)
    : robotToCam(robotToCamera)
{
    camera = std::make_shared<photon::PhotonCamera>(name);
    poseEstimator = std::make_shared<photon::PhotonPoseEstimator>(aprilTagFieldLayout,
                                                                  photon::PoseStrategy::MULTI_TAG_PNP_ON_COPROCESSOR,
                                                                  camera,
                                                                  robotToCamera);

    poseEstimator->SetMultiTagFallbackStrategy(photon::PoseStrategy::LOWEST_AMBIGUITY);
}
PosAndTime PhotonVisionCamera::GetPose()
{
    PosAndTime estimatedPosition;
    estimatedPosition.isValid = false;

    auto result = poseEstimator->Update();

    if (result.has_value())
    {
        auto value = result.value();
        estimatedPosition.isValid = true;
        estimatedPosition.position = value.estimatedPose;
        estimatedPosition.timestamp = value.timestamp;
    }

    return estimatedPosition;
}
