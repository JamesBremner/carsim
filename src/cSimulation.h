
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
    void Run( const std::string& drivePlanName );

    std::string titleText();

private:
    cCar *myCar;
    std::vector< cDrivePlan * > myPlan;
    cDrivePlan * thePlan;                   // the plan being simulated

    cDrivePlan * findPlan( const std::string& drivePlanName );
};