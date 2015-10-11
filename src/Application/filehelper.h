#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStringList>

class FileHelper : public QObject
{
    Q_OBJECT
public:
    enum class Error
    {
        CouldNotCopyFile,
        FileAlreadyExist
    };
    Q_ENUM(Error)

    FileHelper();
    QStringList filesInDir(QDir dir);
    bool copy(const QFile& from, const QFile& to);

signals:
    void error(FileHelper::Error error, QString errorText = QString(""));
};

#endif // FILEHELPER_H
