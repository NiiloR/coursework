#include "city.hh"
#include <QDebug>



namespace  StudentSide
{


City::City()
{
    gameOver_ = false;
}

City::~City()
{
    
}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    // This function is not used in the current state of the program
    map_->setBackgroundBrush(basicbackground);
    Q_UNUSED(bigbackground);
}

void City::setClock(QTime clock)
{
    time_ = clock;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    for ( std::shared_ptr<Interface::IStop> stop_in_city : stops_) {
        if ( stop_in_city->getName() == stop->getName()) {
            return;
        }
    }
    stops_.push_back(stop);
}

void City::startGame()
{
    qDebug () << "Game has started";
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    std::shared_ptr<CourseSide::Nysse> nysse = std::dynamic_pointer_cast<CourseSide::Nysse>(newactor);
    if ( nysse != nullptr ) {
        busses_.push_back(newactor);
        stats_->newNysse();
        return;
    }

    // Player-actor is saved onto player_
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(newactor);
    if (player != nullptr) {
        player_ = player;
        qDebug () << "Player created";
        return;
    }
    actors_.push_back(newactor);
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    for (auto it = actors_.begin(); it!= actors_.end(); ++it){
        if (*it == actor){
            std::shared_ptr<CourseSide::Nysse> nysse = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
            // Actors state is set to "removed"
            actor->remove();
            actors_.erase(it);
            if (nysse != nullptr){
                // Removing a nysse will provoke a separate message
                stats_->nysseRemoved();
            }
            return;
        }
    }
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    std::shared_ptr<CourseSide::Nysse> nysse = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
    if (nysse == nullptr) {
        return;
    }
    else {
        // Nysses that reaches its final stop will be removed from the game
        std::weak_ptr<CourseSide::Stop> stop = nysse->getFinalStop();
        if ( actor->giveLocation() == stop.lock()->getLocation() ){
            actor->remove();
        }
    }
    // An actor won't be saved twice onto the vector
    for (std::shared_ptr<Interface::IActor> act : movedActors_ ) {
        std::shared_ptr<CourseSide::Nysse> nysse = std::dynamic_pointer_cast<CourseSide::Nysse>(act);
        if ( nysse == actor ) {
            return;
        }
    }
    movedActors_.push_back(actor);
}


void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(actor);
    if (player != nullptr) {
        for (std::shared_ptr<Interface::IActor> act : removedActors_ ) {
            if ( act == actor ) {
                return;
            }
        }
        // Removed actors are saved
        actor->remove();
        removedActors_.push_back(actor);
    }
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor> > nearbyActors;
    for (auto nysse : busses_) {
        if (nysse->giveLocation().isClose(loc, 70)) {
            nearbyActors.push_back(nysse);
        }
    }
    return nearbyActors;
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    for (auto act : actors_) {
        if (act == actor) {
            return true;
        }
    }
    return false;
}

bool City::isGameOver() const
{
    return gameOver_;
}


std::vector<std::shared_ptr<Interface::IActor> > City::getActors()
{
    return actors_;
}

std::vector<std::shared_ptr<Interface::IStop> > City::getStops()
{
    return stops_;
}

std::vector<std::shared_ptr<Interface::IActor> > City::getBusses()
{
    return busses_;
}

std::shared_ptr<Interface::IActor> City::getPlayer()
{
    return player_;
}

void City::takeStats(std::shared_ptr<Interface::IStatistics> stats)
{
    stats_ = stats;
}

void City::endGame()
{
    // Sets the city onto gameOver-state
    gameOver_ = true;
}



}



