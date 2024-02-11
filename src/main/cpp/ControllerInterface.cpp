#include "ControllerInterface.h"

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{
    controlData.intakeInput.goToAmpPos = m_copilot.GetAButton();
    controlData.intakeInput.goToGroundPos = m_copilot.GetBButton();
    controlData.intakeInput.goToStowPos = m_copilot.GetXButton();
    controlData.intakeInput.runIntakeIn = m_copilot.GetLeftBumper();
    controlData.intakeInput.runIntakeOut = m_copilot.GetRightBumper();
    controlData.intakeInput.goToPseudoStowPos = m_copilot.GetLeftStickButton();
    
    controlData.launcherInput.goToStowPos = m_copilot.GetBackButton();
    controlData.launcherInput.goToSubPos = m_copilot.GetStartButton();
    controlData.launcherInput.runIndexer = m_copilot.GetRightStickButton();
    controlData.launcherInput.useVisionControl = m_copilot.GetYButton();
};

void ControllerInterface::UpdateSwerveInput(RobotControlData &controlData)
{
    controlData.swerveInput.slowMode = m_pilot.GetAButton();
  
    controlData.swerveInput.yTranslation = m_pilot.GetLeftY();
    controlData.swerveInput.xTranslation = m_pilot.GetLeftX();
    controlData.swerveInput.rotation = -m_pilot.GetRightX();

    if (controlData.swerveInput.slowMode)
    {
        controlData.swerveInput.xTranslation *= m_slowmodefactor;
        controlData.swerveInput.yTranslation *= m_slowmodefactor;
        controlData.swerveInput.rotation *= m_slowmodefactor;
    }
};