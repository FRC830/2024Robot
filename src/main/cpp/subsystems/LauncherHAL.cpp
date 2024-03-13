#include "subsystems/LauncherHAL.h"
#include <iostream>
#include <unistd.h>

LauncherHAL::LauncherHAL()
{
    bool successfulConfig = false;
    int numRetries = 0;
    rev::REVLibError error;

    while (!successfulConfig && numRetries <= 20)
    {
        std::cout << "Retrying flash for LauncherHAL" << std::endl;
        numRetries++;
   
        error = m_PvtMotor.RestoreFactoryDefaults();
        usleep(200000);
        if (error != rev::REVLibError::kOk) continue;
        error = m_IndMotor.RestoreFactoryDefaults();
        usleep(200000);
        if (error != rev::REVLibError::kOk) continue;

        error = m_PvtMotor.SetCANTimeout(50);
        if (error != rev::REVLibError::kOk) continue;
        error = m_IndMotor.SetCANTimeout(50);
        if (error != rev::REVLibError::kOk) continue;
        

        error = m_PvtMotor.EnableVoltageCompensation(VOLT_COMP);
        if (error != rev::REVLibError::kOk) continue;
        error = m_IndMotor.EnableVoltageCompensation(VOLT_COMP);
        if (error != rev::REVLibError::kOk) continue;
      
        error = m_PvtMotor.SetSmartCurrentLimit(LAUNCHER_PVT_CURRENT_LIMIT);
        if (error != rev::REVLibError::kOk) continue;
        error = m_IndMotor.SetSmartCurrentLimit(LAUNCHER_IND_CURRENT_LIMIT);
        if (error != rev::REVLibError::kOk) continue;

        error = m_PvtMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
        if (error != rev::REVLibError::kOk) continue;
        
        m_PvtMotor.SetInverted(true);
        if (m_PvtMotor.GetInverted() != true) continue;

        error = m_PvtMotor.BurnFlash();
        if (error != rev::REVLibError::kOk) continue;
        error = m_IndMotor.BurnFlash();
        if (error != rev::REVLibError::kOk) continue;

        error = m_PvtPID.SetPositionPIDWrappingEnabled(false);
        if (error != rev::REVLibError::kOk) continue;

        error = m_PvtPID.SetP(PVT_P);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PvtPID.SetI(PVT_I);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PvtPID.SetD(PVT_D);
        if (error != rev::REVLibError::kOk) continue;

        error = m_PvtPID.SetFeedbackDevice(m_PvtAbsEncoder);
        if (error != rev::REVLibError::kOk) continue;

        error = m_PvtAbsEncoder.SetInverted(true);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PvtAbsEncoder.SetPositionConversionFactor(LAUNCHER_PVT_ABS_ENC_CONVERSION_FACTOR);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PvtAbsEncoder.SetZeroOffset(LAUNCHER_ZERO_OFFSET);
        if (error != rev::REVLibError::kOk) continue;
        
        successfulConfig = true;

        std::cout << "Flashing complete" << std::endl;
    }





    ctre::phoenix6::configs::TalonFXConfiguration configs{};

    configs.Slot0.kP = FLYWHEEL_P;
    configs.Slot0.kI = FLYWHEEL_I;
    configs.Slot0.kD = FLYWHEEL_D;

    configs.MotionMagic.MotionMagicJerk = MAX_JERK;

    m_FlywheelBottom.SetControl(m_FlywheelTopFollower);
    
    m_FlywheelTop.GetConfigurator().Apply(configs);
    m_FlywheelBottom.GetConfigurator().Apply(configs);

}

void LauncherHAL::SetFlywheelSpeed(double speed)
{   
    if (INVERT_FLYWHEEL)
    {
        speed = -speed;
    }

    units::angular_velocity::turns_per_second_t speed_tps = units::angular_velocity::turns_per_second_t(speed);
    ctre::phoenix6::controls::MotionMagicVelocityVoltage m_request{speed_tps};
        
    if (std::fabs(speed) > 1.0)
    {
        m_request.Acceleration = units::turns_per_second_squared_t(UP_MAX_ACC);
    }
    else
    {
        m_request.Acceleration = units::turns_per_second_squared_t(DOWN_MAX_ACC);
    }

    m_FlywheelTop.SetControl(m_request.WithVelocity(speed_tps));
}

void LauncherHAL::SetIndexerSpeed(double speed)
{
    if (INVERT_INDEXER)
    {
        m_indexerSpeed = -speed;
    }
    else
    {
        m_indexerSpeed = speed;
    }

    m_IndMotor.Set(m_indexerSpeed);
}

void LauncherHAL::SetAngle(double angle)
{
    if (angle > MAX_PIVOT_ANGLE)
    {
        angle = MAX_PIVOT_ANGLE;
    }
    else if (angle < MIN_PIVOT_ANGLE)
    {
        angle = MIN_PIVOT_ANGLE;
    }

    m_PvtPID.SetReference(angle, rev::CANSparkMax::ControlType::kPosition);
}

void LauncherHAL::ProfiledMoveToAngle(double angle)
{
    switch(m_profileState)
    {
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

double LauncherHAL::GetAngle()
{
    return m_PvtAbsEncoder.GetPosition();
}

double LauncherHAL::GetFlywheelSpeed()
{
    return m_FlywheelTop.GetVelocity().GetValueAsDouble();
}

void LauncherHAL::ResetProfiledMoveState()
{
    m_profileState = 0;
}