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
    MyPage(){};
    MyPage(const MyPage& );
    MyPage(QString Url, QString fPathName);
    ~MyPage();
    MyPage& operator=(const MyPage& Right);

    void LoadAndSave(QString Url, QString fPathName);
private:


QString filePathName;
QWebEnginePage page;

};

#endif // MYPAGE_H
