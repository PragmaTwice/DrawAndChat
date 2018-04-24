#include "drawinfo.h"

DrawInfo::DrawInfo(const QString &inAuthor, DrawShape *inShape) :
    author(inAuthor),
    shape(inShape)
{
}

DrawInfo::~DrawInfo()
{
}
