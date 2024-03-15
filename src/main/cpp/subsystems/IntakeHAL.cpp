#include "subsystems/IntakeHAL.h"
#include "ratpack/CANSparkMaxDebugMacro.h"

IntakeHAL::IntakeHAL(){

    START_RETRYING(INTAKE_LFT_ACT_MTR_RESTORE_FACTORY_DEFAULT)
    m_LFTActMotor.RestoreFactoryDefaults();
    END_RETRYING
    START_RETRYING(INTAKE_LFT_PVT_MTR_RESTORE_FACTORY_DEFAULT)
    m_LFTPvtMotor.RestoreFactoryDefaults();
    END_RETRYING
    START_RETRYING(INTAKE_RGT_ACT_MTR_RESTORE_FACTORY_DEFAULT)
    m_RGTActMotor.RestoreFactoryDefaults();
    END_RETRYING
    START_RETRYING(INTAKE_RGT_PVT_MTR_RESTORE_FACTORY_DEFAULT)
    m_RGTPvtMotor.RestoreFactoryDefaults();
    END_RETRYING

    START_RETRYING(INTAKE_LFT_ACT_MTR_SET_CAN_TIMEOUT)
    m_LFTActMotor.SetCANTimeout(50);
    END_RETRYING
    START_RETRYING(INTAKE_LFT_PVT_MTR_SET_CAN_TIMEOUT)
    m_LFTPvtMotor.SetCANTimeout(50);
    END_RETRYING
    START_RETRYING(INTAKE_RGT_ACT_MTR_SET_CAN_TIMEOUT)
    m_RGTActMotor.SetCANTimeout(50);
    END_RETRYING
    START_RETRYING(INTAKE_RGT_PVT_MTR_SET_CAN_TIMEOUT)
    m_RGTPvtMotor.SetCANTimeout(50);
    END_RETRYING

    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            m_RGTActMotor.SetInverted(INVERT_INTAKE_ACT);

            if (m_RGTActMotor.GetInverted() == INVERT_INTAKE_ACT)
            {
                successful = true;
            }
        }

        if (successful)
        {
            std::cout << "Configured INTAKE_RGT_ACT_MTR_SET_INVERTED in " << retries << " retries" << std::endl;
        }
        else
        {
            std::cout << "Failed to configure INTAKE_RGT_ACT_MTR_SET_INVERTED" << std::endl;
        }
    }

    START_RETRYING(INTAKE_LFT_ACT_MTR_FOLLOW)
    m_LFTActMotor.Follow(m_RGTActMotor, true);
    END_RETRYING
    START_RETRYING(INTAKE_RGT_PVT_MTR_FOLLOW)
    m_RGTPvtMotor.Follow(m_LFTPvtMotor, false);
    END_RETRYING
    START_RETRYING(INTAKE_LFT_ACT_MTR_ENABLE_VOLTAGE_COMPENSATION)
    m_LFTActMotor.EnableVoltageCompensation(VOLT_COMP);
    END_RETRYING
    START_RETRYING(INTAKE_LFT_PVT_MTR_ENABLE_VOLTAGE_COMPENSATION)
    m_LFTPvtMotor.EnableVoltageCompensation(VOLT_COMP);
    END_RETRYING
    START_RETRYING(INTAKE_RGT_ACT_MTR_ENABLE_VOLTAGE_COMPENSATION)
    m_RGTActMotor.EnableVoltageCompensation(VOLT_COMP);
    END_RETRYING
    START_RETRYING(INTAKE_RGT_PVT_MTR_ENABLE_VOLTAGE_COMPENSATION)
    m_RGTPvtMotor.EnableVoltageCompensation(VOLT_COMP);
    END_RETRYING

    START_RETRYING(INTAKE_LFT_PVT_PID_SETP)
    m_LFTPvtPID.SetP(INTAKE_P);
    END_RETRYING
    START_RETRYING(INTAKE_LFT_PVT_PID_SETI)
    m_LFTPvtPID.SetI(INTAKE_I);
    END_RETRYING
    START_RETRYING(INTAKE_LFT_PVT_PID_SETD)
    m_LFTPvtPID.SetD(INTAKE_D);
    END_RETRYING
    
    START_RETRYING(INTAKE_LFT_ACT_MTR_SET_SMART_CURRENT_LIMIT)
    m_LFTActMotor.SetSmartCurrentLimit(INTAKE_ACT_CURRENT_LIMIT);
    END_RETRYING
    START_RETRYING(INTAKE_LFT_PVT_MTR_SET_SMART_CURRENT_LIMIT)
    m_LFTPvtMotor.SetSmartCurrentLimit(INTAKE_PVT_CURRENT_LIMIT);
    END_RETRYING
    START_RETRYING(INTAKE_RGT_ACT_MTR_SET_SMART_CURRENT_LIMIT)
    m_RGTActMotor.SetSmartCurrentLimit(INTAKE_ACT_CURRENT_LIMIT);
    END_RETRYING
    START_RETRYING(INTAKE_RGT_PVT_MTR_SET_SMART_CURRENT_LIMIT)
    m_RGTPvtMotor.SetSmartCurrentLimit(INTAKE_PVT_CURRENT_LIMIT);
    END_RETRYING

    START_RETRYING(INTAKE_LFT_PVT_PID_SET_FEEDBACK_DEVICE)
    m_LFTPvtPID.SetFeedbackDevice(m_LFTPvtAbsEncoder);
    END_RETRYING

    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            m_LFTPvtMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

            if (m_LFTPvtMotor.GetIdleMode() == rev::CANSparkMax::IdleMode::kBrake)
            {
                successful = true;
            }
        }

        if (successful)
        {
            std::cout << "Configured INTAKE_LFT_PVT_MTR_SET_IDLE_MODE in " << retries << " retries" << std::endl;
        }
        else
        {
            std::cout << "Failed to configure INTAKE_LFT_PVT_MTR_SET_IDLE_MODE" << std::endl;
        }
    }

    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            m_RGTPvtMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

            if (m_RGTPvtMotor.GetIdleMode() == rev::CANSparkMax::IdleMode::kBrake)
            {
                successful = true;
            }
        }

        if (successful)
        {
            std::cout << "Configured INTAKE_RGT_PVT_MTR_SET_IDLE_MODE in " << retries << " retries" << std::endl;
        }
        else
        {
            std::cout << "Failed to configure INTAKE_RGT_PVT_MTR_SET_IDLE_MODE" << std::endl;
        }
    }
    
    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            m_LFTPvtAbsEncoder.SetInverted(LFT_PVT_ABS_ENC_INVERTED);

            if (m_LFTPvtAbsEncoder.GetInverted() == LFT_PVT_ABS_ENC_INVERTED)
            {
                successful = true;
            }
        }

        if (successful)
        {
            std::cout << "Configured INTAKE_LFT_PVT_ABS_ENC_SET_INVERTED in " << retries << " retries" << std::endl;
        }
        else
        {
            std::cout << "Failed to configure INTAKE_LFT_PVT_ABS_ENC_SET_INVERTED" << std::endl;
        }
    }

    START_RETRYING(INTAKE_LFT_PVT_ABS_ENC_SET_POSITION_CONVERSION_FACTOR)
    m_LFTPvtAbsEncoder.SetPositionConversionFactor(LFT_PVT_ABS_ENC_CONVERSION_FACTOR);
    END_RETRYING
    START_RETRYING(INTAKE_LFT_PVT_ABS_ENC_SET_ZERO_OFFSET)
    m_LFTPvtAbsEncoder.SetZeroOffset(INTAKE_ZERO_OFFSET);
    END_RETRYING

    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            m_LFTPvtMotor.SetInverted(LFT_PVT_MTR_INVERTED);

            if (m_LFTPvtMotor.GetInverted() == LFT_PVT_MTR_INVERTED)
            {
                successful = true;
            }
        }

        if (successful)
        {
            std::cout << "Configured INTAKE_LFT_PVT_MTR in " << retries << " retries" << std::endl;
        }
        else
        {
            std::cout << "Failed to configure INTAKE_LFT_PVT_MTR" << std::endl;
        }
    }

    START_RETRYING(INTAKE_LFT_ACT_MTR_BURN_FLASH)
    m_LFTActMotor.BurnFlash();
    END_RETRYING
    START_RETRYING(INTAKE_LFT_PVT_MTR_BURN_FLASH)
    m_LFTPvtMotor.BurnFlash();
    END_RETRYING
    START_RETRYING(INTAKE_RGT_ACT_MTR_BURN_FLASH)
    m_RGTActMotor.BurnFlash();
    END_RETRYING
    START_RETRYING(INTAKE_RGT_PVT_MTR_BURN_FLASH)
    m_RGTPvtMotor.BurnFlash();
    END_RETRYING


    auto inst = nt::NetworkTableInstance::GetDefault();
    std::shared_ptr<nt::NetworkTable> table = inst.GetTable("intake");
    pub_intakeSpeed = table->GetDoubleTopic("intake").Publish();
    pub_angle = table->GetDoubleTopic("intake").Publish();
    pub_speed = table->GetDoubleTopic("intake").Publish();
    pub_profileState = table->GetStringTopic("intake").Publish();
}


void IntakeHAL::RunIntake(double speed) {

    m_intakeSpeed = speed;

    m_RGTActMotor.Set(m_intakeSpeed);

}

void IntakeHAL::ProfiledMoveToAngle(double angle) {

    switch (m_profileState) {

        case 0: 
        {
            m_ProfileStartPos = GetAngle();

            m_Timer.Restart();

            m_profileState++;

            break;
        }
            

        case 1:
        {
            auto setPoint = m_Profile.Calculate(m_Timer.Get(),    
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_ProfileStartPos}, 0_deg_per_s},  
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{angle}, 0_deg_per_s}
            );

            SetAngle(setPoint.position.to<double>());

            if (m_Profile.IsFinished(m_Timer.Get())) {

                m_profileState++;

            }

            break;
        }

        case 2: 
        {

            m_Timer.Stop();

            m_profileState++;

            break;
        }
        
        default:
            break; 
    }

}

void IntakeHAL::ManualMovePivot(double speed) {

    SetAngle(GetAngle() + (speed * INTAKE_INPUT_TO_DEG));

}

void IntakeHAL::ResetProfiledMoveState() {

    m_profileState = 0;

}

void IntakeHAL::SetAngle(double angle) {

    m_LFTPvtPID.SetReference(angle, rev::CANSparkMax::ControlType::kPosition);

}

double IntakeHAL::GetAngle() {

     return m_LFTPvtAbsEncoder.GetPosition();

}

double IntakeHAL::GetSpeed() {

    return m_intakeSpeed;

}

void IntakeHAL::PublishDebugInfo()
{
    pub_intakeSpeed.Set(m_intakeSpeed);
    pub_angle.Set(GetAngle());
    pub_speed.Set(GetSpeed());

    std::string profileStateString;
    if(m_profileState == 0) profileStateString="ABOUT TO MOVE";
    if(m_profileState == 1) profileStateString="CURRENTLY MOVING";
    if(m_profileState == 2) profileStateString="FINISHED MOVE";
    if(m_profileState == 3) profileStateString="NOT MOVING";
    pub_profileState.Set(profileStateString);
}