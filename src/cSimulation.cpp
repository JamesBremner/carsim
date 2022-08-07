#include <iostream>
#include <sstream>
#include "cFuelTable.h"
#include "cDrivePlan.h"
#include "cSimulation.h"

void cSimulation::Run( const std::string& drivePlanName )
{
    thePlan = findPlan( drivePlanName );
    if( ! thePlan )
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
                myCar->fuelTable()->consumption(
                    speed, acceleration);

            if (!(simt > 0 && t == 0))
                std::cout << simt
                          << "\t" << totalDist + (int)dist
                          << "\t" << speed
                          << "\t" << acceleration
                          << "\t" << consumption
                          << "\n";

            if (t == thePlan->myPlan[1].myTime)
            {
                totalTime += t;
                totalDist += (int)dist;
            }
        }
    }
}
std::string cSimulation::titleText()
{
    std::stringstream ss;
    ss << "Simulation Run\n"
       << thePlan->text()
       << "time\tdist\tspeed\taccel\tfuel\n";
    return ss.str();
}

cDrivePlan * cSimulation::findPlan( const std::string& drivePlanName )
{
    for( auto p : myPlan )
    {
        if( p->myName == drivePlanName )
            return p;
    }
    return 0;
}