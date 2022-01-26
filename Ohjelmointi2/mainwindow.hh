/* TIE-0220 Kevät 2020
 * GUI-projekti: Tetris
 * Laatinut: Niilo Rannikko
 * Op. nro: 268085
 * Email: niilo.rannikko@tuni.fi
 *
 * Otsikkotiedosto graafiselle käyttöliittymäoliolle
 * ja siihen liittyvät metodit ja parametrit
 *
*/



#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <random>
#include <vector>
#include <utility>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Uuden pelin aloittava funktio
    void on_start_button_clicked();
    //Alustaa pelilaudan alkutilanteeseen
    void on_reset_button_clicked();
    //Luo pelialueelle seuraavan putoavan tetrominon
    void on_next_shape_button_clicked();
    //Siirtää putoavaa kappaletta vasemmalle
    void on_move_left_button_clicked();
    //Siirtää putoavaa kappaletta oikealle
    void on_move_right_button_clicked();
    //Pudottaa liikkuvan kappaleen mahdollisimman alas
    void on_drop_button_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         VERTICAL,
                         NUMBER_OF_TETROMINOS};
    // From the enum values above, only the last one is needed in this template.
    // Recall from enum type that the value of the first enumerated value is 0,
    // the second is 1, and so on.
    // Therefore the value of the last one is 7 at the moment.
    // Remove those tetromino kinds above that you do not implement,
    // whereupon the value of NUMBER_OF_TETROMINOS changes, too.
    // You can also remove all the other values, if you do not need them,
    // but most probably you need a constant value for NUMBER_OF_TETROMINOS.


    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;



    //Luo uuden satunnaisen muotoisen ja värisen tetrominon ja asettaa sen
    //pelialueen ylälaitaan, jos mahdollista.
    //Palauttaa true, jos tetrominon luominen on mahdollista, muuten false.
    bool create_tetromino();

    //Liikuttaa liikkeessä olevia palikoita pykälän alas, jos mahdollista, muulloin siirtää
    //laatikot paikallaan olevien laatikoiden vektoriin
    void tetromino_move_down();

    //Kertoo voiko liikkuvia laatikoita siirtää pykälän alas päin
    bool is_moving_ok();

    //Päättää pelin
    void game_over();

    //Käynnistää laatikoiden putoamiseen sidotun kellon ja poistaa uuden palikan
    //luomisnäppäimen
    void start_timer();

    //Pysäyttää kellon ja aktivoi uuden palikan luomisnäppäimen
    void stop_timer();

    // Satunnaisen värin valitsemiseksi
    std::uniform_int_distribution<int> color_distr;
    QTimer timer_;

    //Mahdolliset eri värit tetrominoille
    const std::vector<QBrush> colors_ =
    {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::magenta, Qt::cyan};

    //Pelissä liikkeesä olevat laatikot
    std::vector<QGraphicsRectItem*> moving_blocks_;
    //Pelialueella olevat pysähtyneet laatikot
    std::vector<QGraphicsRectItem*> blocks_on_board_;

    // Vektori eri muotojen palikoiden aloituskoordinaateille.
    // Yksi sisävektori sisältää muodon neljän palikan (x,y) koordinaatit
    // pareittain järjestyksessä vasemmalta oikealle ja ylhäältä alas
    const std::vector<std::vector<std::pair<qreal, qreal>>> shape_starting_cordinates = {
    { {80, 0},  {100, 0},  {120, 0},  {140, 0}  }, //Horizonal
    { {100, 0}, {100, 20}, {120, 20}, {140, 20} }, //Left corner
    { {140, 0}, {100, 20}, {120, 20}, {140, 20} }, //Right corner
    { {100, 0}, {120, 0},  {100, 20}, {120, 20} }, //Square
    { {120, 0}, {100, 20}, {120, 20}, {100, 40} }, //Step up right
    { {100, 0}, {80, 20},  {100, 20}, {120, 20} }, //Pyramid
    { {100, 0}, {100, 20}, {120, 20}, {120, 40} }, //Step up left
    { {120, 0}, {120, 20}, {120, 40}, {120, 60} }  //Vertical
    };

    };
    
    

#endif // MAINWINDOW_HH
