
#include "cGUI.h"

cGUI::cGUI()
    : cStarterGUI(
          "SUMO",
          {50, 50, 1000, 500}),
      wxlbPlans(wex::maker::make<wex::label>(fm)),
      myPlans(wex::maker::make<wex::choice>(fm)),
      wxbnEdit(wex::maker::make<wex::button>(fm)),
      wxbnRun(wex::maker::make<wex::button>(fm)),
      wxmlPlan(wex::maker::make<wex::multiline>(fm)),
      wxlbResults(wex::maker::make<wex::label>(fm)),
      wxchPlots(wex::maker::make<wex::choice>(fm)),
      thePlot(wex::maker::make<wex::plot::plot>(fm)),
      trace(thePlot.AddStaticTrace())
{
    simConfig();

    GUIconstruct();

    myPlans.events().select(
        myPlans.id(),
        [&]
        {
            wxmlPlan.text(
                sim.plan(
                       myPlans.selectedIndex())
                    ->text());
        });
    wxbnEdit.events().click(
        [&]
        {
            edit();
        });
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

    sim.add(cSpaceTimePoint(100, 7));
}
void cGUI::GUIconstruct()
{
    wxlbPlans.move(10, 10, 70, 30);
    wxlbPlans.text("Drive Plans");
    for (auto &p : sim.DrivePlanNameList())
        myPlans.add(p);
    myPlans.move(100, 10, 170, 30);
    wxbnEdit.move(280, 10, 60, 30);
    wxbnEdit.text("SAVE");
    wxbnRun.move(350, 10, 60, 30);
    wxbnRun.text("RUN");
    wxmlPlan.move(5, 50, 450, 60);
    wxmlPlan.text("");
    wxlbResults.move(5, 110, 450, 450);
    wxlbResults.fontName("courier");
    wxlbResults.text("");
    wxchPlots.move(600, 10, 100, 30);
    wxchPlots.add("Distance");
    wxchPlots.add("Speed");
    wxchPlots.select(0);
    thePlot.move(500, 50, 450, 450);
    thePlot.XValues(0, 1);
    trace.color(0x0000FF);
}
void cGUI::edit()
{
}
void cGUI::simulate()
{
    sim.Run(myPlans.selectedText());

    wxlbResults.text(sim.resultText());
    wxlbResults.update();

    std::vector<double> d1;
    for (auto &r : sim.results())
    {
        if (wxchPlots.selectedIndex() == 0)
            d1.push_back(r.dist);
        else
            d1.push_back(r.speed);
    }
    trace.set(d1);
    thePlot.update();
}