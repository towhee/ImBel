

#include "mainwindow.h"
#include "datamodel.h"
#include "text.h"

#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    this->tabifyDockWidget(dockWidgetTemplates, dockWidgetPreferences);
    dockWidgetTemplates->raise();
    dockWidgetTemplates->resize(300, 0);

    QPixmap pixmap(":/Graphics/ImBel.png");
    this->setWindowIcon(pixmap);

    this->showStatus(tr("Welcome to ImBel"));

    initImage();

    PropertyEditor *propertyEditor = new PropertyEditor(treeViewTemplate, comboBoxTemplates,
                                                  "ImBel.txt");
//    propertyEditor->showModelInTree();

    connect(actionShow_model_in_tree, SIGNAL(triggered()),
            propertyEditor, SLOT(showModelInTree()));
    connect(comboBoxTemplates, SIGNAL(currentIndexChanged(int)),
            propertyEditor, SLOT(on_filterbox_currentIndexChanged()));

    connect(action_Save, SIGNAL(triggered()), propertyEditor, SLOT(saveFile()));
    connect(actionAdd_a_new_template, SIGNAL(triggered()), propertyEditor, SLOT(addTemplate()));
    connect(actionAdd_a_new_border, SIGNAL(triggered()), propertyEditor, SLOT(addBorder()));
    connect(actionAdd_a_new_text, SIGNAL(triggered()), propertyEditor, SLOT(addText()));
    connect(actionAdd_a_new_shape, SIGNAL(triggered()), propertyEditor, SLOT(addShape()));
    connect(actionAdd_a_new_graphic, SIGNAL(triggered()), propertyEditor, SLOT(addGraphic()));

    connect(removeRowAction, SIGNAL(triggered()), propertyEditor, SLOT(removeRow()));

    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

//    connect(treeViewTemplate->selectionModel(),
//            SIGNAL(selectionChanged(const QItemSelection &,
//                                    const QItemSelection &)),
//            this, SLOT(updateActions()));

//    connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
//    connect(insertRowAction, SIGNAL(triggered()), this, SLOT(insertRow()));
//    connect(insertColumnAction, SIGNAL(triggered()), this, SLOT(insertColumn()));
//    connect(removeRowAction, SIGNAL(triggered()), this, SLOT(removeRow()));
//    connect(removeColumnAction, SIGNAL(triggered()), this, SLOT(removeColumn()));
//    connect(insertChildAction, SIGNAL(triggered()), this, SLOT(insertChild()));

//    updateActions();

}

void MainWindow::RunTest()
{
//    Fonts *f = new Fonts;
//    f->availableFonts();

//    qDebug() << fileText;
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

void MainWindow::toggleViewTemplateWidget()
{
    if (dockWidgetTemplates->isVisible()) {dockWidgetTemplates->hide();}
        else dockWidgetTemplates->show();
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
//  TEMPLATE OPERATIONS
//*************************************************************************************




//*************************************************************************************
//  WINDOW OPERATIONS
//*************************************************************************************

void MainWindow::showStatus(QString &msg)
{
    statusBar()->showMessage(msg);
}
