#include "city.hh"
#include "bettermainwindow.hh"
#include "statistics.hh"
#include "../Course/CourseLib/core/logic.hh"
#include "player.h"


#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

namespace StudentSide {


class GameEngine
{
public:
    GameEngine();

    /**
     * @brief createGame creates propper objects and initiates the game
     */
    void createGame();

private:

    CourseSide::Logic logic;

};
}

#endif // GAMEENGINE_HH
