#ifndef MYPAGE_H
#define MYPAGE_H

#include <QObject>
#include<QtWebEngineWidgets/QtWebEngineWidgets>


class Downloader:public QObject
{
    Q_OBJECT

signals:
    void createMessage(QString);
    void loadDifferenceCounted(int);

private slots:
    void loadDifference(int);
    void beforeDownload(QWebEngineDownloadItem*);
    void showError(QWebEngineDownloadItem::DownloadState);

public:
    Downloader(QObject* Parent = nullptr);
    Downloader(const Downloader& );
    Downloader(QString Url, QString fPathName,QObject* parent=nullptr);
    ~Downloader();    
    Downloader& operator=(const Downloader& Right);
    QWebEnginePage& page();

    void loadAndSave(QString Url, QString fPathName);

private:
QString FilePathName;
QWebEngineProfile Profile;
QWebEnginePage Page;
QWebEngineDownloadItem* Item;
int LoadProgress;
};

#endif // MYPAGE_H
