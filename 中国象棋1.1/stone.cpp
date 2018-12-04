#include "stone.h"

Stone::Stone()
{

}

void Stone::init(int id)
{
    struct{
        int row,col;
        TYPE type;
    } pos[16]={
    {0,0,TYPE::CHE},
    {0,1,TYPE::MA},
    {0,2,TYPE::XIANG},
    {0,3,TYPE::SHI},
    {0,4,TYPE::JIANG},
    {0,5,TYPE::SHI},
    {0,6,TYPE::XIANG},
    {0,7,TYPE::MA},
    {0,8,TYPE::CHE},

    {2,1,TYPE::PAO},
    {2,7,TYPE::PAO},
    {3,0,TYPE::BING},
    {3,2,TYPE::BING},
    {3,4,TYPE::BING},
    {3,6,TYPE::BING},
    {3,8,TYPE::BING}
};
    if(id>=16){

        this->_col=8-pos[id-16].col;
        this->_row=9-pos[id-16].row;
        this->_type=pos[id-16].type;
    }else
    {
        this->_col=pos[id].col;
        this->_row=pos[id].row;
        this->_type=pos[id].type;
    }

    this->_dead=false;
    this->_red=id>=16;

}

QString Stone::getName()
{
    switch (this->_type)
    {
        case CHE:

            return "车";
        case MA:

            return "马";
        case XIANG:

            return "象";
        case SHI:

            return "士";
        case JIANG:

            return "将";
        case PAO:

            return "炮";
        case BING:

            return "兵";
    }
    return "错误";

}
