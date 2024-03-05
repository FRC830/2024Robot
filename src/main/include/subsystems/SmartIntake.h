#pragma once
#include "RobotControlData.h"
#include <frc/DigitalInput.h>

class SmartIntake{
public:
    SmartIntake();
    ~SmartIntake() = default;
    void HandleInput(RobotControlData& input);
    void ResetSmartIntake();
    
private:
    bool m_SmartIntakeFlag;
    bool m_prevSmartIntake;
    
    bool m_SmartOutTakeFlag;
    bool m_prevSmartOutTake;
    
    bool m_SwitchModeFlag;
    bool m_prevSwitchMode;

    int m_IntakeState;
    int m_OutTakeState;

    bool m_centerNote;
    int m_centerNoteState;

    frc::Timer m_timer;
    frc::DigitalInput m_beam_break{9};
    frc::DigitalInput m_front_beam_break{7};
   };
