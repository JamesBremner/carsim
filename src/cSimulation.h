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
    void add(const cSpaceTimePoint& stp )
    {
        mySpaceTime.push_back( stp );
    }
    void Run( const std::string& drivePlanName );

    std::vector< std::string> DrivePlanNameList() const;

    std::string titleText() const;
    std::string resultText() const;

    const std::vector<sResult>& results() const
    {
        return myResults;
    }

    cDrivePlan* plan( int i )
    {
        return myPlan[ i ];
    }


private:
    cCar *myCar;
    std::vector< cDrivePlan * > myPlan;
    cDrivePlan * thePlan;                   // the plan being simulated
    std::vector< cSpaceTimePoint > mySpaceTime;
    std::vector<sResult> myResults;

    cDrivePlan * findPlan( const std::string& drivePlanName );
};