#pragma once

#include "subsystems/IntakeHAL.h"

struct IntakeInput
{
    bool runIntakeOut;
    bool runIntakeIn;
    bool goToGroundPos;
    bool goToStowPos;
    bool goToAmpPos;
    bool goToPseudoStowPos;
    double manualMove;
};

class IntakeManager
{

public:
    void HandleInput(IntakeInput &input);
    
private:
    IntakeHAL m_intake;
    bool m_goToGroundPos;
    bool m_goToStowPos;
    bool m_goToAmpPos;
    bool m_goToPseudoStowPos;
};