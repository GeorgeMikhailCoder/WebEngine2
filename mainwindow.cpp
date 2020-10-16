#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();

    connect(this,SIGNAL(createMessage(QString)), this, SLOT(showMessage(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMessage(QString msg)
{
    QMessageBox::information(this,"Message",msg);
}

void MainWindow::on_loadProgress(int progress)
{
    ui->progressBar->setValue(ui->progressBar->value()+progress);
}

void MainWindow::countLoadFinished(bool ok)
{
if(ok)CountDownloaded++;
if(CountDownloaded==CountHtml)
{
    ui->progressBar->setValue(ui->progressBar->maximum());
    createMessage("Load finished");
}
}

void MainWindow::on_ButLoad_clicked()
{
    if(QUrl(ui->lineAdress->text()).isValid())
    {
        connect(ui->preview->page(),SIGNAL(loadFinished(bool)),this,SLOT(convertHtml(bool)));
        ui->preview->page()->load(ui->lineAdress->text());
    }
    // else ... обработка ошибки

}
void MainWindow::convertHtml(bool ok)
{
    if(ok)
    {
        ui->preview->page()->toHtml([this](const QString& strHtml)
        {
            ui->codePreview->setText(strHtml);
            QStringList strUrl = findLinks(strHtml);
            QString path = defPath()+"/";

            CountHtml = strUrl.length()+1;
            CountDownloaded=0;
            ui->progressBar->reset();
            ui->progressBar->setMaximum(100*(CountHtml));
            ui->progressBar->show();

            Downloader* basePage = new Downloader(ui->lineAdress->text(),ui->linePath->text(),this);
            MassHtml.append(*basePage);
            for(int  i=0;i<strUrl.length();i++)
            {
                Downloader* curPage = new Downloader(strUrl[i],path+"linked_"+QString::number(i)+".html",this);
                MassHtml.append(*curPage);
            }

        });
    }
    else
        ui->codePreview->setText("load failed!");
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
    else if(QUrl(res[i]).scheme()=="")
            res[i]=ui->lineAdress->text()+"/"+res[i];

    return res;
}

QString MainWindow::defPath()
{
    QString pathSave = ui->linePath->text();
    QDir path = pathSave;
    QString nameHtml = path.dirName();
    nameHtml.remove(nameHtml.indexOf("."),nameHtml.length()-nameHtml.indexOf("."));
    path.cdUp();
    if(path.exists(nameHtml+"_linked"))path.rmdir(nameHtml+"_linked");
    path.mkdir(nameHtml+"_linked");
    path.cd(nameHtml+"_linked");

    return path.path();

}
