#include <iostream>
#include <sstream>
#include <iomanip>
#include "sumo.h"

double cDrivePoint::acceleration(const cDrivePoint &other) const
{

    if (mySpeed == other.mySpeed)
        return 0;
    int deltaTime = other.myTime - myTime;
    if (deltaTime < 0)
        deltaTime *= -1;
    if (deltaTime == 0)
        return 0;
    double deltaSpeed = other.mySpeed - mySpeed;
    return deltaSpeed / deltaTime;
}
std::string cDrivePlan::text() const
{
    std::stringstream ss;
    ss << "Drive Plan: " << myName << "\n"
       << "time\tspeed\n";
    for (auto &p : myPlan)
    {
        ss << p.myTime << "\t" << p.mySpeed << "\n";
    }
    return ss.str();
}

cDrivePlan *GenerateDrivePlanRaceTheLight()
{
    static cDrivePlan dp("Race the Light");
    dp.add(0, 0);
    dp.add(7, 30);
    return &dp;
}
cDrivePlan *GenerateDrivePlanCautious()
{
    static cDrivePlan dp("Cautious");
    dp.add(0, 0);
    dp.add(4, 30);
    dp.add(6, 0);
    return &dp;
}

void cSpaceTimePoint::Calculate(const std::vector<sResult> &results)
{
    sResult less, more;
    for (auto &r : results)
    {
        if (r.dist < distance)
            less = r;
        if (r.dist >= distance)
        {
            more = r;
            break;
        }
    }
    if (more.time >= 0)
    {
        // interpolation
        double deltadist = more.dist - less.dist;
        if (deltadist < 0.5)
        {
            time_to_dist = less.time;
            speed_at_distance = less.speed;
            return;
        }
        double f = (distance - less.dist) / deltadist;
        time_to_dist = less.time + f * (more.time - less.time);
        speed_at_distance = less.speed + f * (more.speed - less.speed);
    }
    else
    {
        // extrapolation
        time_to_dist = -1;
        speed_at_distance = -1;
    }
}
std::string cSpaceTimePoint::text() const
{
    std::stringstream ss;
    ss << std::setw(10) << distance << std::setw(5) << time;
    if (time_to_dist == -1 &&
        speed_at_distance == -1)
    {
        ss << " never reached\n";
    }
    else
    {
        ss << std::setw(15) << time_to_dist 
           << std::setw(15) << speed_at_distance
            << "\n";
    }
    return ss.str();
}