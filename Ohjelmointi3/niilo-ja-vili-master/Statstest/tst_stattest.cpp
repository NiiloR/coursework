#include <QtTest>
#include "../Game/statistics.hh"
//#include "../Game/bettermainwindow.hh"


// add necessary includes here
// Uutta pushausta

class stattest : public QObject
{
    Q_OBJECT

public:
    stattest();
    ~stattest();

private slots:
    void testGivePoints();
    void testAddPoints();

};

stattest::stattest()
{

}

stattest::~stattest()
{

}

void stattest::testGivePoints()
{
    StudentSide::Statistics stats;
    int score = 0;
    QCOMPARE(stats.givePoints(), score);
}

void stattest::testAddPoints()
{
    StudentSide::Statistics stats;
    int points_to_add = 2;
    int current_score = stats.givePoints();
    int new_score = current_score + points_to_add;
    stats.addPoints(points_to_add);
    QCOMPARE(new_score, stats.givePoints());
}


QTEST_APPLESS_MAIN(stattest)

#include "tst_stattest.moc"
