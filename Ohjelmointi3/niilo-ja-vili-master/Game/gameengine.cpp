#include "gameengine.hh"
#include <QDebug>




namespace StudentSide
{


GameEngine::GameEngine()
{

}

void GameEngine::createGame()
{       
    std::shared_ptr<Interface::ICity> gamecity(new City);  
    logic.fileConfig();

    //logic sets up the city given to it and runs its funktions
    logic.takeCity(gamecity);
    logic.setTime(12,0);

    std::shared_ptr<Statistics> stats(new Statistics);
    std::shared_ptr<Interface::IActor> player(new Player(gamecity));
    std::shared_ptr<Player> pl = std::dynamic_pointer_cast<Player>(player);

    //player is created in the setup before the game launches
    pl->createPlayerItem();
    pl->takeStats(stats);
    std::shared_ptr<City> cty = std::dynamic_pointer_cast<City>(gamecity);
    cty->takeStats(stats);

    BetterMainWindow* mainwindow( new BetterMainWindow() );

    //Needed objects are passed to betterMainWindow
    mainwindow->takeObjects(gamecity, player, stats, &logic);
    mainwindow->show();

}


}
