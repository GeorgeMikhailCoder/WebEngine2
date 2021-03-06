# WebEngine2

Небольшой проект для сохранения веб-страниц со всеми ссылками.
Написан на qt, кроссплатформенный.

## Необходимые компоненты:
1.	Qt5, QWebEngine можно установить с официального сайта Qt по лицензии разработчика: https://www.qt.io/download-open-source
2.	CMake: можно установить с сайта: https://cmake.org/download/

## Сборка:
Запустить CMake: в папке с директорией задать команду:
  сmake CMakeLists.txt

## Пример работы:
При запуске открывается окно:
![](/img/1.png)
1.	В верхней строке необходимо задать адрес скачиваемого сайта.
2.	Во второй строке нужно прописать или указать папку и имя для сохранения файла главной страницы.
3.	После этого нажмите Download, начнётся загрузка.
Как только основная страница будет загружена, справа отобразится предпросмотр и html код. В поле messages output отобразятся все найденные на странице ссылки.
После этого сразу начнётся загрузка всех остальных страниц. Они загружаются в папку с именем главной страницы и постфиксом _linked. Каждая страница имеет название в формате “linked_”+id.
Загрузка завершена

Вид после загрузки основной страницы:
![](/img/2.png)

Структура папок после запуска приложения:

![](/img/3.png)
