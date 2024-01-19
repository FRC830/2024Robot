
struct IntakeHAL
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
        void Configure(IntakeHAL &config);

    
    private:
        double m_speed;

        void SetAngle(double angle);
};