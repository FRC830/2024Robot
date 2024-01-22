#pragma once

#include "SubSystemConfig.h"


struct IntakeHALConfig
{
    rev::CANSparkMax *RGTActMotor;
    rev::CANSparkMax *LFTActMotor;
    rev::CANSparkMax *RGTPvtMotor;
    rev::CANSparkMax *LFTPvtMotor;
    ctre::phoenix::sensors::CANCoder *encoder;


    double PVTCalibrate;
    double intakeSpeed;  
    double turningspeed;  
};

class IntakeHAL
{
    public: 
        void RunIntake(double speed);
        void ProfiledMoveToAngle(double angle);
        void ManualMovePivot(double speed);
        double GetAngle(); 
        double GetSpeed();
        void Configure(IntakeHALConfig &config);

    
    private:
        rev::CANSparkMax *m_RGTActMotor;
        rev::CANSparkMax *m_LFTActMotor;
        rev::CANSparkMax *m_RGTPvtMotor;
        rev::CANSparkMax *m_LFTPvtMotor;

        frc::MotorControllerGroup *m_ActMotors;
        frc::MotorControllerGroup *m_PvtMotors;
        
        ctre::phoenix::sensors::CANCoder *m_PVTEncoder; 


        double m_PVTCalibrate;
        double m_intakeSpeed;
        double m_turningSpeed;
        void SetAngle(double angle);
};