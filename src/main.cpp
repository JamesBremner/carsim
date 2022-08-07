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
    cFuelTable ft;
    for (int speed = 0; speed < 100; speed++)
    {
        ft.add(speed, 3, speed);
    }

    // std::cout << ft.text();
    // if( ft.consumption(10,0) != 10 )
    //     throw std::runtime_error(
    //         "failed"    );
    cDrivePlan dp;
    dp.add(0, 0);
    dp.add(10, 30);
    std::cout << dp.text();
    std::cout << "acceleration "
              << dp.myPlan[0].acceleration(dp.myPlan[1])
              << "\n";

    cCar car;
    car.set(ft);
    cSimulation sim;
    sim.set(car);
    sim.set(dp);

    sim.Run();

    cGUI theGUI;
    return 0;
}
