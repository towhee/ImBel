

#include "mainwindow.h"
#include "datamodel.h"

#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    this->tabifyDockWidget(dockWidgetTemplates, dockWidgetOptions);
    dockWidgetTemplates->raise();

    QPixmap pixmap(":/Graphics/ImBel.png");
    this->setWindowIcon(pixmap);

    this->showStatus(tr("Welcome to ImBel"));

    initImage();

    // Headers must match the enum DSF and the DataModel constructor!
    QStringList headers;
    headers << tr("Item") << tr("Value") << tr("Index")
            << tr("Delegate") << tr("HelpTip");

    // read the data file ### add error trapping
//    QFile file(":/ImBel.txt");
    QFile file("ImBel.txt");
    file.open(QIODevice::ReadOnly);
    dModel = new DataModel(headers, file.readAll());
    file.close();

    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());

    initTreeTemplate();
    // must set comboBoxTemplates after treeview because it updates
    // based on comboBoxTemplates index changing
    initTreeCombobox();

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

//    addTemplate();
}

void MainWindow::RunTest()
{


//    qDebug() << fileText;
}

bool MainWindow::saveFile()
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
    QPixmap pixmap(":/Graphics/Hummer1000.jpg");
    scene->addPixmap(pixmap);
    qDebug() << "graphicsView width: " << graphicsView->geometry();
    qDebug() << "pixmap width:       " << pixmap.width();
    graphicsView->setScene(scene);
    graphicsView->show();
}

//*************************************************************************************
//  TEMPLATE OPERATIONS
//*************************************************************************************

void MainWindow::initTreeTemplate()
{

    treeViewTemplate->setModel(dModel);
    treeViewTemplate->setRowHidden(0, QModelIndex(),true);
    treeViewTemplate->collapseAll();
    treeViewTemplate->setColumnWidth(0, 200);
//    treeViewTemplate->setColumnWidth(1, 100);
    treeViewTemplate->header()->setStretchLastSection(true);
    treeViewTemplate->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    treeViewTemplate->setColumnHidden(2, true);           // hide the index column
    treeViewTemplate->setColumnHidden(3, true);           // hide the delegate column
    treeViewTemplate->setColumnHidden(4, true);           // hide the helptip column
    treeViewTemplate->setRootIsDecorated(true);
    int c1 = treeViewTemplate->columnWidth(0);
    int c2 = treeViewTemplate->columnWidth(1);
}

void MainWindow::initTreeCombobox()
{
    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());
    comboBoxTemplates->setModel(dModel);
    comboBoxTemplates->setRootModelIndex(rootIndex);
    comboBoxTemplates->setCurrentIndex(0);
}

void MainWindow::on_comboBoxTemplates_currentIndexChanged(const QString &arg1)
{
    int comboRow = comboBoxTemplates->currentIndex();
    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());
    updateTreeViewTemplates(rootIndex.child(comboRow,0));
}

void MainWindow::updateTreeViewTemplates(const QModelIndex &treeRootIndex)
{
    treeViewTemplate->setRootIndex(treeRootIndex);
    QString s = QString("Widget width: %1\nColumn 0 width: %2\nColumn 1 width: %3")
              .arg(treeViewTemplate->width())
              .arg(treeViewTemplate->columnWidth(0))
              .arg(treeViewTemplate->columnWidth(1));
    qDebug() << s;
//    treeViewTemplate->resizeColumnToContents(0);
//    treeViewTemplate->resizeColumnToContents(1);
//    int columnWidth = treeViewTemplate->columnWidth(0) + 20;
//    treeViewTemplate->expandAll();
}

void MainWindow::on_treeViewTemplate_clicked(const QModelIndex &index)
{
    qDebug() << "on_treeViewTemplate_clicked";
//    updateTreeViewProperties(index);              //Eliminated treeview for now
}

bool MainWindow::readFile(QString fileName)
{
    int newTemplateCount = 1;
    return true;
}

void MainWindow::addTemplate()
{
    // Check if any other new templates
    int newTemplateCount = 1;
    if (comboBoxTemplates->count() > 0) {
        for (int i = 0; i < comboBoxTemplates->count(); ++i){
            QString s = comboBoxTemplates->itemData(i, Qt::DisplayRole).toString();
            if (s.startsWith("New Template"))
                    ++newTemplateCount;
        }

    }
    QString newTemplate = QString("New Template %1").arg(newTemplateCount);
    QModelIndex parent = dModel->addTemplateToModel(newTemplate);
    /* Appending a new template automatically adds a row to comboBoxTemplates
       as it is a model view.  Changing the comboBox index triggers
       :on_comboBoxTemplates_currentIndexChanged, which in turn, updates the
       template treeview. */
    comboBoxTemplates->setCurrentIndex(comboBoxTemplates->model()->rowCount()-1);
}

void MainWindow::addObject(QString name)
{
    // Get the current template, which will be the current comboBox selection
    int comboRow = comboBoxTemplates->currentIndex();
    QModelIndex rootIndex = dModel->index(0,0,QModelIndex());
    QModelIndex rootTemplate = rootIndex.child(comboRow, 0);
    // Pass along to datamodel, where childCount can be used
    dModel->addTemplateObject(rootTemplate, name);
    updateTreeViewTemplates(rootTemplate);
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

//*************************************************************************************
//  WINDOW OPERATIONS
//*************************************************************************************

void MainWindow::showStatus(QString &msg)
{
    statusBar()->showMessage(msg);
}
