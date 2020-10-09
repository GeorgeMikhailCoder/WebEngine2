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
page.setUrl(Url);
connect(&page,SIGNAL(loadFinished(bool)),this,SLOT(Save(bool)));
page.load(Url);
QMessageBox::information(nullptr,"Signal","Sended");
}

void MyPage::Save(bool ok)
{
QMessageBox::information(nullptr,"Signal","Accepted\n"+page.url().toString());
if(ok)
{

    page.save(filePathName,QWebEngineDownloadItem::SavePageFormat::CompleteHtmlSaveFormat);
    //this->~MyPage();//возможны проблемы при асинхронном выполнении save от уничтоженного объекта
}
else
QMessageBox::information(nullptr,"Error","Error loading file\n"+page.url().toString());
}
