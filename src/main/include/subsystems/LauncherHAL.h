#pragma once

#include "SubSystemConfig.h"
#include <frc/Timer.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <units/length.h>
#include <units/velocity.h>
#include <units/angle.h>
#include <units/acceleration.h>
#include <frc/Timer.h>
#include <frc/trajectory/TrapezoidProfile.h>

struct LauncherHALConfig
{

};

class LauncherHAL
{
    public:    
        LauncherHAL();
        ~LauncherHAL();
        void Configure(LauncherHALConfig &config);
        void SetFlywheelSpeed(double speed);
        void SetIndexerSpeed(double speed);
        void ProfiledMoveToAngle(double angle);
        double GetAngle(); 
        double GetFlywheelSpeed();
        void ResetProfiledMoveState();

    private:
        rev::CANSparkMax m_PvtMotor{LAUNCHER_PVT_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_IndMotor{LAUNCHER_IND_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
        ctre::phoenix6::hardware::TalonFX m_FlywheelActMotorA{FLYWHEEL_ACT_MTR_A_ID};
        ctre::phoenix6::hardware::TalonFX m_FlywheelActMotorB{FLYWHEEL_ACT_MTR_B_ID};
        
        rev::SparkRelativeEncoder m_PvtEncoder = m_PvtMotor.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor, 42);
        rev::SparkPIDController m_PvtPID = m_PvtMotor.GetPIDController();
        ctre::phoenix6::hardware::CANcoder m_PvtCanCoder{LAUNCHER_PVT_ENCODER_ID};

        ctre::phoenix6::controls::Follower m_FlywheelActMtrBFollower = ctre::phoenix6::controls::Follower(FLYWHEEL_ACT_MTR_B_ID, true);


        frc::Timer m_Timer;

        frc::TrapezoidProfile<units::meters> m_Profile{

                frc::TrapezoidProfile<units::meters>::Constraints{0_mps, 0_mps_sq}  
                
            };
        
        double m_ProfileStartPos; 
        double m_indexerSpeed;
        int m_profileState = 0;

        void SetAngle(double angle);
};