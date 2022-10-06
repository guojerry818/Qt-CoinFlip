#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>
#include <QDesktopServices>

namespace Ui {
class aboutwindow;
}

class aboutwindow : public QWidget
{
    Q_OBJECT

public:
    explicit aboutwindow(QWidget *parent = nullptr);
    ~aboutwindow();

private:
    Ui::aboutwindow *ui;
};

#endif // ABOUTWINDOW_H
