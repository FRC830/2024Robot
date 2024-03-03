#include "ControllerInterface.h"

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{
    UpdateIntakeInput(controlData);
    UpdateLauncherInput(controlData);
    UpdateSwerveInput(controlData);
};

void ControllerInterface::UpdateIntakeInput(RobotControlData &controlData)
{
    controlData.intakeInput.goToAmpPos = m_copilot.GetLeftY() > 0.5;
    controlData.intakeInput.goToStowPos = m_copilot.GetLeftY() < -0.5;
    controlData.intakeInput.goToPseudoStowPos = m_copilot.GetLeftX() > 0.5;

    if (controlData.intakeOutput.intakePos == IntakePos::AMP)
    {
        controlData.intakeInput.runIntakeIn = m_copilot.GetRightTriggerAxis() > 0.2;
        controlData.launcherInput.runIndexerForward = false;
    }
    else
    {
        controlData.launcherInput.runIndexerForward = m_copilot.GetRightTriggerAxis() > 0.2;
        controlData.intakeInput.runIntakeIn = false;
    }

    controlData.smartIntakeInput.smartOutTake = m_copilot.GetRightBumper();
    controlData.smartIntakeInput.smartIntake = m_copilot.GetLeftBumper();
    // controlData.intakeInput.runIntakeOut = m_copilot.GetRightTriggerAxis() >= 0.2;
};

void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData)
{
    controlData.launcherInput.goToStowPos = m_copilot.GetAButton();
    controlData.launcherInput.goToSubPos = m_copilot.GetYButton();

    // controlData.launcherInput.runIndexerForward = m_copilot.GetRightTriggerAxis() >= 0.2;
    //controlData.launcherInput.runIndexerForward = m_copilot.GetXButton();
    //controlData.launcherInput.runIndexerBackward = m_copilot.GetBButton();
    //controlData.launcherInput.useVisionControl = m_copilot.GetYButton();
};

void ControllerInterface::UpdateSwerveInput(RobotControlData &controlData)
{
    controlData.swerveInput.slowMode = m_pilot.GetLeftBumper();
  
    controlData.swerveInput.xTranslation = -m_pilot.GetLeftY();
    controlData.swerveInput.yTranslation = -m_pilot.GetLeftX();
    controlData.swerveInput.rotation = -m_pilot.GetRightX();

    if (controlData.swerveInput.slowMode)
    {
        controlData.swerveInput.xTranslation *= m_slowmodefactor;
        controlData.swerveInput.yTranslation *= m_slowmodefactor;
        controlData.swerveInput.rotation *= m_slowmodefactor;
    }
};