#include <string>
#include <photon/PhotonCamera.h>
#include <PhotonVisionCamera.h>


int PhotonVisionCamera::id()
{
    return target.GetFiducialId();
}

PhotonVisionCamera::PhotonVisionCamera(std::string name)
{
    camera = photon::PhotonCamera{name};
    result = camera.GetLatestResult();
    target = result.GetBestTarget();
}
PhotonVisionCamera::position()
{
    result = camera.getLatestResult();
    auto visionEst = vision.GetEstimatedGlobalPose();
    auto est = visionEst.value();
    if (result.MultiTagResult().result.isPresent) 
    {
        frc::Transform3d fieldToCamera = result.MultiTagResult().result.best;
    }
    posAndTime thing;
    thing.position = fieldToCamera
    thing.timestamp = est.timestamp;

    return thing;
}
