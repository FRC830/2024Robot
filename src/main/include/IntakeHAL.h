
struct IntakeHALConfig
{

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
        double m_speed;

        void SetAngle(double angle);
};