#ifndef SORTFILESTOFOLDERS_H
#define SORTFILESTOFOLDERS_H

#include <QObject>
#include <QDate>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QSharedPointer>
#include "datetofolder.h"
#include "enumhelper.h"
#include "filehelper.h"
#include "parsedate.h"

class SortFilesToFolders : public QObject
{
    Q_OBJECT
public:
    SortFilesToFolders();
    quint32 sort(QDir from, QDir to);

private:
    QSharedPointer<FileHelper> m_fileHelper;
    QSharedPointer<DateToFolder> m_dateToFolder;
    QSharedPointer<ParseDate> m_parseDate;

private slots:
    void onFileHelperError(FileHelper::Error error, QString errorText);
    void onDateToFolderError(DateToFolder::Error error, QString errorText);
    void onParseDateError(ParseDate::Error error, QString errorText);

};

#endif // SORTFILESTOFOLDERS_H
