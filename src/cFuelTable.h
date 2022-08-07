#include <vector>
#include <string>

class cFuelTable
{
    public:
    std::vector<double> myTable;
    cFuelTable();

    void add( double speed, double acceleration, double consumption );

    /// calculate fuel consumption
    double consumption( double speed, double acceleration ) const;

    std::string text() const;

    private:
    int index( double speed, double acceleration ) const;
};

cFuelTable * GenerateFuelTableA();
