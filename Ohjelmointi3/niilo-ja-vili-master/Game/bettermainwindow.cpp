#include "bettermainwindow.hh"
#include "ui_bettermainwindow.h"
#include <QtGlobal>
#include <QDebug>
#include <QString>
#include <vector>


namespace StudentSide
{


BetterMainWindow::BetterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BetterMainWindow)
{
    ui->setupUi(this);

    ui->ikkuna->setSceneRect(0,0,width_ - 409, height_ -160);
    ui->ikkuna->setGeometry(10, 50, width_ - 405, height_ - 155);
    ui->centralwidget->setFixedSize(width_, height_);
    ui->buttonLeft->setGeometry(1177, 310, buttonWidth_, buttonHeight_);
    ui->buttonRight->setGeometry(1327, 310, buttonWidth_, buttonHeight_);
    ui->buttonUp->setGeometry(1252, 272,buttonWidth_, buttonHeight_);
    ui->buttonDown->setGeometry(1252, 310, buttonWidth_, buttonHeight_);
    ui->buttonInfect->setGeometry(1252, 372, buttonWidth_, buttonWidth_);
    ui->startButton->setGeometry(1120, 72, buttonWidth_, buttonWidth_);
    ui->buttonQuit->setGeometry(10, 10, buttonWidth_, buttonHeight_);
    ui->infoScreen->setGeometry(1200, 72, 240, 70);
    ui->textBrowser->setGeometry(507, 10, 130, buttonHeight_);
    ui->timeWindow->setGeometry(900, 10, 180, buttonHeight_);

    ui->buttonUp->setDisabled(true);
    ui->buttonDown->setDisabled(true);
    ui->buttonLeft->setDisabled(true);
    ui->buttonRight->setDisabled(true);
    ui->buttonInfect->setDisabled(true);
    ui->startButton->setDisabled(true);



    this->setWindowTitle("Pandemic Tampere");

    ui->textBrowser->setText("Score: 0");
    ui->timeWindow->setText("Time left: ");


    // infoScreen will show this message if dialog window is closed from (X)
    ui->infoScreen->setText("Please restart the game and select a difficulty level.");


    oldScore_ = 0;

    map = new QGraphicsScene(this);
    ui->ikkuna->setScene(map);
    map->setSceneRect(0,0,width_,height_);
    map->setBackgroundBrush(defaultImage_);

    // Timer is used for automatic screen refreshing
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &BetterMainWindow::updateUi);

    // Separate timer is needed for the in game clock
    gameTimer = new QTimer(this);
    QObject::connect(gameTimer, &QTimer::timeout, this, &BetterMainWindow::updateInGameClock);

    // Game lasts for one minute
    time_ = new QTime(0, 1, 0);

    // Difficulty level of the game is chesen via a dialog-window
    Dialog *dialogi = new Dialog;
    QObject::connect(dialogi, &Dialog::setDifficulty, this, &BetterMainWindow::setGameDifficulty);
    dialogi->exec();   

}


BetterMainWindow::~BetterMainWindow()
{
    delete ui;
    delete time_;
}

void BetterMainWindow::addActor(int x, int y, int type, std::shared_ptr<Interface::IActor> actor )
{
    // Player object is created differently to other ui items
    // Dynamic_pointer_cast is used to separate player from other IActor subclasses
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(actor);
    if (player != nullptr) {
        CourseSide::SimpleActorItem* playerI = new CourseSide::SimpleActorItem(x, y, type);
        playerItem_ = std::make_pair(playerI, actor);
        map->addItem(playerI);
        playerI->setScale(2);
        playerI->setX(player->giveLocation().giveX() + 352);
        playerI->setY(552 - player->giveLocation().giveY());

        return;
    }
    // ui-objects are saved with a pointer to their respective object
    CourseSide::SimpleActorItem* nActor = new CourseSide::SimpleActorItem(x, y, type);
    actorsAndItems_.push_back(std::make_pair(nActor, actor));

    // New objects are placed on the map
    map->addItem(nActor);

    // Adjusting actors coordinates to allign with the big map
    nActor->setX(x + 352);
    nActor->setY(552 - y);

    // Stops are distinguished by not having a pointer to their respective object
    if (actor == nullptr) {
        nActor->setScale(0.5);
    }
}


void BetterMainWindow::takeObjects(std::shared_ptr<Interface::ICity> city,
                                   std::shared_ptr<Interface::IActor> player,
                                   std::shared_ptr<Interface::IStatistics> stats,
                                   CourseSide::Logic *logic)
{
    city_ = city;
    // To set the style of the player in game, ui item for player is made separately
    addActor(player->giveLocation().giveX(), player->giveLocation().giveY(), 5500, player);
    statistics_ = stats;
    logic_ = logic;
}


void BetterMainWindow::setGameDifficulty(std::string difficulty)
{
    gameDifficulty_ = difficulty;
    ui->startButton->setDisabled(false);
    ui->infoScreen->setText("Press Start to begin the game!");
    ui->infoScreen->append("Try to infect as many busses as you can before the time runs out!");

}



void BetterMainWindow::on_startButton_clicked()
{
    qDebug() << "Game Started";
    ui->startButton->setDisabled(true);

    //Logic sets up the city for the game to start
    logic_->finalizeGameStart();
    // dynamic pointer cast used to distinguish City object from ICity-pointer
    std::shared_ptr<City> city = std::dynamic_pointer_cast<City>(city_);

    // SimpleActorItems are created for busses and stops
    if (city != nullptr) {

        for ( std::shared_ptr<Interface::IStop> stop : city->getStops()) {
            addActor(stop->getLocation().giveX(), stop->getLocation().giveY(), 100);
        }
        for ( std::shared_ptr<Interface::IActor> nysse : city->getBusses() ) {
            addActor(nysse->giveLocation().giveX(), nysse->giveLocation().giveY(), 2500, nysse);
        }
    }
    else {
        qDebug () << "City not given";
    }

    // Game difficulty is sent to player object to set its speed accordingly
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(playerItem_.second);
    player->setPlayerSpeed(gameDifficulty_);

    // Timer is used to refresh ui and starts when the game launches
    timer->start(tick_);
    gameTimer->start(1000);

    // Movement buttons are abled at the start of the game
    ui->buttonUp->setDisabled(false);
    ui->buttonDown->setDisabled(false);
    ui->buttonLeft->setDisabled(false);
    ui->buttonRight->setDisabled(false);
    ui->buttonInfect->setDisabled(false);
}

void BetterMainWindow::updateUi()
{

    //City is checked for new busses that are then added to ui
    std::shared_ptr<City> city = std::dynamic_pointer_cast<City>(city_);


    for ( std::shared_ptr<Interface::IActor> cityNysse : city->getBusses() ) {
        for ( std::shared_ptr<Interface::IActor> uiNysse : busses_ ) {
            if (uiNysse == cityNysse) {
                break;
            }
        }
        busses_.push_back(cityNysse);
        addActor(cityNysse->giveLocation().giveX(), cityNysse->giveLocation().giveY(), 2500, cityNysse);
    }

    unsigned int i = 0;
    // All the nysse-objects in game are moved to their new coordinates
    while (i < actorsAndItems_.size()) {
            // Only busses are moved. If actorsAndItems.second is nullptr its a stop
            if (actorsAndItems_[i].second != nullptr && !actorsAndItems_[i].second->isRemoved()) {
                actorsAndItems_[i].first->setX(actorsAndItems_[i].second->giveLocation().giveX() + 352);
                actorsAndItems_[i].first->setY(552 - actorsAndItems_[i].second->giveLocation().giveY());
            }
            // Object markes as removed are removed from ui
            else if (actorsAndItems_[i].second != nullptr) {
                    if (actorsAndItems_[i].second->isRemoved()){
                        map->removeItem(actorsAndItems_[i].first);
                        actorsAndItems_.erase(actorsAndItems_.begin() + i);
                    }
            }
            ++i;
        }
    // Player is moved to their new position on the map
    playerItem_.first->setX(playerItem_.second->giveLocation().giveX() + 352);
    playerItem_.first->setY(552 - playerItem_.second->giveLocation().giveY());

    // Current score is updated to the ui
    std::shared_ptr<Statistics> stat = std::dynamic_pointer_cast<Statistics>(statistics_);
    QString score = QString::fromStdString(std::to_string(stat->givePoints()));
    // If score has changed a message telling how many new infections have been made appears

    if (stat->givePoints() > oldScore_) {
        QString scoreIncrease = QString::fromStdString(std::to_string(stat->givePoints() - oldScore_));
        ui->infoScreen->setText(scoreIncrease + " New passengers infected");
        oldScore_ = stat->givePoints();
    }
    ui->textBrowser->setText("Score: " + score);
}

void BetterMainWindow::updateInGameClock()
{
    // In game timer is ticked down if there's time left
    if (time_->minute() != 0 || time_->second() > 0) {
       *time_ = time_->addSecs(-1);
    }
    else {
        qDebug () << "Time's up!";
        endGame();
    }
    // Remaining time is updated on the ui
    QString min = QString::fromStdString(std::to_string(time_->minute()));
    QString sec = QString::fromStdString(std::to_string(time_->second()));
    ui->timeWindow->setText("Time left: " + min + ":" + sec);
}


void BetterMainWindow::on_buttonLeft_clicked()
{         

    std::shared_ptr<Interface::IActor> player = playerItem_.second;
    std::shared_ptr<StudentSide::Player> player_cast = std::dynamic_pointer_cast<StudentSide::Player>(player);

    // Player object is moved
    player_cast->moveLeft();
    Interface::Location ploc = player_cast->giveLocation();

    // Player ui item is moved
    playerItem_.first->setCoord(ploc.giveX() + 352, 552 - ploc.giveY());
}

void BetterMainWindow::on_buttonDown_clicked()
{
    std::shared_ptr<Interface::IActor> player = playerItem_.second;
    std::shared_ptr<StudentSide::Player> player_cast = std::dynamic_pointer_cast<StudentSide::Player>(player);

    player_cast->moveDown();
    Interface::Location ploc = player_cast->giveLocation();
    playerItem_.first->setCoord(ploc.giveX() + 352, 552 - ploc.giveY());
}

void BetterMainWindow::on_buttonRight_clicked()
{
    std::shared_ptr<Interface::IActor> player = playerItem_.second;
    std::shared_ptr<StudentSide::Player> player_cast = std::dynamic_pointer_cast<StudentSide::Player>(player);

    player_cast->moveRight();
    Interface::Location ploc = player_cast->giveLocation();
    playerItem_.first->setCoord(ploc.giveX() + 352, 552 - ploc.giveY());
}

void BetterMainWindow::on_buttonUp_clicked()
{
    std::shared_ptr<Interface::IActor> player = playerItem_.second;
    std::shared_ptr<StudentSide::Player> player_cast = std::dynamic_pointer_cast<StudentSide::Player>(player);

    player_cast->moveUp();
    Interface::Location ploc = player_cast->giveLocation();
    playerItem_.first->setCoord(ploc.giveX() + 352, 552 - ploc.giveY());
}

void BetterMainWindow::on_buttonInfect_clicked()
{    
    std::shared_ptr<Player> player_cast = std::dynamic_pointer_cast<Player>(playerItem_.second);
    player_cast->infectOthersNearby();
}


void BetterMainWindow::endGame()
{
    timer->stop();
    gameTimer->stop();
    std::shared_ptr<City> city = std::dynamic_pointer_cast<City>(city_);
    city->endGame();

    std::shared_ptr<Statistics> stat = std::dynamic_pointer_cast<Statistics>(statistics_);
    QString points = QString::fromStdString(std::to_string(stat->givePoints()));
    ui->infoScreen->setText("Time's up!");
    ui->infoScreen->append("Final score: " + points);

    //only quit-button is available when the game ends
    ui->buttonUp->setDisabled(true);
    ui->buttonDown->setDisabled(true);
    ui->buttonLeft->setDisabled(true);
    ui->buttonRight->setDisabled(true);
    ui->buttonInfect->setDisabled(true);
    ui->startButton->setDisabled(true);
}


void StudentSide::BetterMainWindow::on_buttonQuit_clicked()
{
    delete this;
}

}
