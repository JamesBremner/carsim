#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"
#include "cFuelTable.h"
#include "cDrivePlan.h"
#include "cSimulation.h"

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "SUMO",
              {50, 50, 1000, 500}),
          lb(wex::maker::make<wex::label>(fm))
    {
        lb.move(50, 50, 100, 30);
        lb.text("Hello World");

        show();
        run();
    }

private:
    wex::label &lb;
};

main()
{
    // configure simulation
    cCar car;
    car.set( GenerateFuelTableA() );
    cSimulation sim;
    sim.set(car);

    sim.add(GenerateDrivePlanCautious());
    sim.add(GenerateDrivePlanRaceTheLight());

    // run simulations
    sim.Run( "Cautious");

    sim.Run( "Race the Light");

    cGUI theGUI;
    return 0;
}
