#include "Downloader.h"

Downloader::Downloader(QObject* parent):QObject(parent)
{
    LoadProgress=0;
connect(this,SIGNAL(createMessage(QString)),
        this->parent(), SLOT(showMessage(QString)));
connect(&this->Page,SIGNAL(loadProgress(int)),
        this,SLOT(loadDifference(int)));
connect(this,SIGNAL(loadDifferenceCounted(int)),
        this->parent(), SLOT(on_loadProgress(int)),Qt::QueuedConnection);
connect(&this->Page,SIGNAL(loadFinished(bool)),
        this->parent(),SLOT(countLoadFinished(bool)),Qt::QueuedConnection);

}

Downloader::Downloader(QString Url, QString fPathName,QObject* parent):Downloader(parent)
{
    loadAndSave(Url, fPathName);
}
Downloader::Downloader(const Downloader& R)
{
    FilePathName=R.FilePathName;
    Page.setUrl(R.Page.url());
}

Downloader::~Downloader()
{

}

Downloader& Downloader::operator=(const Downloader& Right)
{
    FilePathName=Right.FilePathName;
    Page.setUrl(Right.Page.url());
    return *this;
}

void Downloader::loadDifference(int value)
{
emit loadDifferenceCounted(value-LoadProgress);
    LoadProgress=value;
}

void Downloader::loadAndSave(QString Url, QString fPathName)
{
    FilePathName=fPathName;
    Page.setUrl(Url);
    connect(&Page,SIGNAL(loadFinished(bool)),this,SLOT(save(bool)));
    Page.load(Url);
    //emit createMessage("Signal sended");
}

void Downloader::save(bool ok)
{
if(!ok){emit createMessage("Error loading file\n"+Page.url().toString());return;}
if(CheckAvialSize())
{
    Page.save(FilePathName,QWebEngineDownloadItem::SavePageFormat::CompleteHtmlSaveFormat);
}
}

bool Downloader::CheckAvialSize()
{
    bool b=true;
    QDir SavePath(FilePathName);
    SavePath.cdUp();

    QStorageInfo Disk(SavePath);
    QString str = Disk.rootPath();
    qint64 SizeAvial = Disk.bytesAvailable();
    qint64 SizePage = sizeof(Page);

    qDebug()<<"Последний сайт:";
    qDebug()<<FilePathName;
    qDebug()<<Disk;
    qDebug()<<SizeAvial;
    qDebug()<<SizePage;



    if(!Disk.isReady()){emit createMessage("Fail to acsess file system\n"+FilePathName);b=false;}
    else if(!Disk.isValid()){emit createMessage("Current root disk isn't valid\n"+FilePathName);b=false;}
    else if(SizePage > SizeAvial) {emit createMessage("Not enough aviable size on hard drive\nMaybe you should try it as an admin\n"+FilePathName);b=false;}
return b;
}
