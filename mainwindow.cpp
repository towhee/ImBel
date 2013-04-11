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

#include "mainwindow.h"
#include "datamodel.h"

#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
//    dockWidgetTemplates->sizeHint().setHeight(200);  //not working

    QPixmap pixmap(":/ImBel.png");
    this->setWindowIcon(pixmap);

    initImage();

    QStringList headers;
    headers << tr("Item") << tr("Value");

    // read the data file ### add error trapping
    QFile file(":/ImBel.txt");
    file.open(QIODevice::ReadOnly);
    //DataModel *dModel = new DataModel(headers, file.readAll());
    dModel = new DataModel(headers, file.readAll());
    file.close();

    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());

    treeViewTemplate->setModel(dModel);
    treeViewTemplate->expandAll();


    // must set comboBoxTemplates after treeview because it updates
    // based on comboBoxTemplates index changing
    comboBoxTemplates->setModel(dModel);
    comboBoxTemplates->setRootModelIndex(rootIndex);
    comboBoxTemplates->setCurrentIndex(0);

//    QModelIndex modelRootIndex = dModel->index(0,0,QModelIndex());
//    QModelIndex treeRootIndex = rootIndex.child(row,0);
    updateTreeViewTemplates(rootIndex.child(0,0));

    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(treeViewTemplate->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));

    connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
    connect(insertRowAction, SIGNAL(triggered()), this, SLOT(insertRow()));
    connect(insertColumnAction, SIGNAL(triggered()), this, SLOT(insertColumn()));
    connect(removeRowAction, SIGNAL(triggered()), this, SLOT(removeRow()));
    connect(removeColumnAction, SIGNAL(triggered()), this, SLOT(removeColumn()));
    connect(insertChildAction, SIGNAL(triggered()), this, SLOT(insertChild()));

    updateActions();

    //RunTest();
}

void MainWindow::RunTest()
{
    QRegExp rx("^(Border|Text|Shape|Graphic)$");
    qDebug() << "Border :  " << (rx.exactMatch("Border"));
    qDebug() << "Border1:  " << (rx.exactMatch("Border1"));


    QModelIndex parent = dModel->addTemplateToModel("New Template");
    comboBoxTemplates->setCurrentIndex(comboBoxTemplates->model()->rowCount());
    updateTreeViewTemplates(parent);

//    QModelIndex modelRootIndex = dModel->index(0,0,QModelIndex());
//    dModel->serializeModelData(modelRootIndex, 0);
}







void MainWindow::showModelInTree()
{
    qDebug() << "showModelInTree";
    QTreeView *tree = new QTreeView;
    tree->setModel(dModel);
    tree->expandAll();
    tree->resizeColumnToContents(0);
    tree->resizeColumnToContents(1);
    tree->resizeColumnToContents(2);
    tree->setAlternatingRowColors(true);
    tree->setMinimumSize(600,800);
    tree->show();
}

void MainWindow::initImage()
{
    QGraphicsScene *scene = new QGraphicsScene;
    QPixmap pixmap(":/Hummer1000.jpg");
    scene->addPixmap(pixmap);
    qDebug() << "graphicsView width: " << graphicsView->geometry();
    qDebug() << "pixmap width:       " << pixmap.width();
    graphicsView->setScene(scene);
    graphicsView->show();
}

//*************************************************************************************
//  TEMPLATE OPERATIONS
//*************************************************************************************

void MainWindow::updateTreeViewTemplates(const QModelIndex &treeRootIndex)
{
    treeViewTemplate->setRootIndex(treeRootIndex);
    treeViewTemplate->setRootIsDecorated(true);
    treeViewTemplate->resizeColumnToContents(0);
    treeViewTemplate->resizeColumnToContents(1);
    int columnWidth = treeViewTemplate->columnWidth(0) + 20;
    treeViewTemplate->setColumnWidth(0, columnWidth);
    treeViewTemplate->expandAll();
}

void MainWindow::on_comboBoxTemplates_currentIndexChanged(const QString &arg1)
{
    int comboRow = comboBoxTemplates->currentIndex();
    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());
    updateTreeViewTemplates(rootIndex.child(comboRow,0));
}

void MainWindow::on_treeViewTemplate_clicked(const QModelIndex &index)
{
    qDebug() << "on_treeViewTemplate_clicked";
//    updateTreeViewProperties(index);              //Eliminated treeview for now
}

void MainWindow::addTemplate()
{
    QModelIndex parent = dModel->addTemplateToModel("New Template");
    comboBoxTemplates->setCurrentIndex(comboBoxTemplates->model()->rowCount());
    updateTreeViewTemplates(parent);
}

void MainWindow::addObject(QString name)
{
    // Get the current template, which will be the current comboBox selection
    int comboRow = comboBoxTemplates->currentIndex();
    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());
    QModelIndex rootTemplate = rootIndex.child(comboRow, 0);
    // Pass along to datamodel, where childCount can be used
    dModel->addTemplateObject(rootTemplate, name);
}

void MainWindow::addBorder()
{
    addObject("Border");
}

void MainWindow::addText()
{
    addObject("Text");
}

void MainWindow::addShape()
{
    addObject("Shape");
}

void MainWindow::addGraphic()
{
    addObject("Graphic");
}

void MainWindow::toggleViewTemplateWidget()
{
    if (dockWidgetTemplates->isVisible()) {dockWidgetTemplates->hide();}
        else dockWidgetTemplates->show();
}

void MainWindow::filterJustTemplates(const QModelIndex &node)
{
/*
filterJustTemplates() is a recursive tree walker that looks for all tree nodes that
are values and hides them.  This code has been deprecated for a simpler view of the
template tree.
*/
    qDebug() << "filterJustTemplates";
    QRegExp rx("^(File|Image|Text|Border|Shape|Graphic)[s0-9]{0,3}$");
    QString nodeText = node.data(Qt::DisplayRole).toString();
    // find out if there are children
    if (rx.exactMatch(nodeText) == false) {
        treeViewTemplate->setRowHidden(node.row(), node.parent(), true);
    }
    if (dModel->hasChildren()) {
        // repeat for each child
        for (int i = 0; i < dModel->rowCount(node); ++i){
            filterJustTemplates(dModel->index(i,0,node));
        }
    }
}

void MainWindow::expandAllTreeTemplates()
{
    treeViewTemplate->expandAll();
}

void MainWindow::collapseAllTreeTemplates()
{
    treeViewTemplate->collapseAll();
}

//*************************************************************************************
//  TREE OPERATIONS
//*************************************************************************************

void MainWindow::insertChild()
{
    QModelIndex index = treeViewTemplate->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeViewTemplate->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
    }

    treeViewTemplate->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool MainWindow::insertColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = treeViewTemplate->model();
    int column = treeViewTemplate->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1, parent);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

    updateActions();

    return changed;
}

void MainWindow::insertRow()
{
    QModelIndex index = treeViewTemplate->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeViewTemplate->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }
}

bool MainWindow::removeColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = treeViewTemplate->model();
    int column = treeViewTemplate->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    bool changed = model->removeColumn(column, parent);

    if (!parent.isValid() && changed)
        updateActions();

    return changed;
}

void MainWindow::removeRow()
{
    QModelIndex index = treeViewTemplate->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeViewTemplate->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void MainWindow::updateActions()
{
    bool hasSelection = !treeViewTemplate->selectionModel()->selection().isEmpty();
    removeRowAction->setEnabled(hasSelection);
    removeColumnAction->setEnabled(hasSelection);

    bool hasCurrent = treeViewTemplate->selectionModel()->currentIndex().isValid();
    insertRowAction->setEnabled(hasCurrent);
    insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        treeViewTemplate->closePersistentEditor(treeViewTemplate->selectionModel()->currentIndex());

        int row = treeViewTemplate->selectionModel()->currentIndex().row();
        int column = treeViewTemplate->selectionModel()->currentIndex().column();
        if (treeViewTemplate->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
}
