#include "mycoin.h"
#include <QDebug>
//mycoin::mycoin(QWidget *parent) : QWidget(parent)
//{

//}

mycoin::mycoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        QString str = QString("图片%1加载失败！").arg(btnImg);
        qDebug()<<str.toUtf8().data();
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px};");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //定时器对象初始化
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面信号 反转硬币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px};");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断 如果翻完了，将min重置为1
        if(this->min > this->max)
        {
            this->min = 1;
            isAnimation = false; //动画结束
            timer1->stop();
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px};");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断 如果翻完了，将max重置为8
        if(this->min > this->max)
        {
            this->max = 8;
            isAnimation = false; //动画结束
            timer2->stop();
        }
    });
}

void mycoin::mousePressEvent(QMouseEvent *e)
{
    //播放动画时或胜利后，禁用按键操作
   if(this->isAnimation || this->isWin)   return;
    //if(this->isAnimation)   return;
    else  QPushButton::mousePressEvent(e);

}


//改变正反面标志方法
void mycoin::changeFlag()
{
    //若初始为正，则翻反
    if(this->flag)
    {
        //开始正面 翻反面定时器
        timer1->start(30);
        isAnimation = true; //动画开始
        this->flag = false;
    }
    else {
        timer2->start(30);
        isAnimation = true; //动画开始
        this->flag = true;
    }
}
