
class cCar
{
    public:
    void set( cFuelTable& table )
    {
        myFuelTable = &table;
    }
    cFuelTable * fuelTable()
    {
        return myFuelTable;
    }
    private:
    cFuelTable * myFuelTable;
};

class cSimulation
{
    public:
    void set( cCar& car)
    {
        myCar = &car;
    }
    void set( cDrivePlan& plan )
    {
        myPlan = &plan;
    }
    void Run();

    private:
    cCar* myCar;
    cDrivePlan* myPlan;
};