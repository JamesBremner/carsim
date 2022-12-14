#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "plot2d.h"
#include "cStarterGUI.h"
#include "sumo.h"


class cGUI : public cStarterGUI
{
public:
    cGUI();

private:
    wex::label &wxlbPlans;
    wex::choice &myPlans;
    wex::button &wxbnSave;
    wex::button &wxbnRun;
    wex::multiline &wxmlPlan;
    wex::label &wxlbResults;
    wex::choice &wxchPlots;
    wex::plot::plot &thePlot;
    wex::plot::trace &trace;

    cCar car;

    // configure simulation
    void simConfig();

    void GUIconstruct();

    void save();
    void simulate();
};
