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

#include <QtWidgets>

#include "dataitem.h"
#include "datamodel.h"

//! [0]
DataModel::DataModel(const QStringList &headers, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    // Build the array ds[][] that holds the data structure for each template
    // object: file, image, border, text, shape and graphic.
    initDataStructure();

    // Read date from data file into the model
    // Start with the headers
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    rootItem = new DataItemItem(rootData);
    // populate the model from the data file
    setupModelData(data.split(QString("\n")), rootItem);
}
//! [0]

//! [1]
DataModel::~DataModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int DataModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}
//! [2]

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    DataItemItem *item = getItem(index);

    return item->data(index.column());
}

//! [3]
Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [3]

//! [4]
DataItemItem *DataModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        DataItemItem *item = static_cast<DataItemItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
//! [4]

QVariant DataModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//! [5]
QModelIndex DataModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
//! [5]

//! [6]
    DataItemItem *parentItem = getItem(parent);

    DataItemItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
//! [6]

bool DataModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool DataModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    DataItemItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex DataModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DataItemItem *childItem = getItem(index);
    DataItemItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool DataModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool DataModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    DataItemItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int DataModel::rowCount(const QModelIndex &parent) const
{
    DataItemItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
//! [8]

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    DataItemItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool DataModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void DataModel::walkTree(const QModelIndex &node)
{
    // Do model stuff with current index
//    qDebug() << this->data(index(node.row(),0,node.parent()), Qt::DisplayRole).toString() << " | "
//             << this->data(index(node.row(),1,node.parent()), Qt::DisplayRole).toString() << " | "
//             << this->data(index(node.row(),2,node.parent()), Qt::DisplayRole).toString() << " | "
//             << this->hasChildren(); // << " | " << node.child(0,0).model()->hasChildren();

    // find out if there are children
    if (this->hasChildren()) {
        // repeat for each child
        for (int i = 0; i < rowCount(node); ++i){
            walkTree(this->index(i,0,node));
        }
    }
}


void DataModel::setupModelData(const QStringList &lines, DataItemItem *parent)
{
    QList<DataItemItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int lineNumber = 0;

    while (lineNumber < lines.count()) {
        int position = 0;
        while (position < lines[lineNumber].length()) {
            if (lines[lineNumber].mid(position, 1) != "*")
                break;
            ++position;
        }

        QString lineData = lines[lineNumber].mid(position).trimmed();

        if (!lineData.isEmpty()) {

            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            DataItemItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        ++lineNumber;
    }
}

void DataModel::serializeModelData(const QModelIndex &index, int level)
{

    // Do model stuff with current index
    qDebug() << "Siblings: " << rowCount(index.parent()) << "\t"
             << "Level: " << level << "\t"
             << "Row: " << index.row() << "\t"
             << "Col: " << index.column() << "\t"
             << this->data(index, Qt::DisplayRole).toString();

    // find out if there are children
    if (this->hasChildren()) {
        QString text = this->data(index, Qt::DisplayRole).toString();
        int nRows = rowCount(index);
        int nCols = columnCount(index);
        // repeat for each child
        for (int nRow = 0; nRow < nRows; ++nRow){
            for (int nCol = 0; nCol < nCols; ++nCol) {
                // check to see if the node value is null
                QString text = this->data(index, Qt::DisplayRole).toString();
                if (text.length() > 0)
                    serializeModelData(this->index(nRow, nCol, index), level+1);
            }
        }
    }
}

/*
The data for each template is stored in a file called ImBel.txt.  It holds the tree structure
for each template object (image, border etc) that has been added for the template.  This
function, initDataStructure, holds the master list of the attributes for each template object
in the QList ds of QStringList (each line).  The attributes include instructions on what to add when a new template
object (border, shape etc) are added by the user, including all the properties, delegates,
help tips and an IndexCode that is useful for lookups.

ds takes the form ds[row][column]

Columns are enumerated by DSF as LEVEL, OBJECT, SUBOBJECT, PROPERTY, INDEX, DELEGATE, HELPTIP

Therefore ds[17][HELPTIP] = the help tip in the 17th row.
          ds[17][INDEX] = the index code, which might be "ImageTint"

          Search for the appropriate INDEX to find the right row, then get column
*/
void DataModel::initDataStructure()
{
    QFile file(":/ImBel Data Structure.txt");
    file.open(QIODevice::ReadOnly);
    QString dsTxt = file.readAll();
//    qDebug() << dsTxt;
    QStringList lines = dsTxt.split(QString("\n"));
    dataStructureRows = lines.length();
    for (int line = 1; line < lines.length(); ++line)
    {
        QStringList columnList = lines[line].split("\t", QString::SkipEmptyParts);
        ds.append(columnList);
    }
}

QModelIndex DataModel::addTemplateToModel(QString name)
{
    QModelIndex modelRootIndex = index(0,0,QModelIndex());
    int lastRootChild = modelRootIndex.model()->rowCount() + 1;
//    QModelIndex lastTemplate = this->index(lastRootChild, 0, modelRootIndex);
    insertRows(lastRootChild + 1, lastRootChild + 1, modelRootIndex);
//    insertRow(lastRootChild + 1, modelRootIndex);
    QModelIndex newTemplate = this->index(lastRootChild + 1, 0, modelRootIndex);
    qDebug() << newTemplate << "\tnChildren: " << newTemplate.model()->rowCount();
    this->setData(newTemplate, name, Qt::EditRole);
    addTemplateObjectToModel(newTemplate, "File");
    addTemplateObjectToModel(newTemplate, "Image");
    return newTemplate;
}

void DataModel::addTemplateObjectToModel(QModelIndex &parent, QString objectType)
{
    // Append the passed index to the template item
    DataItemItem *rootItem = getItem(parent);
    rootItem->insertChildren(rootItem->childCount(), 1, 1);
    for (int column = 0; column < 1; ++column)
        rootItem->child(rootItem->childCount() - 1)->setData(column, objectType);
    // Point to the new item1
    DataItemItem *parentItem1 = rootItem->child(rootItem->childCount()-1);

//    beginInsertRows(parent, 0, 0);
//    insertRow(0, parent);
//    endInsertRows();
//    QModelIndex parentLevel0 = index(0, 0, parent);
//    DataItemItem *parentItem1 = getItem(parent.child(0, 0));
//    setData(parentLevel0, objectType, Qt::EditRole);

    DataItemItem *parentItem;
    DataItemItem *parentItem2;

    bool createRow;

    for (int row = 0; row < ds.length() - 1; ++row)
    {
        if (ds[row][OBJECT] == objectType) {
            // ds[row][2] = level 0 tree branch, ds[row][3] = level 1 tree branch
            for (int col = 2; col < 4; ++col){
                parentItem = parentItem1;
                createRow = true;

                // Set things up if Level1
                if (row > 0)
                    if (col == LEVEL1 && ds[row][col] == ds[row-1][col])
                        createRow = false;

                // Set things up if Level2
                if (col == LEVEL2) {
                    if (ds[row][LEVEL2] == "N/A")
                        createRow = false;
                    else
                        if (row > 0)
                            if (ds[row][LEVEL1] == ds[row-1][LEVEL1])
                                parentItem = parentItem2;
                            else
                                parentItem = parentItem1;
                }
                if (col == LEVEL2 && row == 0)
                        parentItem = parentItem2;

                // Create a new row, either a child or a sibling
                if (createRow == true) {

                    {
//                    qDebug() << "Row: " << row << "\tCol: " << col
//                             << "\tchildCount: " << parentItem->childCount()
//                             << "\tLevel)0: " << ds[row][2]
//                             << "\tLevel_1: " << ds[row][3]
//                             << "parentItem: " << parentItem->data(0).toString();
                    }
                    parentItem->insertChildren(parentItem->childCount(), 1, 1);
                    for (int column = 0; column < 1; ++column)
                        parentItem->child(parentItem->childCount() - 1)->setData(column, ds[row][col]);

                    if (col == LEVEL1)
                        parentItem2 = parentItem->child(parentItem->childCount()-1);
                }
            }
        }
    }
}




//                if (!(ds[row][col] == "N/A"))
//                {
//                    QString sParent = parentObject.model()->data(parentObject, Qt::DisplayRole).toString();
//                    QString sParentToUse = parentToUse.model()->data(parentToUse, Qt::DisplayRole).toString();
//                    QString sNewObject = parentSubObject.model()->data(parentSubObject, Qt::DisplayRole).toString();
//                    QString sNewRow = ds[row][col];

//                    qDebug() << "Object: " << ds[row][OBJECT]
//                             << "\trow: " << row << "\tcol: " << col
//                             << "\tds[row][col]: " << ds[row][col]
//                             << "\t\tnChildren: " << nChildren
//                             << "\tLast object: " << sNewObject
//                             << "\tparentToUse: " << sParentToUse;

//                    parentToUse = parentObject;
//                    QString dsCol2 = ds[row][2];
//                    if (col == 3 && !(ds[row][2] == "N/A")) parentToUse = parentSubObject;
//                    nChildren = parentToUse.model()->rowCount();

//                    beginInsertRows(parentToUse, 0, 0);
//                    insertRow(0, parentToUse);
////                    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
//                    endInsertRows();
////                    insertRows(nChildren, nChildren, parentToUse);
//                    QModelIndex newObject = index(0, 0, parentToUse);
//                    this->setData(newObject, ds[row][col], Qt::EditRole);
//                    qDebug() << "New Object: "
//                             << newObject.model()->data(newObject, Qt::DisplayRole).toString();
//                    // add column data for INDEX, DELEGATE, HELPTIP

//                    // if there is a SubObject then make it the parentToUse
////                    ++rowCounter;
//                }

//                int lastSibling = parentObject.model()->rowCount();

//                    QString strMsg = QString("Parent\t\t\t: %1\t\t\nNum Children:\t %2\nNew row\t\t: %3")
//                            .arg(sParentToUse).arg(lastSibling).arg(sNewRow);
//                    msg.setText(strMsg);
//                    msg.exec();

void DataModel::show_ds()
{
//    for (int row = 0; row < ds.length(); ++row)
//        qDebug()
}


/*
void WriteIndex( const QAbstractItemModel & model, const QModelIndex & index, QTextStream & stream, int level )
{
    stream << level <<  index.row() << index.column() << index.data() << endl( stream );
    qDebug() << level <<
    if ( model.hasChildren( index ) )
    {
       int nRows = model.rowCount( index );
       int nCols = model.columnCount( index );
       for ( int nRow = 0; nRow < nRows; ++nRow )
       {
            for ( int nCol = 0; nCol < nCols; ++nCol )
            {
                WriteIndex( model, model.index( nRow, nCol, index ), stream, level + 1 );
            }
       }
    }
}*/

