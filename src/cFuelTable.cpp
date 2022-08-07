#include <stdexcept>
#include <sstream>
#include "cFuelTable.h"

cFuelTable::cFuelTable()
: myTable( 1900 )
{

}
void cFuelTable::add(
    double speed,
     double acceleration
     , double consumption)
{
    myTable[index(speed,acceleration)] = consumption;
}

double cFuelTable::consumption(
    double speed,
     double acceleration) const
{
    return myTable[index(speed,acceleration)];
}

std::string cFuelTable::text() const
{
    std::stringstream ss;
    for( int krow = 0; krow < 100; krow++ ) {
        for( int kcol = 0; kcol < 19; kcol++ ) {
            int index = (krow * 19 ) + kcol;
            ss << myTable[index] << " ";
        }
        ss << "\n";
    }
    return ss.str();
}

int cFuelTable::index( double speed, double acceleration ) const
{
        if (speed < 0 || speed > 99)
        throw std::runtime_error(
            "cFuelTable bad speed");
    if (-9 > acceleration || acceleration > 9)
        throw std::runtime_error(
            "cFuelTable bad acceleration");
    return ((int)speed * 19 ) + (int)acceleration + 9;
}