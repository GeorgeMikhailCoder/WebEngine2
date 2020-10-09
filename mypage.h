#ifndef MYPAGE_H
#define MYPAGE_H

#include <QObject>
#include<QtWebEngineWidgets/QtWebEngineWidgets>


class MyPage:QObject
{
    Q_OBJECT
private slots:
    void Save(bool);

public:
    MyPage(QString Url, QString fPathName);
    ~MyPage();
private:
    void LoadAndSave(QString Url, QString fPathName);

QString filePathName;
QWebEnginePage page;

};

#endif // MYPAGE_H
