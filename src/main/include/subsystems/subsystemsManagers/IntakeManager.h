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

enum class IntakePos
{
    AMP,
    GROUND,
    STOW,
    PSEUDO_STOW,
    UNKNOWN
};

struct IntakeOutput
{
    IntakePos intakePos;
};

class IntakeManager
{

public:
    void HandleInput(IntakeInput &input, IntakeOutput &output);
    void ResetIntake();

private:
    IntakeHAL m_intake;
    bool m_goToGroundPos;
    bool m_goToStowPos;
    bool m_goToAmpPos;
    bool m_goToPseudoStowPos;
};