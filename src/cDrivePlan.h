#include <vector>
#include <string>


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
    double acceleration(int a, int b)
    {
        return myPlan[a].acceleration(myPlan[b]);
    }
    int deltaTime(int a, int b)
    {
        return myPlan[b].myTime - myPlan[a].myTime;
    }

    std::string text() const;
};

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
    void Calculate(const std::vector<sResult> &results);
    std::string text() const;
};