#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <time.h>
#include <QMessageBox>
#include <QPainter>
#include <QKeyEvent>
#include <QFontDatabase>
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>

const int MATCH_SIZE = 25;
const int MARGIN     = 5 ;
const int AREA_ROW   = 100;
const int AREA_COL   = 100;
const int FONT_SIZE  = 10;


enum GameState
{
    PLAYER1_PLAYER2 = 1,
    PLAYER1_AI = 2,
    AI_AI = 2,
    Game_Over = 4
};

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    void InitGame();
    void StartGame(int number_matches);
    void GameOver();

    void Matches_layout(int number_matches);
    void Create_match(int coordX, int coordY);
    int get_number_matches();
    void set_number_matches(int number_matches);


public:
    explicit Game(QWidget *parent = 0);
    ~Game();

    virtual void paintEvent(QPaintEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    //virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::Game *ui;

private:
    GameState game_state;
    int game_area[AREA_ROW][AREA_COL];

    int score;
    int game_timer;
    int paint_timer;
    int speed_ms;
    int refresh_ms;
    int nb_matches;

    static const int font_size_title = 25;
    static const int font_size = 15;
    static const int font_size_2 = 8;
    const QString font_family = "Joystix";
    void loadUI();
    void startMusicPlayer();
};
#endif // GAME_H
