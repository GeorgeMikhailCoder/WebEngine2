#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButLoad_clicked()
{
    if(QUrl(ui->lineAdress->text()).isValid())
    {
        connect(ui->preview->page(),SIGNAL(loadFinished(bool)),this,SLOT(ConvertHtml(bool)));
        ui->preview->page()->load(ui->lineAdress->text());
    }

    // else ... обработка ошибки

}
void MainWindow::ConvertHtml(bool ok)
{
    if(ok)
    ui->preview->page()->toHtml([this](const QString& strHtml)
    {
        ui->coodePreview->setText(strHtml);
    });
    else
        ui->coodePreview->setText("load failed!");
}

