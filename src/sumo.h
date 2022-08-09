#pragma once
#include <vector>

class cResult
{
    public:
    int time;
    double dist;
    double speed;
    double accel;
    double fuel;

    cResult()
    : time(-1)
    {}
};
typedef std::vector<cResult> resultStore;
class cFuelTable
{
    public:
    std::vector<double> myTable;
    cFuelTable();

    void add( double speed, double acceleration, double consumption );

    /// calculate fuel consumption
    double consumption( double speed, double acceleration ) const;

    std::string text() const;

    private:
    int index( double speed, double acceleration ) const;
};

cFuelTable * GenerateFuelTableA();

class cDrivePoint
{
public:
    int myTime;
    double mySpeed;

    cDrivePoint(int time, double speed)
        : myTime(time),
          mySpeed(speed)
    {
    }
    double acceleration(const cDrivePoint &other) const;
};

class cDrivePlan
{
public:
    std::vector<cDrivePoint> myPlan;
    std::string myName;

    cDrivePlan(const std::string &name)
        : myName(name)
    {
    }
    cDrivePlan()
    {}

    /** add drive plan point
     * @param[in] time secs
     * @param[in] speed km/hr
     */
    void add(int time, double speed)
    {
        myPlan.push_back({time, speed});
    }

    int size() const
    {
        return (int)myPlan.size();
    }
    
    /// Calculate acceleration required to get from point a to point b
    double acceleration(int a, int b)
    {
        return myPlan[a].acceleration(myPlan[b]);
    }
    int deltaTime(int a, int b)
    {
        return myPlan[b].myTime - myPlan[a].myTime;
    }

    std::string text() const;

    void parse( const std::string& text );
};

typedef std::vector< cDrivePlan* > drivePlanStore;

cDrivePlan *GenerateDrivePlanRaceTheLight();
cDrivePlan *GenerateDrivePlanCautious();

class cSpaceTimePoint
{
public:
    int distance;
    int time;
    int time_to_dist;
    int speed_at_distance;
    cSpaceTimePoint(int d, int t)
        : distance(d),
          time(t)
    {
    }
    void Calculate(const resultStore &results);

    std::string text() const;
};

typedef std::vector< cSpaceTimePoint > spaceTimeStore;

class cCar
{
public:

    void set( cFuelTable* ft )
    {
        myFuelTable = ft;
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

    const resultStore& results() const
    {
        return myResults;
    }

    cDrivePlan* plan( int i )
    {
        return myPlan[ i ];
    }


private:
    cFuelTable      *myFuelTable;
    drivePlanStore  myPlan;
    cDrivePlan      * thePlan;                   // the plan being simulated
    spaceTimeStore  mySpaceTime;
    resultStore     myResults;

    cDrivePlan * findPlan( const std::string& drivePlanName );
};
