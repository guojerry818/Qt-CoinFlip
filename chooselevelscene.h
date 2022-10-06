#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
#include "aboutwindow.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写绘图事件，实现背景绘制
    void paintEvent(QPaintEvent *event);

    //游戏场景对象指针
    playscene * play = NULL;

    //关于
    aboutwindow * about = NULL;


signals:
    //自定义信号，告诉主场景 执行返回操作
    void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
