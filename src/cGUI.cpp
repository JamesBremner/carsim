
#include "cGUI.h"

cGUI::cGUI()
    : cStarterGUI(
          "SUMO",
          {50, 50, 1000, 500}),
      wxlbPlans(wex::maker::make<wex::label>(fm)),
      myPlans(wex::maker::make<wex::choice>(fm)),
      wxbnRun(wex::maker::make<wex::button>(fm)),
      wxlbResults(wex::maker::make<wex::label>(fm)),
      wxchPlots(wex::maker::make<wex::choice>(fm)),
      thePlot(wex::maker::make<wex::plot::plot>(fm)),
      trace(thePlot.AddStaticTrace())
{
    simConfig();

    GUIconstruct();

    wxbnRun.events().click(
        [&]
        {
            simulate();
        });

    show();
    run();
}

void cGUI::simConfig()
{
    car.set(GenerateFuelTableA());

    sim.set(car);

    sim.add(GenerateDrivePlanCautious());
    sim.add(GenerateDrivePlanRaceTheLight());

    sim.add( cSpaceTimePoint( 100,7));
}
void cGUI::GUIconstruct()
{
    wxlbPlans.move(10, 10, 70, 30);
    wxlbPlans.text("Drive Plans");
    for (auto &p : sim.DrivePlanNameList())
        myPlans.add(p);
    myPlans.move(100, 10, 200, 30);
    wxbnRun.move(350, 10, 100, 30);
    wxbnRun.text("RUN");
    wxlbResults.move(5, 50, 450, 450);
    wxlbResults.fontName("courier");
    wxlbResults.text("");
    wxchPlots.move(600, 10, 100, 30);
    wxchPlots.add("Distance");
    wxchPlots.select(0);
    thePlot.move(500, 50, 450, 450);
    thePlot.XValues(0, 1);
    trace.color(0x0000FF);
}
void cGUI::simulate()
{
    sim.Run(myPlans.selectedText());

    wxlbResults.text(sim.resultText());
    wxlbResults.update();

    std::vector<double> d1;
    for (auto &r : sim.results())
    {
        d1.push_back(r.dist);
    }
    trace.set(d1);
    thePlot.update();
}