#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QPainter>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

//playscene::playscene(QWidget *parent) : QMainWindow(parent)
//{

//}

playscene::playscene(int levelNum)
{
    QString str = QString("进入第%1关").arg(levelNum);
    qDebug()<<str.toUtf8().data();
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(390,570);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻硬币游戏");

    //代码实现
    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    //创建菜单
    QMenu * startMenu = bar->addMenu("游戏");
    QMenu * helpmenu = bar->addMenu("帮助");
    //创建退出菜单项
    QAction * quitAciton = startMenu->addAction("退出游戏");
    QAction * aboutAction = helpmenu->addAction("关于");

    //点击退出 实现游戏退出
    connect(quitAciton,&QAction::triggered,[=](){
        this->close();
    });

    //点击关于 弹出关于窗口
    connect(aboutAction,&QAction::triggered,[=](){
        about = new aboutwindow;
        about->show();
    });

    //添加音效
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width()-3,this->height()-backBtn->height()-3);

    QSound *backsound = new QSound(":/res/BackButtonSound.wav");

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        QString str = QString("退出第%1关").arg(levelNum);
        qDebug()<<str.toUtf8().data();
        //发送返回信号 告诉主场景 执行返回；主场景监听chooseLevelScene的返回按钮
        backsound->play();
        emit this->playSceneBack();;

    });

    //显示当前所在关卡
    //设置标签控件
    QLabel * label = new QLabel;
    label->setParent(this);
    //设置字体
    QFont font;
    font.setFamily("优设标题黑");
    font.setPointSize(12);
    QString str1 = QString("当前关卡：%1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(QRect(20, this->height() - 45,120, 50));


    dataConfig config;
    //初始化关卡的二维数组
    for(int i =0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j ++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //显示胜利标识
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

    //显示硬币背景
    for(int i = 0 ; i < 4;i++)
       {
           for(int j = 0 ; j < 4; j++)
           {
              //绘制背景图片
               QPixmap pix = QPixmap (":/res/BoardNode.png");
               QLabel* label = new QLabel;
               label->setGeometry(0,0,pix.width(),pix.height());
               label->setPixmap(QPixmap(pix));
               label->setParent(this);
               label->move(88 + i*(pix.width()+3),200+j*(pix.height()+3));

               //显示硬币
               QString str;
               if (this->gameArray[i][j] == 1)//若数组1 则显示金币
               {
                   str = ":/res/Coin0001.png";

               }
               else
               {
                   str = ":/res/Coin0008.png";
               }

               mycoin * coin = new mycoin(str);
               coin->setParent(label);
               coin->move(2,2);
               //coin->move(88 + i*pix.width(),200+j*pix.height());


               //给硬币属性赋值
               coin->posX = i;
               coin->posY = j;
               coin->flag = gameArray[i][j];

               //将硬币放入 硬币二维数组，便于维护
               coinBtn[i][j] = coin;


               //点击金币，翻转
               if(!this->isWin)
               connect(coin,&mycoin::clicked,[=](){
                   //鼠标按下后，禁止金币翻转
                   for(int i = 0 ; i < 16 ; i ++)
                   {
                       coinBtn[i%4][i/4]->isWin = true;
                   }

                   flipSound->play();

                   coin->changeFlag();
                   this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1:0;//更新数组


                   //翻转周围硬币
                   //延时翻转
                   QTimer::singleShot(200,this,[=](){
                       //当前硬币的右侧 翻转条件
                       if(coin->posX +1 <= 3)
                       {
                           coinBtn[coin->posX+1][coin->posY]->changeFlag();
                           this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1:0;//更新数组
                       }
                       //当前硬币的左侧 翻转条件
                       if(coin->posX -1 >= 0)
                       {
                           coinBtn[coin->posX-1][coin->posY]->changeFlag();
                           this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1:0;//更新数组
                       }
                       //当前硬币的上侧 翻转条件
                       if(coin->posY -1 >= 0)
                       {
                           coinBtn[coin->posX][coin->posY-1]->changeFlag();
                           this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1:0;//更新数组
                       }
                       //当前硬币的下侧 翻转条件
                       if(coin->posY +1 <= 3)
                       {
                           coinBtn[coin->posX][coin->posY+1]->changeFlag();
                           this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1:0;//更新数组
                       }

                       //金币翻转完成，解除禁止
                       for(int i = 0 ; i < 16 ; i ++)
                       {
                           coinBtn[i%4][i/4]->isWin = false;
                       }

                        //判断是否胜利
                       this->isWin = true;
                       for(int i = 0 ; i < 16 ; i ++)
                       {
                           if(coinBtn[i%4][i/4]->flag == false) //只要有一个是反面 则判定未胜利
                           {
                               QString str = QString("当前第%1个硬币为反面，没胜利").arg(i+1);
                               qDebug() << str;
                                this->isWin = false;
                                break;
                           }
                       }

                       if(this->isWin)
                       {
                           //胜利
                           qDebug() << "游戏胜利！";
                           winSound->play();
                           //将所有按钮胜利标志位改为true
                           for(int i = 0 ; i < 16 ; i ++)
                           {
                               coinBtn[i%4][i/4]->isWin = true;
                           }
                           //移动胜利图片 使其显示在屏幕中
                           //创建胜利图片的动画
                           QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                           //设置时间间隔
                           animation->setDuration(800);
                           //设置开始位置
                           animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                           //设置结束位置
                           animation->setEndValue(QRect(winLabel->x(),winLabel->y()+125,winLabel->width(),winLabel->height()));
                           //设置缓和曲线
                           animation->setEasingCurve(QEasingCurve::OutBounce);
                           //执行动画
                           animation->start();
                       }


                   });

                   //判断是否胜利
//                   this->isWin = true;
//                   for(int i = 0 ; i < 4;i++)
//                   {
//                       for(int j = 0 ; j < 4; j++)
//                       {

//                           if( coinBtn[i][j]->flag == false)
//                           {
//                               QString str = QString("当前(%1,%2)硬币为反面，没胜利").arg(i,j);
//                               qDebug() << str;
//                               this->isWin = false;
//                               break;
//                           }
//                       }
//                   }

//                   if(this->isWin)
//                   {
//                       //胜利
//                       qDebug() << "游戏胜利！";

//                   }
//                   }
               });
           }
       }
}

void playscene::paintEvent(QPaintEvent *event)
{
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
