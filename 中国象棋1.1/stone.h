#ifndef STONE_H
#define STONE_H

#include <QString>
class Stone
{
public:
    Stone();
    enum TYPE{
        CHE,MA,XIANG,SHI,JIANG,PAO,BING
    } _type;
    bool _red;
    bool _dead;
    int _col;
    int _row;
    int _id;

    void init(int id);
    QString getName();
};

#endif // STONE_H
