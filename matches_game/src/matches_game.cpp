#include "matches_game.h"
#include "ui_matches_game.h"

Game::Game(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    startMusicPlayer();
    InitGame();
    StartGame(get_number_matches());
}

Game::~Game()
{
    delete ui;
}

void Game::startMusicPlayer(){
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/src/audio/theme.mp3"));
    player->setVolume(50);
    player->play();
}


int match[2][2]=
{
    {0,1},
    {0,1}
};

void Game::InitGame()
{
    for(int i=0;i<AREA_ROW;i++){
        for(int j=0;j<AREA_COL;j++){
            game_area[i][j]=0;
        }
    }
    set_number_matches(15);
    speed_ms=800;
    refresh_ms=3;
    srand(time(0));
    score=0;
    loadUI();
}

void Game::StartGame(int number_matches)
{
    game_state = PLAYER1_PLAYER2;

    game_timer=startTimer(speed_ms);
    
    paint_timer=startTimer(refresh_ms);
    
    Matches_layout(number_matches);

}

void Game::GameOver()
{
    game_state = Game_Over;

    killTimer(game_timer);
    killTimer(paint_timer);
    QMessageBox::information(this,"Failed","Game over");
}


void Game::loadUI(){

}

void Game::Create_match(int coordX, int coordY)
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap("path/to/image.png"));
    //scene.addItem(item);
    item->setPos(coordX, coordY);
}

void Game::Matches_layout(int number_matches)
{

}

int Game::get_number_matches()
{
return nb_matches;
}

void Game::set_number_matches(int number_matches)
{
nb_matches = number_matches;
}

void Game::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(MARGIN,MARGIN,AREA_COL*MATCH_SIZE,AREA_ROW*MATCH_SIZE);
    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));

    QFontDatabase::addApplicationFont(":/src/font/pixel.ttf");
    painter.setPen(Qt::black);
    painter.setFont(QFont(font_family, font_size));
    painter.drawText(QRect(MARGIN*3+AREA_COL*MATCH_SIZE,MARGIN*2+4*MATCH_SIZE,MATCH_SIZE*4,MATCH_SIZE*4),
                     Qt::AlignCenter,
                     "SCORE: "+ QString::number(score));
    for(int i=0;i<AREA_ROW;i++)
        for(int j=0;j<AREA_COL;j++)
        {
            if(game_area[i][j]==1)
            {
                painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawRect(j*MATCH_SIZE+MARGIN,i*MATCH_SIZE+MARGIN,MATCH_SIZE,MATCH_SIZE);
            }
            else if(game_area[i][j]==2)
            {
                painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                painter.drawRect(j*MATCH_SIZE+MARGIN,i*MATCH_SIZE+MARGIN,MATCH_SIZE,MATCH_SIZE);
            }
        }
}

void Game::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==game_timer && game_state != Game_Over){
    }
    if(event->timerId()==paint_timer){
        update();
    }
}

