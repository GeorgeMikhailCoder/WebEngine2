#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this,SIGNAL(convertFinished),this,SLOT(when_convertFinished));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ButLoad_clicked()
{
      ui->preview->page()->load(ui->lineAdress->text());
      ui->preview->page()->toHtml([this](const QString& data){
          emit this->when_convertFinished(data);
      });
}
void MainWindow::when_convertFinished(QString str)
{
    ui->coodePreview->setText(str);
}
