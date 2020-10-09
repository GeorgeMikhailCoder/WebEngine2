#include "mypage.h"

MyPage::MyPage(QString Url, QString fPathName)
{
    LoadAndSave( Url,  fPathName);
}

MyPage::~MyPage()
{

}

void MyPage::LoadAndSave(QString Url, QString fPathName)
{
filePathName=fPathName;
connect(&page,SIGNAL(loadFinished(bool)),this,SLOT(Save(bool)));
page.load(Url);
QMessageBox::information(nullptr,"Signal","Sended");
}

void MyPage::Save(bool ok)
{
    QMessageBox::information(nullptr,"Signal","Accepted");
if(ok)
{
    page.save(filePathName,QWebEngineDownloadItem::SavePageFormat::CompleteHtmlSaveFormat);
    //this->~MyPage();//возможны проблемы при асинхронном выполнении save от уничтоженного объекта
}

}
