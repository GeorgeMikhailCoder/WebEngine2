#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    this->setFixedSize(QSize(800,600));
    connect(this,
            SIGNAL(createMessage(QString)),
            this,
            SLOT(showMessage(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMessage(QString msg)
{
    ui->MsgOut->appendPlainText(msg);
    QMessageBox::information(this,"Message",msg);
}

void MainWindow::on_loadProgress(int progress)
{
    ui->progressBar->setValue(ui->progressBar->value()+progress);
}

void MainWindow::countLoadFinished(bool ok)
{
    if(ok)
    {
        CountDownloaded++;
    }

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
        parsePath();
        if(!checkPath())
        {
            return;
        }

        if(!createPageDirectory())
        {
            return;
        }

        ui->MsgOut->appendPlainText("Loading main page...");
        addLinkedPath();
        QDir MainPath = SavePath;
        MainPath.cdUp();

        ui->progressBar->reset();
        ui->progressBar->show();

        MassHtml.append(new Downloader(this));
        connect(&MassHtml.last()->page(),
                SIGNAL(loadFinished(bool)),
                this,
                SLOT(convertHtml(bool)));

        MassHtml.last()->loadAndSave(ui->lineAdress->text(),
                                     MainPath.absolutePath()
                                        +"/"
                                        +SaveFileName
                                        +".html");

        ui->preview->setPage(&MassHtml.last()->page());
    }
    else
    {
        createMessage("Url isn't valid");
    }


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
            ui->MsgOut->appendPlainText("\n Find links:\n"
                                            +strUrl.join("\n")
                                            +"\n");

            CountHtml = strUrl.length();
            CountDownloaded=0;
            ui->progressBar->reset();
            ui->progressBar->setMaximum(100*(CountHtml));
            ui->progressBar->show();

            for(int  i=0;i<strUrl.length();i++)
            {
                MassHtml.append(new Downloader(this));
                MassHtml.last()->loadAndSave(strUrl[i],
                                             SavePath.absolutePath()
                                                 +"/linked_"
                                                 +QString::number(i)
                                                 +".html");
            }
        });
    }
    else
        ui->codePreview->setText("load failed!");
}

void MainWindow::on_ButSetPath_clicked()
{
    QString pathSave = QFileDialog::getExistingDirectory(0,
                                              QObject::tr("Укажите папку для сохранения файла"),
                                              QDir::currentPath());

    ui->linePath->setText(QDir(QDir::currentPath()).relativeFilePath(pathSave));
}

QStringList MainWindow::findLinks(QString strHtml)
{
    QStringList strlist(strHtml.split("\n"));
    QRegExp linkMark;

    linkMark.setPatternSyntax(QRegExp::Wildcard);
    linkMark.setPattern("<a href=\"*\"");

    QStringList result = strlist.filter(linkMark);

    result.replaceInStrings(QRegExp("*<a href=\"",
                                 Qt::CaseSensitive,
                                 QRegExp::Wildcard),
                         "");
    result.replaceInStrings(QRegExp("\"*",
                                 Qt::CaseSensitive,
                                 QRegExp::Wildcard),
                         "");

    for(int i=0;i<result.length();i++)
    {
        if(!QUrl(result[i]).isValid())
        {
            result.removeAt(i);
        }
        else if(QUrl(result[i]).scheme()=="")
        {
            result[i]=ui->lineAdress->text()+"/"+result[i];
        }
    }

    return result;
}

void MainWindow::parsePath()
{
    SavePath = QDir(ui->linePath->text());
    SaveFileName = ui->lineName->text();
}

bool MainWindow::createPageDirectory()
{
    bool boolResult = SavePath.mkpath(SaveFileName);
    if(!boolResult)
    {
        createMessage("Fail to create directory of the page");
    }
    SavePath.cd(SaveFileName);
    return boolResult;
}

bool MainWindow::checkPath()
{
    //создание несуществующего пути
    if(!SavePath.exists())
    {
        if(QMessageBox::question(this,"Message","Do you want to create path?"))
            if(SavePath.mkpath(SavePath.absolutePath()))
            {
                createMessage("Directory created");
            }
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
    bool boolResult = true;
    if(SavePath.exists(SaveFileName+"_linked"))
    {
        boolResult*=SavePath.rmdir(SaveFileName+"_linked");
    }

    boolResult*=SavePath.mkdir(SaveFileName+"_linked");
    boolResult*=SavePath.cd(SaveFileName+"_linked");

    if(!boolResult)
    {
        createMessage("Fail to create \"linked\" directory");
    }

    return SavePath.absolutePath();

}
