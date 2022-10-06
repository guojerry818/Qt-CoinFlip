#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
#include "aboutwindow.h"

class playscene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playscene(QWidget *parent = nullptr);
    playscene(int levelNum);

    int levelIndex;//内部成员函数，记录关卡

    //重写paintevent事件
    void paintEvent(QPaintEvent *event);

    //关于
    aboutwindow * about = NULL;


    //二维数组 存储关卡数据
    int gameArray[4][4];

    //二维数组 维护硬币数据
    mycoin * coinBtn[4][4];

    //是否胜利的标志位
    bool isWin=false;


signals:
    //自定义信号，告诉选关场景 执行返回操作
    void playSceneBack();   //不同场景的自定义信号可以同名

public slots:
};

#endif // PLAYSCENE_H
