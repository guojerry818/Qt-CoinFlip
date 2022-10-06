#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"
#include "aboutwindow.h"

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重写paintEvent事件  绘制背景
    void paintEvent(QPaintEvent *event);

    //
    ChooseLevelScene * chooseScene = NULL;
    aboutwindow * about = NULL;

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
