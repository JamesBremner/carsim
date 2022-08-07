#include <sstream>
#include "cDrivePlan.h"

double cDrivePoint::acceleration(const cDrivePoint &other) const
{

    if( mySpeed == other.mySpeed )
        return 0;
    int deltaTime = other.myTime - myTime;
    if( deltaTime < 0 )
        deltaTime *= -1;
    if( deltaTime == 0 )
        return 0;
    double deltaSpeed = other.mySpeed - mySpeed;
    return deltaSpeed / deltaTime;

}
std::string cDrivePlan::text() const
{
    std::stringstream ss;
    ss << "Drive Plan: " << myName <<"\n"
        << "time\tspeed\n";
    for (auto &p : myPlan)
    {
        ss << p.myTime << "\t" << p.mySpeed << "\n";
    }
    return ss.str();
}

cDrivePlan * GenerateDrivePlanRaceTheLight()
{
    static cDrivePlan dp("Race the Light");
    dp.add(0, 0);
    dp.add(7, 30);
    return &dp;
}
cDrivePlan * GenerateDrivePlanCautious()
{
    static cDrivePlan dp("Cautious");
    dp.add(0, 0);
    dp.add(4, 30);
    dp.add(6, 0);
    return &dp; 
}