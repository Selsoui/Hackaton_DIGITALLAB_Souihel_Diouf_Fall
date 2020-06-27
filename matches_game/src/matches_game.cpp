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
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/src/audio/theme.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    
    QMediaPlayer* player = new QMediaPlayer;
    player->setPlaylist(playlist);
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

QGraphicsPixmapItem* Game::Create_match(int coordX, int coordY)
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap("/src/img/allumette.png"));
    item->setPos(coordX, coordY);
    return item;
}

void Game::Delete_match(int coordX, int coordY)
{

}

std::vector<QGraphicsPixmapItem*> Game::Matches_layout(int number_matches)
{
    std::vector<QGraphicsPixmapItem*> image_items;
    int i = 0, k=0, l=0;
    while (i < number_matches)
        {
        image_items.push_back(Create_match(AREA_ROW/(number_matches/2)+k,AREA_COL/2+l));
        i++;
        l = MATCH_SIZE*floor(-1-sqrt(1+8*i));
        k = pow(-1,i)*l*MATCH_SIZE;
        }
    return image_items;

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
    QGraphicsScene scene(this);
    std::vector<QGraphicsPixmapItem*> matches = Matches_layout(get_number_matches());
    
    for (int i = 0; i< matches.size(); i++)
        {
        scene.addItem(matches[i]);
        }
    
    QGraphicsView view(&scene);
    view.show();
        
    
}

void Game::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==game_timer && game_state != Game_Over){
    
    }
    if(event->timerId()==paint_timer){
        update();
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{

}

