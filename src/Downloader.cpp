#include "Downloader.h"

Downloader::Downloader(QObject* parent)
    :QObject(parent),Profile(this), Page(&Profile,this)
{
    LoadProgress = 0;
    connect(
            this,
            SIGNAL(createMessage(QString)),
            this->parent(),
            SLOT(showMessage(QString))
            );

    connect(
            &this->Page,
            SIGNAL(loadProgress(int)),
            this,
            SLOT(loadDifference(int))
            );

    connect(
            this,
            SIGNAL(loadDifferenceCounted(int)),
            this->parent(),
            SLOT(on_loadProgress(int)),
            Qt::QueuedConnection
            );

    connect(
            &this->Page,
            SIGNAL(loadFinished(bool)),
            this->parent(),
            SLOT(countLoadFinished(bool)),
            Qt::QueuedConnection
            );

}

Downloader::Downloader(QString Url, QString fPathName,QObject* parent):Downloader(parent)
{
    loadAndSave(Url, fPathName);
}
Downloader::Downloader(const Downloader& R)
{
    FilePathName = R.FilePathName;
    Page.setUrl(R.Page.url());
}

Downloader::~Downloader()
{

}

QWebEnginePage& Downloader::page()
{
    return Page;
}

Downloader& Downloader::operator=(const Downloader& Right)
{
    FilePathName = Right.FilePathName;
    Page.setUrl(Right.Page.url());
    return *this;
}

void Downloader::loadDifference(int value)
{
    emit loadDifferenceCounted(value - LoadProgress);
    LoadProgress = value;
}

void Downloader::loadAndSave(QString Url, QString fPathName)
{
    FilePathName = fPathName;
    Page.setUrl(Url);

    connect(
            &Profile,
            SIGNAL(downloadRequested(QWebEngineDownloadItem*)),
            this,
            SLOT(beforeDownload(QWebEngineDownloadItem*))
            );

    Page.download(Url,fPathName);

}

void Downloader::beforeDownload(QWebEngineDownloadItem* DownloadItem)
{
    Item = DownloadItem;
    connect(
            DownloadItem,
            SIGNAL(stateChanged (QWebEngineDownloadItem :: DownloadState)),
            this,
            SLOT(showError(QWebEngineDownloadItem :: DownloadState))
            );
    DownloadItem->accept();
}

void Downloader::showError(QWebEngineDownloadItem::DownloadState State)
{
    if(State == QWebEngineDownloadItem::DownloadState::DownloadInterrupted)
    {
        createMessage("Error while loading\n" + Page.url().toString() + "\n" + Item->interruptReasonString());
    }
}
