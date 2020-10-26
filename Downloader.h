#ifndef MYPAGE_H
#define MYPAGE_H

#include <QObject>
#include<QtWebEngineWidgets/QtWebEngineWidgets>


class Downloader:QObject
{
    Q_OBJECT
signals:
    void createMessage(QString);
    void loadDifferenceCounted(int);
private slots:
    void loadDifference(int);
    void BeforeDownload(QWebEngineDownloadItem*);
    void ShowError(QWebEngineDownloadItem::DownloadState);

public:
    Downloader(QObject* parent = nullptr);
    Downloader(const Downloader& );
    Downloader(QString Url, QString fPathName,QObject* parent=nullptr);
    ~Downloader();
    Downloader& operator=(const Downloader& Right);
    void setDownloaderParent(QObject*);// можно удалить

    void loadAndSave(QString Url, QString fPathName);

private:

QString FilePathName;
QWebEngineProfile Profile;
QWebEnginePage Page;
QWebEngineDownloadItem* Item;
int LoadProgress;
};

#endif // MYPAGE_H
