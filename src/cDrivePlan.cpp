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
    ss << "Drive Plan: " << myName << "\r\n"
       << "time\t";
    for (auto &p : myPlan)
    {
        ss << p.myTime << "\t";
    }
    ss << "\r\nspeed\t";
    for (auto &p : myPlan)
    {
        ss << p.mySpeed << "\t";
    }

    return ss.str();
}

void cDrivePlan::parse(const std::string &t)
{
    std::istringstream ss(t);
    std::string token;
    std::vector<int> vtime;

    myName = "";
    myPlan.clear();

    ss >> token;
    ss >> token;

    while (true)
    {
        ss >> token;
        if (token == "time")
            break;
        myName += " " + token;
    }
    while (true)
    {
        ss >> token;
        if (token == "speed")
            break;
        vtime.push_back(atof(token.c_str()));
    }
    double speed;
    for (int k = 0; k < vtime.size(); k++)
    {
        ss >> speed;
        add(vtime[k], speed);
    }
    //std::cout << text();
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

void cSpaceTimePoint::Calculate(const resultStore &results)
{
    cResult less, more;
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