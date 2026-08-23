#ifndef PLAYER_H
#define PLAYER_H

#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/interfaces/istop.hh"
#include "../Course/CourseLib/core/location.hh"
#include "../Game/city.hh"

#include <iostream>
#include <QTimer>

namespace StudentSide {

class Player : public Interface::IActor
{

public:
    Player(std::shared_ptr<Interface::ICity> city);
    ~Player();

    Interface::Location giveLocation() const override;
    void move(Interface::Location loc) override;
    bool isRemoved() const override;
    void remove() override;

    /**
     * @brief createPlayerItem creates graphic representation for player via city
     */
    void createPlayerItem();

    /**
     * @brief takeStats takes the Statistics object for scorekeeping
     * @param statistics is pointer to the Statistics object
     */
    void takeStats(std::shared_ptr<Interface::IStatistics> statistics);

    /**
     * @brief setPlayerSpeed changes the players speed to match difficulty level
     * @param difficulty is the wanted level of difficulty
     */
    void setPlayerSpeed(std::string difficulty);

    /**
     * @brief infectOthersNearby checs if any actors are close by and infects them
     */
    void infectOthersNearby();

    /**
     * @brief moveUp moves the player up
     */
    void moveUp();

    /**
     * @brief moveDown moves the player down
     */
    void moveDown();

    /**
     * @brief moveLeft moves the player left
     */
    void moveLeft();

    /**
     * @brief moveRight moves the player right
     */
    void moveRight();

private:

    //Players position on the map
    Interface::Location location_;

    std::vector<std::shared_ptr<Interface::IActor> > infectedActors_;

    //Players level of speed
    int stepsize_;
    bool removed_;

    std::shared_ptr<Interface::ICity> city_;
    std::shared_ptr<Interface::IStatistics> stats_;

};

}


#endif // PLAYER_H
