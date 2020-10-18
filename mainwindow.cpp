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
            parsePath(ui->linePath->text());
            if(!checkPath())return;
            addLinkedPath();
            qDebug()<<SavePath;
            ui->MsgOut->setText("\n Find links:\n"+strUrl.join("\n"));

            CountHtml = strUrl.length()+1;
            CountDownloaded=0;
            ui->progressBar->reset();
            ui->progressBar->setMaximum(100*(CountHtml));
            ui->progressBar->show();

            QDir MainPath = SavePath;
            MainPath.cdUp();
            qDebug()<<MainPath;
            MassHtml.append(new Downloader(ui->lineAdress->text(),MainPath.path()+"/"+SaveFileName+".html",this));
            for(int  i=0;i<strUrl.length();i++)
                MassHtml.append(new Downloader(strUrl[i],SavePath.path()+"/linked_"+QString::number(i)+".html",this));

        });
    }
    else
        ui->codePreview->setText("load failed!");
}

void MainWindow::on_ButSetPath_clicked()
{
    QString pathSave = QFileDialog::getSaveFileName(0,QObject::tr("Укажите папку для сохранения файла"),QDir::homePath(), QObject::tr("Web-страница (*.html);;Все файлы (*.*)"));
    ui->linePath->setText(QDir(QDir::homePath()).relativeFilePath(pathSave));
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

void MainWindow::parsePath(QString StrPath)
{
    QDir Path(StrPath);

    QString NameHtml = Path.dirName();
    qDebug()<<NameHtml.indexOf(QString("."));
    qDebug()<< NameHtml.length();
    NameHtml.remove(NameHtml.indexOf(QString(".")),NameHtml.length()-NameHtml.indexOf(QString(".")));
    qDebug()<<NameHtml;
    if(!Path.cdUp())
    {
        StrPath.remove(QString("\\"+NameHtml+".html"));
        Path.setPath(StrPath);
    }
    qDebug()<<Path.path();


    SavePath = Path;
    SaveFileName = NameHtml;
}


bool MainWindow::checkPath()
{
qDebug()<< SavePath.path();
    //создание несуществующего пути
    if(!SavePath.exists())
    {
        if(QMessageBox::question(this,"Message","Do you want to create path?"))
            if(SavePath.mkpath(SavePath.path()))
                createMessage("Directory created");
            else
            {
                createMessage("Fail to create directory");
                return false;
            }
        else
        {
            createMessage("Directory doesn't exists");
            return false;
        }
    }

return true;
}

QString MainWindow::addLinkedPath()
{
    bool b = 1;
    qDebug()<<SavePath<<SaveFileName;
    if(SavePath.exists(SaveFileName+"_linked"))b*=SavePath.rmdir(SaveFileName+"_linked");
    b*=SavePath.mkdir(SaveFileName+"_linked");
    b*=SavePath.cd(SaveFileName+"_linked");
    if(!b)createMessage("Fail to create \"linked\" directory");
    return SavePath.absolutePath();

}
