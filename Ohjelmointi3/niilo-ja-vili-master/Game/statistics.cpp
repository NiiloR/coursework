#include "statistics.hh"
#include <QtDebug>





namespace StudentSide
{


Statistics::Statistics()
{
    //No points in the begining of the game
    score_ = 0;

}

Statistics::~Statistics()
{

}

void Statistics::addPoints(int points_to_add)
{
    score_ += points_to_add;
}

int Statistics::givePoints()
{
    return score_;
}


void Statistics::morePassengers(int num)
{
    qDebug () << num << " passengers added.";
}

void Statistics::nysseRemoved()
{
    qDebug () << "A nysse has been removed from the city";
}

void Statistics::newNysse()
{
    qDebug () << "New nysse has been added to the city.";
}

void Statistics::nysseLeft()
{
    qDebug () << "A nysse has left the game";
}




}
