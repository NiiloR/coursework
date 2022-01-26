#ifndef CITY_HH
#define CITY_HH



#include "../Course/CourseLib/interfaces/icity.hh"
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/interfaces/istop.hh"
#include "../Course/CourseLib/graphics/simplemainwindow.hh"
#include "../Course/CourseLib/core/location.hh"
#include "../Course/CourseLib/actors/nysse.hh"
#include "bettermainwindow.hh"


#include <QTime>
#include <vector>
#include <QPixmap>
#include <QtGlobal>
#include <algorithm>

namespace  StudentSide
{
// Available difficulty levels
enum difficulty {EASY, MEDIUM, HARD};

class City : public Interface::ICity
{
public:
    City();
    ~City();
    void setBackground(QImage &basicbackground, QImage &bigbackground) override;
    void setClock(QTime clock) override;
    void addStop(std::shared_ptr<Interface::IStop> stop) override;
    void startGame() override;
    void addActor(std::shared_ptr<Interface::IActor> newactor) override;
    void removeActor(std::shared_ptr<Interface::IActor> actor) override;
    void actorMoved(std::shared_ptr<Interface::IActor> actor) override;
    void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;    
    bool findActor(std::shared_ptr<Interface::IActor> actor) const override;
    bool isGameOver() const override;

    /**
     * @brief getActors returns all actors of the city
     * @return vector that contains all actors of the city
     */
    std::vector<std::shared_ptr<Interface::IActor>> getActors();

    /**
     * @brief getStops returns all stops of the city
     * @return vector that contains all stops of the city
     */
    std::vector<std::shared_ptr<Interface::IStop>> getStops();

    /**
     * @brief getBusses returns all nysse-actors of the city
     * @return vector that contains all nysse-actors of the city
     */
    std::vector<std::shared_ptr<Interface::IActor>> getBusses();

    /**
     * @brief getPlayer returns player-actor of the city
     * @return Pointer to player-object
     */
    std::shared_ptr<Interface::IActor> getPlayer();

    /**
     * @brief takeStats receives a pointer to a IStatistics for propper notifications about the game
     * @param stats shared pointer to the IStatistics-object
     */
    void takeStats(std::shared_ptr<Interface::IStatistics> stats);

    /**
     * @brief endGame sets city into a gameOver state that is used to stop the game
     */
    void endGame();

private:
    std::vector<std::shared_ptr<Interface::IStop>> stops_;
    std::vector<std::shared_ptr<Interface::IActor>> actors_;
    std::vector<std::shared_ptr<Interface::IActor>> busses_;
    QGraphicsScene *map_;
    QTime time_;
    bool gameOver_;


    std::vector<std::shared_ptr<CourseSide::SimpleActorItem>> actorItems_;
    std::vector< std::shared_ptr <Interface::IActor> > removedActors_;
    std::vector< std::shared_ptr <Interface::IActor> > movedActors_;
    std::shared_ptr<Interface::IActor> player_;
    std::shared_ptr<Interface::IStatistics> stats_;
    
};


}
#endif // CITY_HH
