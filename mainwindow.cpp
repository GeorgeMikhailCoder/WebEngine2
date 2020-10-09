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
    {
        ui->preview->page()->toHtml([this](const QString& strHtml)
        {
            ui->coodePreview->setText(strHtml);
            QStringList strUrl = findLinks(strHtml);
            new MyPage(ui->lineAdress->text(), ui->linePath->text()); //утечка памяти!
            for(int  i=0;i<strUrl.length();i++)
            {
                //MyPage(strUrl[i],)
            }

        });
    }
    else
        ui->coodePreview->setText("load failed!");
}

void MainWindow::SaveHtml(bool ok)
{
    if(ok)
    {

        ui->MsgOut->setText("!!!");
    }
    else
        ui->MsgOut->setText("Failed saving html by link");
}

void MainWindow::on_ButSetPath_clicked()
{
    QString pathSave = QFileDialog::getSaveFileName(0,QObject::tr("Укажите папку для сохранения файла"),QDir::homePath(), QObject::tr("Web-страница (*.html);;Все файлы (*.*)"));
    ui->linePath->setText(pathSave);
}

QStringList MainWindow::findLinks(QString strHtml)
{
    QStringList strlist(strHtml.split("\n"));
    QRegExp linkMark;
    linkMark.setPatternSyntax(QRegExp::Wildcard);
    linkMark.setPattern("<a href=\"*\"");
    QStringList res = strlist.filter(linkMark);
    res.replaceInStrings(QRegExp("*<a href=\"",Qt::CaseSensitive,QRegExp::Wildcard),"");
    res.replaceInStrings(QRegExp("\"*",Qt::CaseSensitive,QRegExp::Wildcard),"");

    for(int i=0;i<res.length();i++)
        if(!QUrl(res[i]).isValid())
            res.removeAt(i);
    return res;
}
