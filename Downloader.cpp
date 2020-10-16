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
//emit createMessage("Signal accepted\n"+Page.url().toString());
if(ok)
{
    Page.save(FilePathName,QWebEngineDownloadItem::SavePageFormat::CompleteHtmlSaveFormat);
}
else
emit createMessage("Error loading file\n"+Page.url().toString());
}
