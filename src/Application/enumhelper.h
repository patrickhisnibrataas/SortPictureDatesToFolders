#ifndef ENUMHELPER_H
#define ENUMHELPER_H

#include <QDebug>
#include <QMetaEnum>
#include <QString>
#include <QStringList>

template <class T>
class EnumHelper : public QObject
{
public:
    EnumHelper() {}

    //Convert enum of type T to string.
    static QString toString(T enumerator)
    {
        //Get meta enum data from enum T.
        auto metaEnum = QMetaEnum::fromType<T>();

        //Get string corresponding to provided enum value.
        auto enumString = metaEnum.key(static_cast<int>(enumerator));

        //Return the string corresponinding to the enum value.
        return enumString;
    }

    //Convert string name to enum of type T if name is found in T.
    static T toEnum(QString name, bool *ok = 0)
    {
        //Set default status of variable ok if provided.
        if (ok != nullptr)
        {
            *ok = true;
        }

        //Get meta enum data from enum T.
        auto metaEnum = QMetaEnum::fromType<T>();

        //Find index in enum is name is found in enum.
        int enumerator = metaEnum.keyToValue(name.toStdString().c_str());

        //Check if enumerator for string name was found.
        if (enumerator == -1)
        {
            qDebug() << staticMetaObject.className() << ": Could not convert " << name << " to enum";

            //Set status of variable ok to false as the enumerator for string name was not found.
            if (ok != nullptr)
            {
                *ok = false;
            }
        }

        //Return enumerator value.
        return static_cast<T>(enumerator);
    }

    //Get length of enum.
    static int length()
    {
        auto metaEnum = QMetaEnum::fromType<T>();
        return metaEnum.keyCount();
    }

    //Get all enums as a string list.
    static QStringList toStringList()
    {
        QStringList stringList;

        //Get length of enum and iterate over them.
        auto length = EnumHelper<T>::length();
        for (auto i = 0; i < length; i++)
        {
            //Get string for current enum index.
            auto enumString = EnumHelper<T>::toString(static_cast<T>(i));

            //Append enum string to the string list.
            stringList.append(enumString);
        }

        //Return the string list.
        return stringList;
    }
};

#endif // ENUMHELPER_H
