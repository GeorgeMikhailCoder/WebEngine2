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
    void save(bool);
    void loadDifference(int);

public:
    Downloader(QObject* parent = nullptr);
    Downloader(const Downloader& );
    Downloader(QString Url, QString fPathName,QObject* parent=nullptr);
    ~Downloader();
    Downloader& operator=(const Downloader& Right);

    void loadAndSave(QString Url, QString fPathName);
private:


QString FilePathName;
QWebEnginePage Page;
int LoadProgress;
};

#endif // MYPAGE_H
