#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsObject>
#include <QTimer>
#include <QApplication>
#include <QObject>
#include "Player.h"
#include "TowerSmall.h"
#include "Cannon.h"
#include "Bomb.h"
#include "ExitBtn.h"
#include <QPixmap>
#include "BuildSmallTower.h"
#include "BuildCannon.h"
#include "BuildBomb.h"
#include "Weapon.h"
#include "BuildWeapon.h"
#include "Hole.h"
#include "BuildHole.h"
#include "Remover.h"
#include "Lifes.h"
#include "BuildRemover.h"
#include <iostream>
#include "Play.h"
#include "PlayAgain.h"
#include"Score.h"
#include"Game.h"
#include"Zombie.h"
#include"Coins.h"
#include "Tank.h"
#include "TowerSmallBullet.h"
#include "WeaponBullets.h"
#include "TankRocket.h"
#include "CannonBullet.h"
#include "BuildTank.h"
#include "Continue.h"
#include "Pause.h"
QGraphicsPixmapItem* UIButton(int x,int y){
    QPixmap img(":/imgs/blue_button06.png");
        QGraphicsPixmapItem * box = new QGraphicsPixmapItem();
        box->setPixmap(img.scaled(QSize(100,100)));
        box->setPos(x,y);
        return box;

}

QGraphicsPixmapItem* print_wire(int y){
    QPixmap silver_wire(":/imgs/lighting_blue.png");
    QGraphicsPixmapItem * wire = new QGraphicsPixmapItem();
    wire->setPixmap(silver_wire.scaled(QSize(30,30)));
    wire->setPos(950,y);
    return wire;
}

Game::Game(QWidget *parent){
    //Pravimo scenu za crtanje objekata
    scene = new QGraphicsScene();

    //Pravimo igraca
    Player * player = new Player();
    scene->addItem(player);


    //Prikazujemo scenu
    QGraphicsView * view = new QGraphicsView(scene);
    view->show();
    view->setFixedSize(1300,700);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->showFullScreen();
    view->setMouseTracking(true);

    scene->setSceneRect(0,0,1300,700);

    // Pozadina
        QPixmap bk(":/imgs/plants-vs-zombies-background-7.jpg");
        QGraphicsPixmapItem * backround = new QGraphicsPixmapItem();
        backround->setPixmap(bk.scaled(QSize(2000,1000)));
        backround->setPos(-300,-200);
        scene->addItem(backround);
    // Dugme za exit
    ExitBtn * exit = new ExitBtn();
    scene->addItem(exit);

    //Dodaje se linija nakon koje korisnik gubi zivot ukoliko je neprijatelj dodirne
    QGraphicsPixmapItem * wire;
    for(int i=0;i<600;i+=20){
        wire=print_wire(i);
        scene->addItem(wire);
    }

    //Panel za odabir kula (ukras, zato ne pravimo zasebnu klasu)
    QPixmap panel(":/imgs/blue_panel.png");
    QGraphicsPixmapItem * box_panel = new QGraphicsPixmapItem();
    box_panel->setPixmap(panel.scaled(QSize(1500,200)));
    box_panel->setPos(-80,600);
    scene->addItem(box_panel);

    //Tablice sa cenama oruzja
    QPixmap table_pic1(":/imgs/sign3.png");
    QGraphicsPixmapItem * table1 = new QGraphicsPixmapItem();
    table1->setPixmap(table_pic1.scaled(QSize(60,60)));
    table1->setPos(30,545);
    scene->addItem(table1);
    QGraphicsPixmapItem * table2 = new QGraphicsPixmapItem();
    table2->setPixmap(table_pic1.scaled(QSize(60,60)));
    table2->setPos(180,545);
    scene->addItem(table2);
    QPixmap table_pic2(":/imgs/sign6.png");
    QGraphicsPixmapItem * table3 = new QGraphicsPixmapItem();
    table3->setPixmap(table_pic2.scaled(QSize(60,60)));
    table3->setPos(330,545);
    scene->addItem(table3);
    QPixmap table_pic3(":/imgs/sign2.png");
    QGraphicsPixmapItem * table4 = new QGraphicsPixmapItem();
    table4->setPixmap(table_pic3.scaled(QSize(60,60)));
    table4->setPos(480,545);
    scene->addItem(table4);
    QPixmap table_pic4(":/imgs/sign4.png");
    QGraphicsPixmapItem * table5 = new QGraphicsPixmapItem();
    table5->setPixmap(table_pic4.scaled(QSize(60,60)));
    table5->setPos(630,545);
    scene->addItem(table5);
    QPixmap table_pic5(":/imgs/sign5.png");
    QGraphicsPixmapItem * table6 = new QGraphicsPixmapItem();
    table6->setPixmap(table_pic5.scaled(QSize(60,60)));
    table6->setPos(780,545);
    scene->addItem(table6);


    //Tabla na kojoj ce se prikazivati rezultati
    QPixmap table_pic(":/imgs/table.png");
    QGraphicsPixmapItem * table = new QGraphicsPixmapItem();
    table->setPixmap(table_pic.scaled(QSize(150,65)));
    table->setPos(0,5);
    scene->addItem(table);
    // Okviri za kule (ukras, zato ne pravimo zasebnu klasu vec samo fju za iscrtavanje)
    // shift za 150px
    QGraphicsPixmapItem * box ;
    box= UIButton(10,605);
    scene->addItem(box);
    box = UIButton(160,605);
    scene->addItem(box);
    box= UIButton(310,605);
    scene->addItem(box);
    box= UIButton(460,605);
    scene->addItem(box);
    box= UIButton(610,605);
    scene->addItem(box);
    box= UIButton(760,605);
    scene->addItem(box);

    // Dugme za pravljenje malih kula
    BuildSmallTower * st = new BuildSmallTower();
    scene->addItem(st);

    // Dugme za pravljenje topova
    BuildCannon * cannon = new BuildCannon();
    scene->addItem(cannon);

    // Dugme za pravljenje bombe
    BuildBomb * bomb = new BuildBomb();
    scene->addItem(bomb);


    // Dugme za pravljenje rupa
    BuildHole * hole = new BuildHole();
    scene->addItem(hole);

    // Dugme za pravljenje oruzja
    BuildWeapon * weapon = new BuildWeapon();
    scene->addItem(weapon);

    // Dugme za pravljenje brisaca
    BuildRemover * remover = new BuildRemover();
    scene->addItem(remover);

    // Dugme za pravljenje tenka
    BuildTank * tank=new BuildTank();
    scene->addItem(tank);

    // Dodavanje zivota
    lifes = new Lifes();
    scene->addItem(lifes);

    // Dodavanje poena
    score=new Score();
    scene->addItem(score);

    // Dodaje se novcic koji se okrece
    Coins* coins=new Coins();
    scene->addItem(coins);

    //Dodavanje dugmeta za pauziranje
    Pause* p=new Pause();
    scene->addItem(p);

    play = new Play();
    this->scene->addItem(play);


    //Protivnici se stvaraju na nekom intervalu
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(10000);

}

void Game::begin(){

     if(!this->started){
        this->started=true;
        this->scene->removeItem(play);
    }
    this->timer->start(10000);

}

void Game::continue_game(){
    this->pause=false;
    delete c;
}

void Game::paused(){
    this->pause=true;
    c=new Continue();
    this->scene->addItem(c);
}

void Game::reset()
{
   //Vracamo pocetne vrednosti i izgled ekrana i startujemo tajmer za pravljenje novih protivnika

    this->score->score=10;
    this->score->prints();
    this->player->lifes=3;
    this->lost=false;

    this->scene->removeItem(game_end);
    delete game_end;
    this->scene->removeItem(pa);
    delete pa;

    for (auto item : this->scene->items())
        {
            if (typeid (*item) == typeid (Enemy)
               || typeid (*item) == typeid (Zombie)
               || typeid (*item) == typeid (Robot)
               || typeid (*item) == typeid (WomanEnemy)
               || typeid (*item) == typeid (Weapon)
               || typeid (*item) == typeid (Tank)
               || typeid (*item) == typeid (Hole)
               || typeid (*item) == typeid (Bomb)
               || typeid (*item) == typeid (TowerSmall)
               || typeid (*item) == typeid (TankRocket)
               || typeid (*item) == typeid (Cannon)
               || typeid (*item) == typeid (WeaponBullet1)
               || typeid (*item) == typeid (WeaponBullet2)
               || typeid (*item) == typeid (WeaponBullet3)
               || typeid (*item) == typeid (CannonBullet1)
               || typeid (*item) == typeid (CannonBullet2)
               || typeid (*item) == typeid (TowerSmallBullet))
          {
                this->scene->removeItem(item);
                delete item;
            }
        }

    this->timer->start(10000);
}


void Game::game_over(){

    //Kraj igre-zaustavljamo pravljenje novih protivnika
    //ispisujemo poruku o kraju
    this->timer->stop();
    this->lost=true;

    QPixmap end(":/imgs/game_over.png");
    game_end = new QGraphicsPixmapItem();
    game_end->setPixmap(end.scaled(QSize(600,100)));
    game_end->setPos(350,200);
    this->scene->addItem(game_end);

    pa = new PlayAgain();
    this->scene->addItem(pa);

}

