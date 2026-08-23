#ifndef STATISTICS_HH
#define STATISTICS_HH


#include "../Course/CourseLib/interfaces/istatistics.hh"
#include "bettermainwindow.hh"
#include "city.hh"



namespace StudentSide {


class Statistics : public Interface::IStatistics
{
public:
    Statistics();

    virtual ~Statistics();

    /**
     * @brief addPoints takes players new points and adds them to current points
     * @param points_to_add are players new points
     */
    void addPoints(int points_to_add);

    /**
     * @brief givePoints gives players score
     * @return players points
     */
    int givePoints();

    void morePassengers(int num) override;

    void nysseRemoved() override;

    void newNysse() override;

    void nysseLeft() override;

private:

    // Players score
    int score_;

};

}

#endif // STATISTICS_HH
