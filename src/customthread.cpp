#include "customthread.h"

#include<iostream>

// Thread One
void CustomThreadOne::stepFunction()
{
    std::cerr << '.';
}


//Thread Two
void CustomThreadTwo::stepFunction()
{
    if (!mModel->hasChildren())
        return;

    QModelIndex parent;
    for (QModelIndex curIndex; mModel->hasChildren(curIndex); curIndex = mModel->index(0, 0, curIndex))
        parent = curIndex;

    mModel->removeRow(0, parent);
}
