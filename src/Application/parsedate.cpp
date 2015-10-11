#include "parsedate.h"

ParseDate::ParseDate()
{

}

ParseDate::ParseDate(const QFile& file) : m_status(false)
{
    setFile(file);
}

void ParseDate::setFile(const QFile &file)
{
    //Set file name.
    m_fileName = file.fileName();
}

QDateTime ParseDate::dateTime() const
{
    return m_dateTime;
}

bool ParseDate::parse()
{
    QRegularExpression regExp(QString(R"((\d\d\d\d-\d\d-\d\d).{0,}(\d\d\.\d\d\.\d\d))"));

    //Check if filename is empty.
    if (m_fileName.isEmpty())
    {
        return false;
    }

    //Check if a match is found in the filename using provided regular expression.
    QRegularExpressionMatch match = regExp.match(m_fileName);
    if (match.hasMatch())
    {
        //Retreive date and time.
        auto dateString = match.captured(1);
        auto timeString = match.captured(2);

        //Create and set date and time object from parsed strings.
        auto date = QDate::fromString(dateString, "yyyy-MM-dd");
        auto time = QTime::fromString(timeString, "hh.mm.ss");

        //Set date-time object.
        m_dateTime.setDate(date);
        m_dateTime.setTime(time);

        return true;
    }

    return false;
}
