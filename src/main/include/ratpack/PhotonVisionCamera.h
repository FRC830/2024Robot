#include <string>
#include <photon/PhotonCamera.h>

struct posAndTime {
    frc::Transform3d position;
    double timestamp;
};

class PhotonVisionCamera
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
        Camera(std::string name);
        posAndTime position();
};