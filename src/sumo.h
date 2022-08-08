#pragma once
struct sResult
{
    int time;
    double dist;
    double speed;
    double accel;
    double fuel;

    sResult()
    : time(-1)
    {}
};
#include "cFuelTable.h"
#include "cDrivePlan.h"
#include "cSimulation.h"
