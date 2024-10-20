#include <string>
#include <photon/PhotonCamera.h>

class Camera
{
    private:
    /*
        double yaw = target.GetYaw();
        double pitch = target.GetPitch();
        int targetID = target.GetFiducialId();
        double poseAmbiguity = target.GetPoseAmbiguity();
        */
       photon::PhotonCamera camera;
       photon::PhotonPipelineResult result;
       photon::PhotonTrackedTarget target;

    public:
        int id();
        //double ambiguity();
        double yaw();
        double pitch();
        Camera(std::string name);
};