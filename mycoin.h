#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class mycoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit mycoin(QWidget *parent = nullptr);

    //参数：传入金币/银币路径
    mycoin(QString btnImg);


    //金币属性
    int posX;//X坐标位置
    int posY;//Y坐标位置
    int flag;//正反标志位


    //改变标志位的方法
    void changeFlag();

    QTimer *timer1;//
    QTimer *timer2;//反面翻正面定时器
    int min = 1;
    int max = 8;

    //动画执行标志位：防止动画执行过程中被打断
    bool isAnimation = false;

    //重写*按下*状态
    void mousePressEvent(QMouseEvent *e);

    //是否胜利标志位
    bool isWin=false;


signals:

public slots:
};

#endif // MYCOIN_H
