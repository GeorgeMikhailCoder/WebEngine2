#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    this->setFixedSize(QSize(800,600));
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
        ui->MsgOut->setText("Loading main page...");



        parsePath(ui->linePath->text());
        if(!checkPath())return;
        addLinkedPath();
        qDebug()<<SavePath;
        QDir MainPath = SavePath;
        MainPath.cdUp();

        ui->progressBar->reset();
        ui->progressBar->show();

        MassHtml.append(new Downloader(this));
        connect(&MassHtml.last()->page(),SIGNAL(loadFinished(bool)),this,SLOT(convertHtml(bool)));
        MassHtml.last()->loadAndSave(ui->lineAdress->text(),MainPath.path()+"/"+SaveFileName+".html");
        ui->preview->setPage(&MassHtml.last()->page());
    }
    else createMessage("Url isn't valid");


}
void MainWindow::convertHtml(bool ok)
{
    ui->progressBar->setValue(100);
    createMessage("Loading main page finished");
    if(ok)
    {
        ui->preview->page()->toHtml([this](const QString& strHtml)
        {
            ui->codePreview->setText(strHtml);
            QStringList strUrl = findLinks(strHtml);
            ui->MsgOut->setText("\n Find links:\n"+strUrl.join("\n"));

            CountHtml = strUrl.length();
            CountDownloaded=0;
            ui->progressBar->reset();
            ui->progressBar->setMaximum(100*(CountHtml));
            ui->progressBar->show();

            for(int  i=0;i<strUrl.length();i++)
            {
                MassHtml.append(new Downloader(this));
                MassHtml.last()->loadAndSave(strUrl[i],SavePath.path()+"/linked_"+QString::number(i)+".html");
            }


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
