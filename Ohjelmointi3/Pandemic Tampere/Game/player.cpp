#include "player.h"
#include "QDebug"




namespace StudentSide
{


Player::Player(std::shared_ptr<Interface::ICity> city) :
    city_(city)
{
    // Player starts from center of Tammerkoski
    location_ = Interface::Location(6825010, 3327755 );
    removed_ = false;
}

Player::~Player()
{

}

Interface::Location Player::giveLocation() const
{
    return location_;
}

void Player::move(Interface::Location loc)
{
    location_ = loc;
}

bool Player::isRemoved() const
{
    return removed_;
}

void Player::remove()
{
    removed_ = true;
}

void Player::createPlayerItem()
{
    std::shared_ptr<Interface::IActor> selfPtr(this);
    city_->addActor(selfPtr);
}

void Player::takeStats(std::shared_ptr<Interface::IStatistics> statistics)
{
    stats_ = statistics;
}

void Player::setPlayerSpeed(std::string difficulty)
{
    if ( difficulty == "easy" ) {
        stepsize_ = 20;
        qDebug () << "Difficulty set to easy";
    }
    else if ( difficulty == "medium" ) {
        stepsize_ = 10;
        qDebug () << "Difficulty set to medium";
    }
    else if ( difficulty == "hard" ) {
        stepsize_ = 5;
        qDebug () << "Difficulty set to hard";
    }
    else {
        qDebug () << "Difficulty not chosen properly";
    }
}

void Player::infectOthersNearby()
{
    // Checks for actors nearby and infects them if they are not already infected
    std::vector<std::shared_ptr<Interface::IActor> > nearbyActors = city_->getNearbyActors(location_);
    int new_infections = 0;
    for (std::shared_ptr<Interface::IActor> actor : nearbyActors) {
        bool already_infected = false;
        for (std::shared_ptr<Interface::IActor> infectedActor : infectedActors_) {
            if (actor == infectedActor) {
                already_infected = true;
                break;
            }
        }
        if (!already_infected) {
            infectedActors_.push_back(actor);
            std::shared_ptr<CourseSide::Nysse> nysse = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
            //Infected nysse are removed from the game
            if (nysse != nullptr) {
                new_infections += nysse->getPassengers().size();
                nysse->remove();
            }
            else {
                new_infections += 1;
            }
        }
    }
    std::shared_ptr<Statistics> stats = std::dynamic_pointer_cast<Statistics>(stats_);
    //Infected passengers count for one point per passenger
    stats->addPoints(new_infections);
    qDebug () << new_infections << " passengers infected";

}

void Player::moveUp()
{
    Interface::Location newLocation;
    newLocation.setXY(location_.giveX(),location_.giveY()+stepsize_);
    if (552-newLocation.giveY() >= 0) {
        Player::move(newLocation);
    }
    else {
        newLocation.setXY(newLocation.giveX(),552);
        Player::move(newLocation);
    }

}

void Player::moveDown()
{
    Interface::Location newLocation;
    newLocation.setXY(location_.giveX(),location_.giveY()-stepsize_);
    if ( 552-newLocation.giveY() <= 560) {
        Player::move(newLocation);
    }
    else {
        newLocation.setXY(newLocation.giveX(),552-560);
        Player::move(newLocation);
    }
}

void Player::moveLeft()
{
    Interface::Location newLocation;
    newLocation.setXY(location_.giveX()-stepsize_,location_.giveY());
    if (newLocation.giveX()+352 >= 0) {
        Player::move(newLocation);
    }
    else {
        newLocation.setXY(-352,newLocation.giveY());
        Player::move(newLocation);
    }
}

void Player::moveRight()
{
    Interface::Location newLocation;
    newLocation.setXY(location_.giveX()+stepsize_,location_.giveY());
    if (newLocation.giveX()+352 <= 1062) {
        Player::move(newLocation);
    }
    else {
        newLocation.setXY(1062-352,newLocation.giveY());
        Player::move(newLocation);
    }
}


}


