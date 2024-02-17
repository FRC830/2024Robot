#include "ControllerInterface.h"

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{
    UpdateIntakeInput(controlData);
    UpdateLauncherInput(controlData);
    UpdateSwerveInput(controlData);
};

void ControllerInterface::UpdateIntakeInput(RobotControlData &controlData)
{
    controlData.intakeInput.goToAmpPos = m_copilot.GetYButton();
    controlData.intakeInput.goToStowPos = m_copilot.GetAButton();
    controlData.smartIntakeInput.smartIntake = m_copilot.GetLeftBumper();
    controlData.smartIntakeInput.smartOutTake = m_copilot.GetRightBumper();
    controlData.intakeInput.runIntakeIn = m_copilot.GetLeftTriggerAxis() >= 0.2;
    controlData.intakeInput.runIntakeOut = m_copilot.GetRightTriggerAxis() >= 0.2;

    // This for debug purposes only
    controlData.smartIntakeInput.laser = m_copilot.GetLeftStickButton();
};

void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData)
{
    controlData.launcherInput.goToStowPos = m_copilot.GetBackButton();
    controlData.launcherInput.goToSubPos = m_copilot.GetStartButton();
    controlData.launcherInput.runIndexerForward = m_copilot.GetXButton();
    controlData.launcherInput.runIndexerBackward = m_copilot.GetBButton();
    //controlData.launcherInput.useVisionControl = m_copilot.GetYButton();
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