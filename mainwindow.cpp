#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this,SIGNAL(convertFinished(QString)),this,SLOT(when_convertFinished(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ButLoad_clicked()
{
      connect(ui->preview->page(),SIGNAL(loadFinished(bool)),this,SLOT(when_loadFinished(bool)));
      ui->preview->page()->load(ui->lineAdress->text());
}
void MainWindow::when_convertFinished(QString str)
{
    ui->coodePreview->setText(str);
}
void MainWindow::when_loadFinished(bool ok)
{
    if(ok)
    ui->preview->page()->toHtml([this](const QString& data)
    {
          emit this->when_convertFinished(data);
    });
    else
        ui->coodePreview->setText("load failed!");
}
