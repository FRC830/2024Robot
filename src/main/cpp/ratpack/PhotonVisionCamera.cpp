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
std::optional<photon::EstimatedRobotPose> PhotonVisionCamera::GetPose()
{

    auto result = poseEstimator->Update();
    return result;

}
