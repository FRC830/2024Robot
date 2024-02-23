#include "AutoAimer.h"


AutoAimer::AutoAimer(WPISwerveDrive& swerve){


    m_vision = VisionConsumer();
    m_Swerve = swerve;


}

void TurnChasisToDeg(double deg) {

    m_Swerve->drive(0, 0, deg);

}

bool AutoAim() {


    


}