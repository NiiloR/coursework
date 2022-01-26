/*
 * TIE-0220 Kevät 2020
 * GUI-projekti: Tetris
 * Laatinut: Niilo Rannikko
 * Op. nro: 268085
 * Email: niilo.rannikko@tuni.fi
*/


#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "QGraphicsRectItem"
#include <QTimer>
#include <utility>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 50; // x coordinate
    int top_margin = 50; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    // Add more initial settings and connect calls, when needed.
    color_distr = std::uniform_int_distribution<int>(0, colors_.size() - 1);

    // Alussa lauta on tyhjä kaikista laatikoista
    moving_blocks_ = {};
    blocks_on_board_ = {};
    
    connect(&timer_, &QTimer::timeout, this, &MainWindow::tetromino_move_down);

    // Alkutilanteessa vain Start Game -nappula on käytettävissä
    ui->reset_button->setDisabled(true);
    ui->next_shape_button->setDisabled(true);
    ui->drop_button->setDisabled(true);
    ui->move_left_button->setDisabled(true);
    ui->move_right_button->setDisabled(true);
    ui->textBrowser->append("Press Start Game to play");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_button_clicked()
{
    ui->start_button->setDisabled(true);
    ui->textBrowser->clear();
    ui->textBrowser->append("Click Next Shape button to create a new tetromino");
    ui->textBrowser->append("");
    ui->textBrowser->append("Drop the tetromino down by pressin Drop");
    //Start Game -nappi luo ensimmäisen tetrominon ja aloittaa pelin
    if (create_tetromino()) {
        start_timer();
    }
}


void MainWindow::on_reset_button_clicked()
{
    blocks_on_board_.clear();
    moving_blocks_.clear();
    ui->textBrowser->clear();
    ui->start_button->setDisabled(false);
    ui->reset_button->setDisabled(true);
    ui->next_shape_button->setDisabled(true);
    scene_->clear();
    ui->textBrowser->clear();
    ui->textBrowser->append("Press Start Game to play");
}


void MainWindow::on_next_shape_button_clicked()
{
    if (create_tetromino()) {
        start_timer();
    }
}


void MainWindow::on_move_left_button_clicked()
{
    QRectF rect = scene_->sceneRect();
    if (timer_.isActive()) {
        //Tarkistetaan voiko suuntaan liikkua
        for (auto block : moving_blocks_) {
            // Onko uusi sijainti peliruudussa
            if (!(rect.contains(block->x()-SQUARE_SIDE, block->y()))) {
                    return;
            }
            // Onko uudessa sijainnissa jo ennestään laatikko
            for (auto stopped_block : blocks_on_board_) {
                if (stopped_block->x() == block->x() - SQUARE_SIDE &&
                        stopped_block->y() == block->y()) {
                    return;
                }
            }
        }
        for (auto blk : moving_blocks_) {
        blk->moveBy(-SQUARE_SIDE, 0);
        }
        return;
    }
}


void MainWindow::on_move_right_button_clicked()
{
    QRectF rect = scene_->sceneRect();
    if (timer_.isActive()) {
        for (auto block : moving_blocks_) {
            if (!(rect.contains(block->x()+SQUARE_SIDE, block->y()))) {
                    return;
            }
            for (auto stopped_block : blocks_on_board_) {
                if (stopped_block->x() == block->x() + SQUARE_SIDE &&
                        stopped_block->y() == block->y()) {
                    return;
                }
            }
        }
        for (auto blk : moving_blocks_) {
        blk->moveBy(SQUARE_SIDE, 0);
        }
        return;
    }
}


void MainWindow::on_drop_button_clicked()
{
    while (is_moving_ok()) {
        for (auto blk : moving_blocks_) {
        blk->moveBy(0, SQUARE_SIDE);
        }
    }
    // Pudotetut laatikot lisätään pelialueen paikallaan oleviin laatikoihin
    for ( QGraphicsRectItem* stopped_block : moving_blocks_) {
        blocks_on_board_.push_back(stopped_block);
    }
    // Pudotetut laatikot poistetaan liikkuvista laatikoista
    moving_blocks_.clear();
}


bool MainWindow::create_tetromino()
{
    // Muoto valitaan ottamalla satunnaisen muodon laatikoiden aloituskoordinaatit
    // vektoristaan
    std::vector<std::pair<qreal, qreal>> random_shape =
            shape_starting_cordinates.at(distr(randomEng));
    // Muodon väri arvotaan samaan tapaan
    QBrush brush = colors_.at(color_distr(randomEng));
    QPen pen(Qt::black);

    for (std::pair<qreal, qreal> block_coordinates : random_shape) {
        QGraphicsRectItem* block;
        block = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, pen, brush);
        block->moveBy(block_coordinates.first, block_coordinates.second);
        // Tarkistetaan uuden laatikon sijainti. Vain ensimmäiset paikalleen
        // mahtuvat laatikot lisätään pelialueelleen
        for (auto block_on_board : blocks_on_board_) {
            if (block_on_board->x() == block->x() &&
                    block_on_board->y() == block->y()) {
               // Toisen laatikon päälle syntynyt laatikko poistetaan
               delete block;
               // Pelin lopettava ehto täyttyy
               game_over();
               return false;
            }
        }
        moving_blocks_.push_back(block);
    }
    return true;
}


void MainWindow::tetromino_move_down()
{
    if ((is_moving_ok())) {
        // Jos liikkuminen onnistuu, kaikki muodon laatikot siirretään
        // pykälää alemmas
        for (QGraphicsRectItem* block_to_be_moved : moving_blocks_) {
            block_to_be_moved->moveBy(0, SQUARE_SIDE);
        }
    }
     else {
        // Tetrominot, joita ei voi enää laskea, pysähtyvät ja niiden
        // laatikot siirretään pelialueella olevien laatikoiden joukkoon
        for ( QGraphicsRectItem* stopped_block : moving_blocks_) {
            blocks_on_board_.push_back(stopped_block);
        }
        moving_blocks_.clear();
        return;
    }
    return;
}


bool MainWindow::is_moving_ok()
{
    for (QGraphicsRectItem* moving_block : moving_blocks_) {
        if (blocks_on_board_.size() > 0){
            for (QGraphicsRectItem* block : blocks_on_board_) {
                if (block->x() == moving_block->x() &&
                        block->y() == (moving_block->y() + SQUARE_SIDE)) {
                    stop_timer();
                    return false;
                }
            }
        }
        if (moving_block->y() + SQUARE_SIDE >= BORDER_DOWN) {
            stop_timer();
            return false;
        }
    }
    return true;
}


void MainWindow::game_over()
{
    // Suurin osa käyttöliitymän painikkeista poistetaan käytöstä
    ui->textBrowser->clear();
    ui->textBrowser->append("Game Over!");
    ui->textBrowser->append("Start a new game by pressing reset and then start");
    ui->reset_button->setDisabled(false);
    ui->next_shape_button->setDisabled(true);
    ui->start_button->setDisabled(true);
    ui->move_left_button->setDisabled(true);
    ui->move_right_button->setDisabled(true);
    ui->drop_button->setDisabled(true);
    timer_.stop();
    return;
}


void MainWindow::start_timer()
{
   timer_.start(250);
   ui->reset_button->setDisabled(true);
   ui->next_shape_button->setDisabled(true);
   ui->move_left_button->setDisabled(false);
   ui->move_right_button->setDisabled(false);
   ui->drop_button->setDisabled(false);
}


void MainWindow::stop_timer()
{
    // Kello on pysähtyneenä kun pelialueella ei ole liikkuvia tetrominoja,
    // jolloin muotojen liikutteluun liikkuvat painikkeet eivät ole käytössä
    timer_.stop();
    ui->next_shape_button->setDisabled(false);
    ui->reset_button->setDisabled(false);
    ui->move_left_button->setDisabled(true);
    ui->move_right_button->setDisabled(true);
    ui->drop_button->setDisabled(true);
}







