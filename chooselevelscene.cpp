#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "playscene.h"
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    //设置固定大小
    setFixedSize(390,570);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("选择关卡");
    //代码实现
    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    //创建菜单
    QMenu * startMenu = bar->addMenu("游戏");
    QMenu * helpMenu = bar->addMenu("帮助");
    //创建退出菜单项和帮助菜单项
    QAction * quitAciton = startMenu->addAction("退出游戏");
    QAction * aboutaction = helpMenu->addAction("关于");

    //点击退出 实现游戏退出
    connect(quitAciton,&QAction::triggered,[=](){
        this->close();
    });

    //点击关于 弹出关于窗口
    connect(aboutaction,&QAction::triggered,[=](){
        about = new aboutwindow;
        about->show();
    });

    //选择关卡按钮音效
    QSound *chooseSound = new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width()-3,this->height()-backBtn->height()-3);

    //实现点击返回效果
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        //qDebug()<<"返回上一页！";
        //发送返回信号 告诉主场景 执行返回；主场景监听chooseLevelScene的返回按钮
        emit this->chooseSceneBack();

    });


    //创建选关按钮
    for( int i = 0 ; i<20 ; i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png",":/res/LevelIcon2.png");
        menuBtn->setParent(this);
        menuBtn->move( 60 + i%4 * 70 , 130 + i/4 * 70);

        connect(menuBtn,&MyPushButton::clicked,[=](){
            //播放选关音效
            chooseSound->play();
            QString str = QString("已选择第%1关!").arg( i+1 );
            qDebug()<<str.toUtf8().data();

            //设置游戏场景初始位置
            play = new playscene(i+1);
            play->setGeometry(this->geometry());

            //进入游戏场景
            play->show();
            this->hide();


            connect(play,&playscene::playSceneBack,[=](){
                QTimer::singleShot(200,this,[=](){
                    this->setGeometry(play->geometry());
                    this->show();    //隐藏游戏场景
                    delete play;   //删除游戏场景
                    play = NULL;
                });
            });
        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        QFont font;
        font.setFamily("等线");
        font.setPointSize(10);
        label->setFont(font);
        label->move( 60 + i%4 * 70 , 130 + i/4 * 70);

        //设置label文字对齐方式 : 水平居中+垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
