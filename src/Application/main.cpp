#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QString>
#include "sortfilestofolders.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    SortFilesToFolders sortFilesToFolders;
    quint32 copiedFiles = sortFilesToFolders.sort(QDir("C:/lol"), QDir("L:/lol"));

    qDebug() << "Files copied: " + QString::number(copiedFiles);

    return app.exec();
}
