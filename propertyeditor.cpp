#include "propertyeditor.h"
#include <QDebug>
#include <QFile>

PropertyEditor::PropertyEditor(QTreeView *treeView, QComboBox *combobox,
                               QString fileName,
                               QObject *parent) :  QObject(parent)
{
    tree = treeView;
    filterbox = combobox;

    // Headers must match the enum DSF and the DataModel constructor!
    QStringList headers;
    headers << tr("Item") << tr("Value") << tr("Index")
            << tr("Delegate") << tr("HelpTip");

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    dModel = new DataModel(headers, file.readAll());
    file.close();

    noEditDelegate = new NoEditDelegate(this);
    baseDelegate = new BaseDelegate(this);
    widgetDelegate = new WidgetDelegate(this);

    initTree();

    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());
    updateTree(rootIndex.child(0,0));

    connect(dModel, SIGNAL(mouseOverItem(const QModelIndex&)),
            this, SLOT(on_tree_mouseMove(const QModelIndex&)));

//    connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
//    connect(insertRowAction, SIGNAL(triggered()), this, SLOT(insertRow()));
//    connect(insertColumnAction, SIGNAL(triggered()), this, SLOT(insertColumn()));
//    connect(removeRowAction, SIGNAL(triggered()), this, SLOT(removeRow()));
//    connect(removeColumnAction, SIGNAL(triggered()), this, SLOT(removeColumn()));
//    connect(insertChildAction, SIGNAL(triggered()), this, SLOT(insertChild()));

//    updateActions();

}

void PropertyEditor::showModelInTree()
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


void PropertyEditor::initTree()
{

    tree->setModel(dModel);
    tree->setRowHidden(0, QModelIndex(),true);
    tree->collapseAll();
    tree->setColumnWidth(0, 150);
    tree->setColumnWidth(1, 100);
    tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // does not help
    tree->header()->setStretchLastSection(true);
    tree->setColumnHidden(2, true);           // hide the index column
    tree->setColumnHidden(3, true);           // hide the delegate column
    tree->setColumnHidden(4, true);           // hide the helptip column
    tree->setRootIsDecorated(true);
    tree->setEditTriggers(QAbstractItemView::AllEditTriggers);
    int c1 = tree->columnWidth(0);
    int c2 = tree->columnWidth(1);

    tree->setItemDelegate(baseDelegate);
    tree->setItemDelegateForColumn(0, noEditDelegate);
    tree->setItemDelegateForColumn(1, widgetDelegate);

    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());
    filterbox->setModel(dModel);
    filterbox->setRootModelIndex(rootIndex);
    filterbox->setCurrentIndex(0);

}

void PropertyEditor::on_filterbox_currentIndexChanged(const QString &arg1)
{
    int comboRow = filterbox->currentIndex();
    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());
    updateTree(rootIndex.child(comboRow,0));
}

void PropertyEditor::updateTree(const QModelIndex &treeRootIndex)
{
    tree->setRootIndex(treeRootIndex);
}

void PropertyEditor::on_tree_mouseMove(const QModelIndex &index) const
{
//    if (tree->EditingState());
//    tree->edit(index);
}

void PropertyEditor::on_tree_clicked(const QModelIndex &index)
{
//  QVariant helpTip = dModel->data(index, Qt::StatusTipRole);
    QString helpTip = dModel->getHelpTip(index);
    qDebug() << "on_tree_clicked - helpTip = " << helpTip;
}

bool PropertyEditor::readFile(QString fileName)
{
    int newTemplateCount = 1;
    return true;
}

void PropertyEditor::addTemplate()
{
    // Check if any other new templates
    int newTemplateCount = 1;
    if (filterbox->count() > 0) {
        for (int i = 0; i < filterbox->count(); ++i){
            QString s = filterbox->itemData(i, Qt::DisplayRole).toString();
            if (s.startsWith("New Template"))
                    ++newTemplateCount;
        }

    }
    QString newTemplate = QString("New Template %1").arg(newTemplateCount);
    QModelIndex parent = dModel->addTemplateToModel(newTemplate);
    /* Appending a new template automatically adds a row to filterbox
       as it is a model view.  Changing the comboBox index triggers
       :on_filterbox_currentIndexChanged, which in turn, updates the
       template treeview. */
    filterbox->setCurrentIndex(filterbox->model()->rowCount()-1);
}

void PropertyEditor::addObject(QString name)
{
    // Get the current template, which will be the current comboBox selection
    int comboRow = filterbox->currentIndex();
    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());
    QModelIndex rootTemplate = rootIndex.child(comboRow, 0);
    // Pass along to datamodel, where childCount can be used
    dModel->addTemplateObject(rootTemplate, name);
    updateTree(rootTemplate);
}

void PropertyEditor::addBorder()
{
    addObject("Border");
}

void PropertyEditor::addText()
{
    addObject("Text");
}

void PropertyEditor::addShape()
{
    addObject("Shape");
}

void PropertyEditor::addGraphic()
{
    addObject("Graphic");
}



//*************************************************************************************
//  TREE OPERATIONS
//*************************************************************************************

//void PropertyEditor::insertChild()
//{
//    QModelIndex index = tree->selectionModel()->currentIndex();
//    QAbstractItemModel *model = tree->model();

//    if (model->columnCount(index) == 0) {
//        if (!model->insertColumn(0, index))
//            return;
//    }

//    if (!model->insertRow(0, index))
//        return;

//    for (int column = 0; column < model->columnCount(index); ++column) {
//        QModelIndex child = model->index(0, column, index);
//        model->setData(child, QVariant("[No data]"), Qt::EditRole);
//        if (!model->headerData(column, Qt::Horizontal).isValid())
//            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
//    }

//    tree->selectionModel()->setCurrentIndex(model->index(0, 0, index),
//                                            QItemSelectionModel::ClearAndSelect);
//    updateActions();
//}

//bool PropertyEditor::insertColumn(const QModelIndex &parent)
//{
//    QAbstractItemModel *model = tree->model();
//    int column = tree->selectionModel()->currentIndex().column();

//    // Insert a column in the parent item.
//    bool changed = model->insertColumn(column + 1, parent);
//    if (changed)
//        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

//    updateActions();

//    return changed;
//}

//void PropertyEditor::insertRow()
//{
//    QModelIndex index = tree->selectionModel()->currentIndex();
//    QAbstractItemModel *model = tree->model();

//    if (!model->insertRow(index.row()+1, index.parent()))
//        return;

//    updateActions();

//    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
//        QModelIndex child = model->index(index.row()+1, column, index.parent());
//        model->setData(child, QVariant("[No data]"), Qt::EditRole);
//    }
//}

//bool PropertyEditor::removeColumn(const QModelIndex &parent)
//{
//    QAbstractItemModel *model = tree->model();
//    int column = tree->selectionModel()->currentIndex().column();

//    // Insert columns in each child of the parent item.
//    bool changed = model->removeColumn(column, parent);

//    if (!parent.isValid() && changed)
//        updateActions();

//    return changed;
//}

//void PropertyEditor::removeRow()
//{
//    QModelIndex index = tree->selectionModel()->currentIndex();
//    QAbstractItemModel *model = tree->model();
//    if (model->removeRow(index.row(), index.parent()))
//        updateActions();
//}

//void PropertyEditor::updateActions()
//{
//    bool hasSelection = !tree->selectionModel()->selection().isEmpty();
//    removeRowAction->setEnabled(hasSelection);
//    removeColumnAction->setEnabled(hasSelection);

//    bool hasCurrent = tree->selectionModel()->currentIndex().isValid();
//    insertRowAction->setEnabled(hasCurrent);
//    insertColumnAction->setEnabled(hasCurrent);

//    if (hasCurrent) {
//        tree->closePersistentEditor(tree->selectionModel()->currentIndex());

//        int row = tree->selectionModel()->currentIndex().row();
//        int column = tree->selectionModel()->currentIndex().column();
//        if (tree->selectionModel()->currentIndex().parent().isValid())
//            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
//        else
//            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
//    }
//}

bool PropertyEditor::saveFile()
{
    QModelIndex modelRootIndex = dModel->index(0,0,QModelIndex());
    QString fileText;
    dModel->serializeModelData(modelRootIndex, 0, fileText);
    qDebug() << fileText;
//    return true;
    QFile file("ImBel.txt");
    if (!file.open(QIODevice::WriteOnly))
          return false;
    QTextStream outStream(&file);
    outStream << fileText;
    file.close();
    return true;
}
