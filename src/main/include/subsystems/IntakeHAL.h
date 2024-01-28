#pragma once

#include "SubSystemConfig.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/Timer.h>



class IntakeHAL
{
    public: 
        IntakeHAL(); 
        ~IntakeHAL();
        void RunIntake(double speed);
        void ProfiledMoveToAngle(double angle);
        void ManualMovePivot(double speed);
        double GetAngle(); 
        double GetSpeed();
        void ResetProfiledMoveState();


    
    private:
        rev::CANSparkMax m_RGTActMotor{RGT_INTAKE_ACT_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_LFTActMotor{LFT_INTAKE_ACT_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_RGTPvtMotor{INTAKE_PVT_MTR_A, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_LFTPvtMotor{INTAKE_PVT_MTR_B, rev::CANSparkMax::MotorType::kBrushless};
        
        rev::SparkMaxRelativeEncoder m_LFTPvtEncoder = m_LFTPvtMotor.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor, 42);
        rev::SparkPIDController m_LFTPvtPID = m_LFTPvtMotor.GetPIDController();

        ctre::phoenix6::hardware::CANcoder m_PvtCanCoder{INTAKE_PVT_ENCODER_ID, "rio"};

        frc::Timer m_Timer; 

        frc::TrapezoidProfile<units::meters> m_Profile{

                frc::TrapezoidProfile<units::meters>::Constraints{0_mps, 0_mps_sq}  
                
            };

        double m_ProfileStartPos; 
        
        double m_intakeSpeed;
        int m_profileState = 0;
        void SetAngle(double angle);
};