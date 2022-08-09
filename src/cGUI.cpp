
#include "cGUI.h"

cGUI::cGUI()
    : cStarterGUI(
          "SUMO",
          {50, 50, 1000, 500}),
      wxlbPlans(wex::maker::make<wex::label>(fm)),
      myPlans(wex::maker::make<wex::choice>(fm)),
      wxbnSave(wex::maker::make<wex::button>(fm)),
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
                car.plan(
                       myPlans.selectedIndex())
                    ->text());
        });
    wxbnSave.events().click(
        [&]
        {
            save();
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

    car.add(GenerateDrivePlanCautious());
    car.add(GenerateDrivePlanRaceTheLight());

    car.add(cSpaceTimePoint(100, 7));
}
void cGUI::GUIconstruct()
{
    wxlbPlans.move(10, 10, 70, 30);
    wxlbPlans.text("Drive Plans");
    for (auto &p : car.DrivePlanNameList())
        myPlans.add(p);
    myPlans.move(100, 10, 170, 30);
    wxbnSave.move(280, 10, 60, 30);
    wxbnSave.text("SAVE");
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
void cGUI::save()
{
    static cDrivePlan dp;
    dp.parse( wxmlPlan.text() );
    car.add( &dp );
    myPlans.add(dp.myName);
}
void cGUI::simulate()
{
    car.Run(myPlans.selectedText());

    wxlbResults.text(car.resultText());
    wxlbResults.update();

    std::vector<double> d1;
    for (auto &r : car.results())
    {
        if (wxchPlots.selectedIndex() == 0)
            d1.push_back(r.dist);
        else
            d1.push_back(r.speed);
    }
    trace.set(d1);
    thePlot.update();
}