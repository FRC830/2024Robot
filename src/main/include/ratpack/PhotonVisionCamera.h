#include <string>
#include <photon/PhotonCamera.h>
#include <photon/PhotonPoseEstimator.h>
#include <frc/geometry/Transform3d.h>
#include <frc/apriltag/AprilTagFieldLayout.h>
#include <frc/geometry/Pose3d.h>
#include <memory>

struct PosAndTime {
    frc::Transform3d position;
    double timestamp;
    bool isValid;
};

class PhotonVisionCamera
{
    private:
       std::shared_ptr<photon::PhotonCamera> camera;
       frc::AprilTagFieldLayout aprilTagFieldLayout = frc::LoadAprilTagLayoutField(frc::AprilTagField::k2024Crescendo);
       frc::Transform3d robotToCam;
       std::shared_ptr<photon::PhotonPoseEstimator> poseEstimator;

    public:
        PhotonVisionCamera(std::string name, frc::Transform3d robotToCamera);
        PosAndTime GetPose();
};