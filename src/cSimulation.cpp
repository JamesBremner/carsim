#include <iostream>
#include "cFuelTable.h"
#include "cDrivePlan.h"
#include "cSimulation.h"

void cSimulation::Run()
{
    if (myPlan->myPlan.size() < 2)
        return;
    std::cout << "Simulation Run\n"
              << "time\tdist\tspeed\taccel\tfuel\n";

    // track total fuel consumption
    double consumption = 0;

    // loop over drive plan points
    for (int kdp = 0; kdp < myPlan->size() - 1; kdp++)
    {
        // acceleration needed to reach next drive plan point
        double acceleration = myPlan->acceleration(kdp, kdp+1);

        // loop over time till next drive plan point
        for (
            int t = myPlan->myPlan[0].myTime;
            t <= myPlan->myPlan[1].myTime;
            t++)
        {

            // calculate using the equations of motion
            // s = ut + ½at²
            // v = u + at
            double dist =
                myPlan->myPlan[kdp].mySpeed * t + 0.5 * acceleration * t * t;
            double speed =
                myPlan->myPlan[kdp].mySpeed + acceleration * t;

            // look up the fuel consumption, adding to total
            consumption +=
                myCar->fuelTable()->consumption(
                    speed, acceleration);

            std::cout << t
                      << "\t" << (int)dist
                      << "\t" << speed
                      << "\t" << acceleration
                      << "\t" << consumption
                      << "\n";
        }
    }
}