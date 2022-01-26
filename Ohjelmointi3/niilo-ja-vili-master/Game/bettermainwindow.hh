#ifndef BETTERMAINWINDOW_HH
#define BETTERMAINWINDOW_HH

#include "interfaces/iactor.hh"
#include "graphics/simpleactoritem.hh"
#include "../Course/CourseLib/graphics/simplemainwindow.hh"
#include "statistics.hh"

#include "gameengine.hh"
#include "dialog.hh"
#include "player.h"
#include "statistics.hh"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>

namespace Ui {
class BetterMainWindow;
}



namespace StudentSide {


enum direction {UP, DOWN, LEFT, RIGHT};


/**
 * @brief The BetterMainWindow class takes care of the ui
 */
class BetterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BetterMainWindow(QWidget *parent = 0);
    ~BetterMainWindow();



    /**
     * @brief addActor creates graphic representation for an object and places it on the map
     * @param x is the x-coordinate of the item to be made
     * @param y is the y-coordinate of the item to be made
     * @param type defines the style of the item
     * @param nysse is a pointer to correspondig object
     */
    void addActor(int x, int y, int type = 0, std::shared_ptr<Interface::IActor> actor = nullptr );

    /**
     * @brief takeObjects takes pointers for needed objects
     * @param city is a pointer to the city-object of the game
     * @param player is a pointer to the player character
     * @param stats is a pointer to Statistics-object
     * @param logic is a pointer to logic-object
     */
    void takeObjects(std::shared_ptr<Interface::ICity> city, std::shared_ptr<Interface::IActor> player,
                     std::shared_ptr<Interface::IStatistics> stats,
                     CourseSide::Logic *logic);



public slots:

    /**
     * @brief setGameDifficulty sends the games difficulty to player-object and abels movement buttons
     * @param difficulty is the difficultylevel to be set
     */
    void setGameDifficulty(std::string difficulty);




private slots:

    /**
     * @brief on_startButton_clicked sets up the ui and begins the game
     */
    void on_startButton_clicked();

    /**
     * @brief updateUi Updates the Ui, moves all objects to their new positions and removes unneeded objects
     */
    void updateUi();

    /**
     * @brief on_buttonLeft_pressed moves the player item to left in ui
     */
    void on_buttonLeft_clicked();

    /**
     * @brief on_buttonDown_pressed moves the player item down in ui
     */
    void on_buttonDown_clicked();

    /**
     * @brief on_buttonRight_pressed moves the player item right in ui
     */
    void on_buttonRight_clicked();

    /**
     * @brief on_buttonUp_pressed moves the player item up in ui
     */
    void on_buttonUp_clicked();

    /**
     * @brief on_buttonInfect_clicked checks for close actors and sends them to player-object
     */
    void on_buttonInfect_clicked();

    /**
     * @brief on_buttonQuit_clicked deletes the object and ends the game instantly
     */
    void on_buttonQuit_clicked();

private:

    /**
     * @brief updateInGameClock ticks down the in game clock and signals the game to end when time's up
     */
    void updateInGameClock();

    /**
     * @brief endGame stops the game and shows the final score
     */
    void endGame();


    Ui::BetterMainWindow *ui;
    std::shared_ptr<Interface::ICity> city_;
    CourseSide::Logic* logic_;

    int width_ = 1500;
    int height_ = 750;
    int tick_ = 250;
    int oldScore_;

    //Constants for ui design
    int buttonWidth_ = 70;
    int buttonHeight_ = 32;

    QGraphicsScene *map;
    QTimer *timer;
    QTimer *gameTimer;
    QTime *time_;

    //Ui's simpleActorItems and pointers to their corresponding objects
    std::vector<std::pair<CourseSide::SimpleActorItem*, std::shared_ptr<Interface::IActor>>> actorsAndItems_;

    std::vector<std::shared_ptr<Interface::IActor>> busses_;

    std::string gameDifficulty_;

    std::shared_ptr<Interface::IStatistics> statistics_;

     // SimpleActorItems are stored with a pointer to their respected actor
    std::pair<CourseSide::SimpleActorItem*, std::shared_ptr<Interface::IActor>> playerItem_;

    // Default background for ui
    QImage defaultImage_ = QImage(":/materials/kartta_iso_1095x592");


};

}
#endif // BETTERMAINWINDOW_HH
