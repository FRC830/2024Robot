#pragma once

#include "SubSystemConfig.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/Timer.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/DoubleTopic.h>
#include <networktables/IntegerTopic.h>
#include <networktables/StringTopic.h>

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
        void PublishDebugInfo();
        

    private:
        rev::CANSparkMax m_RGTActMotor{RGT_INTAKE_ACT_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_LFTActMotor{LFT_INTAKE_ACT_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_RGTPvtMotor{INTAKE_PVT_MTR_A, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_LFTPvtMotor{INTAKE_PVT_MTR_B, rev::CANSparkMax::MotorType::kBrushless};
    
        rev::SparkRelativeEncoder m_LFTPvtRelEncoder = m_LFTPvtMotor.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor, 42);
        rev::SparkAbsoluteEncoder m_LFTPvtAbsEncoder = m_LFTPvtMotor.GetAbsoluteEncoder(rev::SparkAbsoluteEncoder::Type::kDutyCycle);
        rev::SparkPIDController m_LFTPvtPID = m_LFTPvtMotor.GetPIDController();

        ctre::phoenix6::hardware::CANcoder m_PvtCanCoder{INTAKE_PVT_ENCODER_ID, "rio"};

        frc::Timer m_Timer; 

        frc::TrapezoidProfile<units::degrees> m_Profile{

                frc::TrapezoidProfile<units::degrees>::Constraints{60_deg_per_s, 30_deg_per_s_sq}  
                
            };

        nt::DoublePublisher pub_intakeSpeed;
        nt::DoublePublisher pub_angle;
        nt::DoublePublisher pub_speed;
        nt::StringPublisher pub_profileState;

        double m_ProfileStartPos; 
        
        double m_intakeSpeed;
        int m_profileState = 0;
        void SetAngle(double angle);
};