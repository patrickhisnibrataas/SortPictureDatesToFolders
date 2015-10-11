#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDate>
#include <QFile>
#include "parsedate.h"
#include "datetofolder.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //TODO: Get a string list of all file names in a specific folder.
    //TODO: Parse all file names in string list.
    //TODO: Create folders for all file names.

    //Parse a file's name.
    QFile file(QString("2012-09-30 17.49.23.jpg"));
    ParseDate parseDate(file);
    if (!parseDate.parse())
    {
        qDebug() << "Could not parse";
    }

    //Create directory of file's name.
    QDate date = parseDate.dateTime().date();
    QDir dir("C:/");
    DateToFolder dateToFolder(date, dir);
    if (!dateToFolder.create())
    {
        qDebug() << "Could not create";
    }

    return app.exec();
}
