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
    for (auto &p : myPlan)
    {
        ss << p.myTime << "\t" << p.mySpeed << "\n";
    }
    return ss.str();
}