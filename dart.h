#ifndef DART_H
#define DART_H
#include <QLabel>

class dart
{
private:
    int point;
    QLabel *label;

public:
    dart(int point, QLabel *label);
    int getDart();
    void setDart(int point);
    void addDart(int point);
    void minusDart(int point);
};

#endif // DART_H
