#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <QDesktopServices>
#include <QUrl>

aboutwindow::aboutwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutwindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/Icon.png"));

    connect(ui->blogBtn,&QPushButton::clicked,[=](){
        QDesktopServices::openUrl(QUrl(QLatin1String("https://guojerry818.github.io/about/")));
    });
    connect(ui->closeBtn,&QPushButton::clicked,[=](){
        this->close();
    });
}

aboutwindow::~aboutwindow()
{
    delete ui;
}
