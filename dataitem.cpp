/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
    treeitem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include "dataitem.h"

#include <QStringList>

//! [0]
DataItemItem::DataItemItem(const QVector<QVariant> &data, DataItemItem *parent)
{
    parentItem = parent;
    itemData = data;
}
//! [0]

//! [1]
DataItemItem::~DataItemItem()
{
    qDeleteAll(childItems);
}
//! [1]

//! [2]
DataItemItem *DataItemItem::child(int number)
{
    return childItems.value(number);
}
//! [2]

//! [3]
int DataItemItem::childCount() const
{
    return childItems.count();
}
//! [3]

//! [4]
int DataItemItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<DataItemItem*>(this));

    return 0;
}
//! [4]

//! [5]
int DataItemItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
QVariant DataItemItem::data(int column) const
{
    return itemData.value(column);
}
//! [6]

//! [7]
bool DataItemItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        DataItemItem *item = new DataItemItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
bool DataItemItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (DataItemItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}
//! [8]

//! [9]
DataItemItem *DataItemItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
bool DataItemItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
//! [10]

bool DataItemItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (DataItemItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

//! [11]
bool DataItemItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}
//! [11]
