#ifndef DRAWINFO_H
#define DRAWINFO_H

#include <QVariantMap>

#include "drawshape.h"

class DrawInfo
{

public:

    QString author;
    DrawShape* shape;

    DrawInfo(const QString& inAuthor,DrawShape* inShape);
    ~DrawInfo();
};

#endif // DRAWINFO_H
