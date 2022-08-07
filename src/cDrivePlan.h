#include <vector>
#include <string>

class cDrivePoint
{
    public:

    int myTime;
    double mySpeed;

    cDrivePoint( int time, double speed )
    : myTime( time ),
    mySpeed( speed )
    {
    }
    double acceleration( const cDrivePoint& other ) const;
};

class cDrivePlan
{
    public:
    std::vector< cDrivePoint > myPlan;

    /** add drive plan point
     * @param[in] time secs
     * @param[in] speed km/hr
     */
    void add( int time, double speed )
    {
        myPlan.push_back({time,speed});
    }

    std::string text() const;
};