#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    this->setFixedSize(QSize(800,600));
    connect(
            this,
            SIGNAL(createMessage(QString)),
            this,
            SLOT(showMessage(QString))
            );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMessage(QString msg)
{
    ui->MsgOut->appendPlainText(msg);
    QMessageBox::information(this, "Message", msg);
}

void MainWindow::on_loadProgress(int progress)
{
    ui->progressBar->setValue(ui->progressBar->value() + progress);
}

void MainWindow::countLoadFinished(bool ok)
{
    if(ok)
    {
        CountDownloaded++;
    }

    if(CountDownloaded == CountHtml)
    {
        ui->progressBar->setValue(ui->progressBar->maximum());
        createMessage("Load finished");
        ui->ButLoad->setDisabled(false);
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

        if(!addLinkedPath())
        {
            return;
        }

        ui->ButLoad->setDisabled(true);
        ui->MsgOut->appendPlainText("Loading main page...");
        QDir MainPath = SavePath;
        MainPath.cdUp();

        CountDownloaded = 0;
        ui->progressBar->reset();
        ui->progressBar->show();

        MassHtml.append(new Downloader(this));
        connect(
                &MassHtml.last()->page(),
                SIGNAL(loadFinished(bool)),
                this,
                SLOT(convertHtml(bool))
                );

        MassHtml.last()->loadAndSave(
                    ui->lineAdress->text(),
                    MainPath.absolutePath() + "/" + SaveFileName + ".html"
                    );

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
            ui->MsgOut->appendPlainText("\n Find links:\n" + strUrl.join("\n") + "\n");

            CountHtml = strUrl.length();
            CountDownloaded=0;
            ui->progressBar->reset();
            ui->progressBar->setMaximum(100 * (CountHtml));
            ui->progressBar->show();

            for(int i = 0; i < strUrl.length(); i++)
            {
                MassHtml.append(new Downloader(this));
                MassHtml.last()->loadAndSave(
                            strUrl[i],
                            SavePath.absolutePath() + "/linked_" + QString::number(i) + ".html");
            }
        });
    }
    else
        ui->codePreview->setText("load failed!");
}

void MainWindow::on_ButSetPath_clicked()
{
    QString pathSave = QFileDialog::getExistingDirectory(
                0,
                QObject::tr("Укажите папку для сохранения файла"),
                QDir::currentPath()
                );

    if( !pathSave.isEmpty() )
    {
        ui->linePath->setText(
                    QDir(QDir::currentPath()).relativeFilePath(pathSave)
                    );
    }

}

QStringList MainWindow::findLinks(QString strHtml)
{
    QStringList strlist(strHtml.split("\n"));
    QRegExp linkMark;

    linkMark.setPatternSyntax(QRegExp::Wildcard);
    linkMark.setPattern("<a href=\"*\"");

    QStringList result = strlist.filter(linkMark);

    result.replaceInStrings(
                QRegExp("*<a href=\"",
                Qt::CaseSensitive,
                QRegExp::Wildcard),
                "");
    result.replaceInStrings(
                QRegExp("\"*",
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

bool MainWindow::checkPath()
{
    qDebug()<<SavePath;
    //создание несуществующего пути
    if(!SavePath.exists())
    {
        if(QMessageBox::question(this,
                                 "Message",
                                 "Do you want to create path?"))
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

bool MainWindow::createPageDirectory()
{
    QString SiteDirName = SaveFileName;
    if(SavePath.exists(SaveFileName))
    {

        int countRepeatedFiles = 2;
        QString EndNumber = "(" + QString::number(2) + ")";
        for(; SavePath.exists(SiteDirName+EndNumber); countRepeatedFiles++)
        {
            EndNumber = "(" + QString::number(countRepeatedFiles) + ")";
        }
        SiteDirName += EndNumber;
        if(QMessageBox::question(this,
                                 "Message",
                                 "The directory of the filename  \"" +SaveFileName+ "\" already exists."
                                 +" Do you want to create directory \"" +SiteDirName+ "\"?")
                == QMessageBox::StandardButton::No)
        {
            createMessage("Fail to create directory of the site. Directory already exists. Please change the name of file.");
            return false;
        }

    }

    if( !SavePath.mkdir(SiteDirName) )
    {
        createMessage("Fail to create directory of the site");
        return false;
    }

    SavePath.cd(SiteDirName);
    return true;
}


bool MainWindow::addLinkedPath()
{
    QString LinkedDirName = SaveFileName + "_linked";

    if( !SavePath.mkdir(LinkedDirName) )
    {
        createMessage("Fail to create \"linked\" directory");
        return false;
    }

    SavePath.cd(LinkedDirName);
    return true;

}
