#include "filehelper.h"

FileHelper::FileHelper()
{

}

QStringList FileHelper::filesInDir(QDir dir)
{
    QStringList files;
    auto dirInfo = dir.entryInfoList();

    for (auto currentItem : dirInfo)
    {
        if (currentItem.isFile())
        {
            files.append(currentItem.fileName());
        }
    }

    return files;
}

bool FileHelper::copy(const QFile &from, const QFile &to)
{
    //Check if file exist.
    if (to.exists())
    {
        emit error(FileHelper::Error::FileAlreadyExist, to.fileName());
        return true;
    }

    //Copy file from 'from' to 'to'.
    auto fromString = from.fileName();
    auto toString = to.fileName();
    if (!QFile::copy(fromString, toString))
    {
        QString errorText = "From: " + fromString + " to: " + toString;
        emit error(FileHelper::Error::CouldNotCopyFile, errorText);
        return false;
    }

    return true;
}
