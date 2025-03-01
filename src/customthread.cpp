#include "customthread.h"

#include <QMutexLocker>
#include <QStack>

// Thread One
void CustomThreadOne::stepFunction()
{
    QMutexLocker locker(getMutex());

    QModelIndex parent;
    QStack<bool> canAddRow;
    QStack<int> rowToAdd;

    for ( ; ; )
    {
        int rows = mModel->rowCount(parent);

        canAddRow.push(mModel->canInsertRows(parent));
        rowToAdd.push(rows);

        if (!mModel->hasChildren(parent))
            break;

        parent = mModel->index(rows - 1, 0, parent);
    }

    for ( ; !canAddRow.isEmpty(); rowToAdd.pop())
    {
        if (canAddRow.pop())
        {
            mModel->insertRow(rowToAdd.pop(), parent);
            break;
        }

        parent = mModel->parent(parent);
    }
}



//Thread Two
void CustomThreadTwo::stepFunction()
{
    QMutexLocker locker(getMutex());

    if (!mModel->hasChildren())
        return;

    QModelIndex parent;
    for (QModelIndex curIndex; mModel->hasChildren(curIndex); curIndex = mModel->index(0, 0, curIndex))
        parent = curIndex;

    mModel->removeRow(0, parent);
}
