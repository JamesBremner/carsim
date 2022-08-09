#include <iostream>
#include <sstream>
#include <iomanip> 

#include "sumo.h"

void cCar::Run(const std::string &drivePlanName)
{

    myResults.clear();

    thePlan = findPlan(drivePlanName);
    if (!thePlan)
        return;
    if (thePlan->myPlan.size() < 2)
        return;

    std::cout << titleText();

    // track total fuel consumption
    double consumption = 0;
    int totalDist = 0;
    int totalTime = 0;

    // loop over drive plan points
    for (int kdp = 0; kdp < thePlan->size() - 1; kdp++)
    {
        // acceleration needed to reach next drive plan point
        double acceleration = thePlan->acceleration(kdp, kdp + 1);

        // loop over time till next drive plan point
        int t = -1;
        for (
            int simt = thePlan->myPlan[kdp].myTime;
            simt <= thePlan->myPlan[kdp + 1].myTime;
            simt++)
        {

            // calculate using the equations of motion
            // v = u + at
            // s = ut + ½at²
            t++;
            double speed =
                thePlan->myPlan[kdp].mySpeed + acceleration * t;
            if (speed < 0)
                speed = 0;
            double dist =
                thePlan->myPlan[kdp].mySpeed * t + 0.5 * acceleration * t * t;

            // look up the fuel consumption, adding to total
            consumption +=
                myFuelTable->consumption(
                    speed, acceleration);

            if (!(simt > 0 && t == 0))
            {
                cResult result;
                result.time = simt;
                result.dist = totalDist + (int)dist;
                result.speed = speed;
                result.accel = acceleration;
                result.fuel = consumption;
                myResults.push_back(result);
            }

            if (t == thePlan->myPlan[1].myTime)
            {
                totalTime += t;
                totalDist += (int)dist;
            }
        }
    }

    for( auto& stp : mySpaceTime )
    {
        stp.Calculate( myResults );
    }

    std::cout << resultText();
}

std::string cCar::resultText() const
{
    std::stringstream ss;
    ss << std::setw(5) << "time"
        << std::setw(10) <<"dist"
        << std::setw(10) <<"speed"
        << std::setw(10) << "accel"
        << std::setw(10) << "fuel\n";
    for (auto &r : myResults)
    {
        ss << std::setw(5) << r.time
           << std::setw(10) << r.dist
           << std::setw(10) << r.speed
           << std::setw(10) << r.accel
           << std::setw(10) << r.fuel
           << "\n";
    }
    ss << "\nSpace Time\n"
        << std::setw(10) << "dist"
        << std::setw(5) << "time"
        << std::setw(15) << "time at dist"
        << std::setw(15) << "speed at dist\n";
    for( auto& p : mySpaceTime )
    {
        ss << p.text();
    }
    return ss.str();
}

std::string cCar::titleText() const
{
    std::stringstream ss;
    ss << "Simulation Run\n"
       << thePlan->text();
    return ss.str();
}

cDrivePlan *cCar::findPlan(const std::string &drivePlanName)
{
    for (auto p : myPlan)
    {
        if (p->myName == drivePlanName)
            return p;
    }
    return 0;
}

std::vector<std::string> cCar::DrivePlanNameList() const
{
    std::vector<std::string> list;
    for (auto p : myPlan)
        list.push_back(p->myName);
    return list;
}