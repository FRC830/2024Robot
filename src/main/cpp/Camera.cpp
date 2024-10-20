#include <string>
#include <photon/PhotonCamera.h>
#include <Camera.h>


int Camera::id()
{
    return target.GetFiducialId();
}
double Camera::yaw()
{
    return target.GetYaw();
}
double Camera::pitch()
{
    return target.GetPitch();
}
Camera::Camera(std::string name)
{
    camera = photon::PhotonCamera {name};
    result = camera.GetLatestResult();
    target = result.GetBestTarget();
}