#pragma once
#include "RobotControlData.h"

class SmartIntake{
public:
    SmartIntake();
    ~SmartIntake() = default;
    void HandleInput(RobotControlData& input);
    
private:
    bool m_SmartIntakeFlag;
    bool m_prevSmartIntake;
    
    bool m_SmartOutTakeFlag;
    bool m_prevSmartOutTake;
    
    bool m_SwitchModeFlag;
    bool m_prevSwitchMode;

    int m_IntakeState;
    int m_OutTakeState;
   };
