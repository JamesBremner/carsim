#include <iostream>
#include "cFuelTable.h"
#include "cDrivePlan.h"
#include "cSimulation.h"

void cSimulation::Run()
{
    if( myPlan->myPlan.size() < 2 )
        return;
    std::cout << "Simulation Run\n"
        <<"time\tdist\tspeed\taccel\tfuel\n";
    double consumption = 0;
    double acceleration = myPlan->acceleration( 0, 1);
    for( 
        int t  = myPlan->myPlan[0].myTime;
        t <= myPlan->myPlan[1].myTime;
        t++ ) {
            //s = ut + ½at²
            double dist =
                 myPlan->myPlan[0].mySpeed * t
                 + 0.5 * acceleration * t * t;
            double speed = 
                myPlan->myPlan[0].mySpeed
                + acceleration * t;
            consumption +=
                myCar->fuelTable()->consumption(
                    speed, acceleration                );
            
            std::cout << t
                << "\t"<< (int) dist
                << "\t"<< speed
                << "\t"<< acceleration 
                << "\t"<< consumption
                <<"\n";
        }
}