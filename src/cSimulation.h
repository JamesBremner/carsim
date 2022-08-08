
class cCar
{
public:
    void set(cFuelTable *table)
    {
        myFuelTable = table;
    }
    cFuelTable *fuelTable()
    {
        return myFuelTable;
    }

private:
    cFuelTable *myFuelTable;
};

struct sResult
{
    int time;
    double dist;
    double speed;
    double accel;
    double fuel;
};

class cSimulation
{
public:
    void set(cCar &car)
    {
        myCar = &car;
    }
    void add(cDrivePlan *plan)
    {
        myPlan.push_back( plan );
    }
    void Run( const std::string& drivePlanName );

    std::vector< std::string> DrivePlanNameList() const;

    std::string titleText() const;
    std::string resultText() const;

    const std::vector<sResult>& results() const
    {
        return myResults;
    }


private:
    cCar *myCar;
    std::vector< cDrivePlan * > myPlan;
    cDrivePlan * thePlan;                   // the plan being simulated
    std::vector<sResult> myResults;

    cDrivePlan * findPlan( const std::string& drivePlanName );
};