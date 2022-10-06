#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QSound>   //multimedia下的头文件

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景
    //设置固定大小
    setFixedSize(390,570);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("主场景");
    //实现退出按钮
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    connect(ui->actionabout,&QAction::triggered,[=](){
        about = new aboutwindow;
        about->show();
    });

    //准备开始按钮的音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);


    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5 , this->height() *0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮信号 放在new选关界面后 时刻监听
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        QTimer::singleShot(200,this,[=](){
            this->setGeometry(chooseScene->geometry());
            chooseScene->hide();    //隐藏选关场景
            this->show();   //显示当前场景
        });
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        qDebug() << "开始游戏！";

        //播放开始音效
        startSound->play();;
        //startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5 , this->height() *0.5-3);
        startBtn->zoom1();    //注释掉zoom1似乎也可用？
        startBtn->zoom2();
        //startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5 , this->height() *0.5);

        //延时进入关卡选择
        QTimer::singleShot(200,this,[=](){
            //设置choosescene场景位置
            chooseScene->setGeometry(this->geometry());

            //自身隐藏
            this->hide();
            //进入关卡选择场景
            chooseScene->show();

//            //监听选关界面的返回按钮
//            connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
//                this->setGeometry(this->geometry());
//                this->show();
//            })
        });




    });

}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    //pix.load(":/res/Title.png");
    //图片缩放
    pix.scaled(pix.width() * 0.4,pix.height() * 0.4);
    //绘制标题
    //painter.drawPixmap(0,30,pix);

}

MainScene::~MainScene()
{
    delete ui;
}
