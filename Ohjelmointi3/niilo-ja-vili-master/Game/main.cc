#include <QApplication>
#include "../Course/CourseLib/graphics/simplemainwindow.hh"
#include "gameengine.hh"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    StudentSide::GameEngine *engine = new StudentSide::GameEngine();
    engine->createGame();
    return a.exec();
}

// Testataan commitin ajoo remoteen
//sama t. Niilo
