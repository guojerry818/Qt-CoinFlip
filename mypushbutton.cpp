#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}


MyPushButton::MyPushButton(QString normalImg,QString pressImg)  //按钮常态和按下两种状态的图片
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret =  pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败！";
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void MyPushButton::zoom1()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //结束位置
    //animation->setStartValue(QRect(this->x(),this->y()+5,this->width(),this->height()));//如果像这样写，只需要一个zoom1即可实现弹跳操作
    animation->setEndValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::zoom2()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+5,this->width(),this->height()));

    //结束位置
    //animation->setStartValue(QRect(this->x(),this->y()+5,this->width(),this->height()));//如果像这样写，只需要一个zoom1即可实现弹跳操作,但是按钮会闪
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "")    //传入 按下图片 参数非空，执行切换按下图片操作
    {
        QPixmap pix;
        bool ret =  pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败！";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //让父类执行其余操作
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "")    //传入 按下图片 参数非空，执行切换初始图片操作
    {
        QPixmap pix;
        bool ret =  pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败！";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //让父类执行其余操作
    return QPushButton::mouseReleaseEvent(e);
}
