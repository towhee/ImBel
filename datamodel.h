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

#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QTextStream>

#include "mainwindow.h"

class DataItemItem;


//! [0]
class DataModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    DataModel(const QString &data,
              QObject *parent = 0);
    ~DataModel();

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setFlags(Qt::ItemFlags flags);
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole);

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());

    QString getDelegate(const QModelIndex &index) const;
    QString getHelpTip(const QModelIndex &index) const;
    QModelIndex findModelRow(QModelIndex &startRow, QString name);

    void walkTree(const QModelIndex &node);
    void serializeModelData(const QModelIndex &node, int level,QString &fileText);
    void appendAttributeColumnData(QModelIndex & index);
    void WriteIndex( const QAbstractItemModel & model, const QModelIndex & index, QTextStream & stream, int level);

//    QString dataStructureFile;      // Data structure text file name in resources
    QList<QStringList> ds;          // Holds data struction

/* Same enum in delegate.h - MUST UPDATE BOTH

    1.  When creating a new column in data structure fill with "N/A"
    2.  Update enum in both datamodel.h and delegate.h
    3.  Update the header list in DataModel::DataModel
    4.  Hide the new column in PropertyEditor::initTree
    5.  Add column to DataModel::appendAttributeColumnData

 */
    enum DSF                 // Data Structure Field
    {
        D_LEVEL0, D_LEVEL1, D_LEVEL2, D_INDEX, D_DELEGATE, D_RANGE, D_HELPTIP
    };
    enum modelColumns
    {
        M_ITEM, M_VALUE, M_INDEX, M_DELEGATE, M_RANGE, M_HELPTIP
    };

    int dataStructureRows;      // ### required?
    QModelIndex addTemplateToModel(QString name);
    void addTemplateObjectToModel(QModelIndex &index, QString objectType);
    void addTemplateObject(QModelIndex &index, QString name);
    int findRowInDS(QString indexText);
    void show_ds();

private:
    void initDataStructure(QString &dataStructureFile);
    void readFileData(const QStringList &lines, DataItemItem *parent);
    void pad(QString &text, int length);
    QString star(int count);
    QString serializedModel;
    int level;
    DataItemItem *getItem(const QModelIndex &index) const;

    DataItemItem *rootItem;

signals:
    void mouseOverItem(const QModelIndex &index) const;
};
//! [2]

#endif // DATAMODEL_H
