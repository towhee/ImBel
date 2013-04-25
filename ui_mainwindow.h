/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *exitAction;
    QAction *insertRowAction;
    QAction *removeRowAction;
    QAction *insertColumnAction;
    QAction *removeColumnAction;
    QAction *insertChildAction;
    QAction *action_Run_test;
    QAction *actionAnother;
    QAction *actionShow_Templates;
    QAction *actionShow_model_in_tree;
    QAction *actionAdd_a_new_border;
    QAction *actionAdd_a_new_text;
    QAction *actionAdd_a_new_shape;
    QAction *actionAdd_a_new_graphic;
    QAction *actionAdd_a_new_template;
    QAction *action_Expand_all_in_tree;
    QAction *action_Collapse_all_in_tree;
    QAction *actionTest2;
    QAction *actionTest;
    QAction *action_Save;
    QAction *actionSave_As;
    QAction *action_Open;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *actionsMenu;
    QMenu *menu_Test;
    QMenu *menu_View;
    QStatusBar *statusbar;
    QDockWidget *dockWidgetTemplates;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_2;
    QFrame *frameTreeTemplates;
    QVBoxLayout *verticalLayout;
    QFrame *frameToolButtons;
    QFormLayout *formLayout;
    QToolButton *toolButton;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBoxTemplates;
    QToolButton *toolButtonExpandAll;
    QToolButton *toolButtonCollapseAll;
    QTreeView *treeViewTemplate;
    QToolBar *toolBar;
    QDockWidget *dockWidgetPreferences;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1306, 964);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Graphics/Hummer32.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::ForceTabbedDocks);
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        insertRowAction = new QAction(MainWindow);
        insertRowAction->setObjectName(QStringLiteral("insertRowAction"));
        removeRowAction = new QAction(MainWindow);
        removeRowAction->setObjectName(QStringLiteral("removeRowAction"));
        insertColumnAction = new QAction(MainWindow);
        insertColumnAction->setObjectName(QStringLiteral("insertColumnAction"));
        removeColumnAction = new QAction(MainWindow);
        removeColumnAction->setObjectName(QStringLiteral("removeColumnAction"));
        insertChildAction = new QAction(MainWindow);
        insertChildAction->setObjectName(QStringLiteral("insertChildAction"));
        action_Run_test = new QAction(MainWindow);
        action_Run_test->setObjectName(QStringLiteral("action_Run_test"));
        actionAnother = new QAction(MainWindow);
        actionAnother->setObjectName(QStringLiteral("actionAnother"));
        actionShow_Templates = new QAction(MainWindow);
        actionShow_Templates->setObjectName(QStringLiteral("actionShow_Templates"));
        actionShow_Templates->setCheckable(true);
        actionShow_model_in_tree = new QAction(MainWindow);
        actionShow_model_in_tree->setObjectName(QStringLiteral("actionShow_model_in_tree"));
        actionAdd_a_new_border = new QAction(MainWindow);
        actionAdd_a_new_border->setObjectName(QStringLiteral("actionAdd_a_new_border"));
        actionAdd_a_new_text = new QAction(MainWindow);
        actionAdd_a_new_text->setObjectName(QStringLiteral("actionAdd_a_new_text"));
        actionAdd_a_new_shape = new QAction(MainWindow);
        actionAdd_a_new_shape->setObjectName(QStringLiteral("actionAdd_a_new_shape"));
        actionAdd_a_new_graphic = new QAction(MainWindow);
        actionAdd_a_new_graphic->setObjectName(QStringLiteral("actionAdd_a_new_graphic"));
        actionAdd_a_new_template = new QAction(MainWindow);
        actionAdd_a_new_template->setObjectName(QStringLiteral("actionAdd_a_new_template"));
        action_Expand_all_in_tree = new QAction(MainWindow);
        action_Expand_all_in_tree->setObjectName(QStringLiteral("action_Expand_all_in_tree"));
        action_Collapse_all_in_tree = new QAction(MainWindow);
        action_Collapse_all_in_tree->setObjectName(QStringLiteral("action_Collapse_all_in_tree"));
        actionTest2 = new QAction(MainWindow);
        actionTest2->setObjectName(QStringLiteral("actionTest2"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionTest->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Graphics/Plus.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionTest->setIcon(icon1);
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QStringLiteral("action_Save"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QStringLiteral("border-bottom-color: rgb(171, 171, 171);"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 1, 0);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setFrameShape(QFrame::Panel);
        graphicsView->setFrameShadow(QFrame::Plain);
        graphicsView->setLineWidth(1);
        graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1306, 21));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QStringLiteral("fileMenu"));
        actionsMenu = new QMenu(menubar);
        actionsMenu->setObjectName(QStringLiteral("actionsMenu"));
        menu_Test = new QMenu(menubar);
        menu_Test->setObjectName(QStringLiteral("menu_Test"));
        menu_View = new QMenu(menubar);
        menu_View->setObjectName(QStringLiteral("menu_View"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        statusbar->setStyleSheet(QStringLiteral("background-color: rgb(156, 156, 156);"));
        MainWindow->setStatusBar(statusbar);
        dockWidgetTemplates = new QDockWidget(MainWindow);
        dockWidgetTemplates->setObjectName(QStringLiteral("dockWidgetTemplates"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidgetTemplates->sizePolicy().hasHeightForWidth());
        dockWidgetTemplates->setSizePolicy(sizePolicy);
        dockWidgetTemplates->setMinimumSize(QSize(300, 117));
        dockWidgetTemplates->setBaseSize(QSize(0, 0));
        dockWidgetTemplates->setLocale(QLocale(QLocale::English, QLocale::Canada));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        frameTreeTemplates = new QFrame(dockWidgetContents_3);
        frameTreeTemplates->setObjectName(QStringLiteral("frameTreeTemplates"));
        frameTreeTemplates->setFrameShape(QFrame::Panel);
        frameTreeTemplates->setFrameShadow(QFrame::Plain);
        frameTreeTemplates->setLineWidth(0);
        verticalLayout = new QVBoxLayout(frameTreeTemplates);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frameToolButtons = new QFrame(frameTreeTemplates);
        frameToolButtons->setObjectName(QStringLiteral("frameToolButtons"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frameToolButtons->sizePolicy().hasHeightForWidth());
        frameToolButtons->setSizePolicy(sizePolicy1);
        frameToolButtons->setMaximumSize(QSize(16777215, 0));
        frameToolButtons->setFrameShape(QFrame::StyledPanel);
        frameToolButtons->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frameToolButtons);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(3, 0, 0, 0);
        toolButton = new QToolButton(frameToolButtons);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setMinimumSize(QSize(0, 20));

        formLayout->setWidget(0, QFormLayout::LabelRole, toolButton);


        verticalLayout->addWidget(frameToolButtons);

        frame_2 = new QFrame(frameTreeTemplates);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy2);
        frame_2->setMaximumSize(QSize(16777215, 25));
        frame_2->setSizeIncrement(QSize(0, 0));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBoxTemplates = new QComboBox(frame_2);
        comboBoxTemplates->setObjectName(QStringLiteral("comboBoxTemplates"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBoxTemplates->sizePolicy().hasHeightForWidth());
        comboBoxTemplates->setSizePolicy(sizePolicy3);
        comboBoxTemplates->setMinimumSize(QSize(0, 0));
        comboBoxTemplates->setEditable(true);
        comboBoxTemplates->setInsertPolicy(QComboBox::InsertAtCurrent);

        horizontalLayout->addWidget(comboBoxTemplates);

        toolButtonExpandAll = new QToolButton(frame_2);
        toolButtonExpandAll->setObjectName(QStringLiteral("toolButtonExpandAll"));
        toolButtonExpandAll->setMinimumSize(QSize(0, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        toolButtonExpandAll->setFont(font);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Graphics/Plus2.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonExpandAll->setIcon(icon2);
        toolButtonExpandAll->setAutoRaise(true);
        toolButtonExpandAll->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(toolButtonExpandAll);

        toolButtonCollapseAll = new QToolButton(frame_2);
        toolButtonCollapseAll->setObjectName(QStringLiteral("toolButtonCollapseAll"));
        toolButtonCollapseAll->setMinimumSize(QSize(0, 21));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setWeight(75);
        toolButtonCollapseAll->setFont(font1);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Graphics/Minus2.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonCollapseAll->setIcon(icon3);
        toolButtonCollapseAll->setAutoRaise(true);

        horizontalLayout->addWidget(toolButtonCollapseAll);


        verticalLayout->addWidget(frame_2);

        treeViewTemplate = new QTreeView(frameTreeTemplates);
        treeViewTemplate->setObjectName(QStringLiteral("treeViewTemplate"));
        sizePolicy.setHeightForWidth(treeViewTemplate->sizePolicy().hasHeightForWidth());
        treeViewTemplate->setSizePolicy(sizePolicy);
        treeViewTemplate->setMinimumSize(QSize(300, 0));
        treeViewTemplate->setSizeIncrement(QSize(0, 0));
        treeViewTemplate->setBaseSize(QSize(0, 0));
        treeViewTemplate->setMouseTracking(true);
        treeViewTemplate->setAutoFillBackground(true);
        treeViewTemplate->setStyleSheet(QStringLiteral(""));
        treeViewTemplate->setFrameShadow(QFrame::Plain);
        treeViewTemplate->setLineWidth(0);
        treeViewTemplate->setAlternatingRowColors(false);
        treeViewTemplate->setIndentation(10);
        treeViewTemplate->setRootIsDecorated(false);
        treeViewTemplate->setWordWrap(true);
        treeViewTemplate->header()->setDefaultSectionSize(25);

        verticalLayout->addWidget(treeViewTemplate);


        verticalLayout_2->addWidget(frameTreeTemplates);

        dockWidgetTemplates->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetTemplates);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidgetPreferences = new QDockWidget(MainWindow);
        dockWidgetPreferences->setObjectName(QStringLiteral("dockWidgetPreferences"));
        dockWidgetPreferences->setMinimumSize(QSize(0, 0));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockWidgetPreferences->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetPreferences);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(actionsMenu->menuAction());
        menubar->addAction(menu_Test->menuAction());
        menubar->addAction(menu_View->menuAction());
        fileMenu->addAction(action_Open);
        fileMenu->addAction(action_Save);
        fileMenu->addAction(actionSave_As);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAction);
        actionsMenu->addAction(actionAdd_a_new_template);
        actionsMenu->addSeparator();
        actionsMenu->addAction(actionAdd_a_new_border);
        actionsMenu->addAction(actionAdd_a_new_text);
        actionsMenu->addAction(actionAdd_a_new_shape);
        actionsMenu->addAction(actionAdd_a_new_graphic);
        actionsMenu->addSeparator();
        actionsMenu->addAction(insertRowAction);
        actionsMenu->addAction(insertColumnAction);
        actionsMenu->addSeparator();
        actionsMenu->addAction(removeRowAction);
        actionsMenu->addAction(removeColumnAction);
        actionsMenu->addSeparator();
        actionsMenu->addAction(insertChildAction);
        menu_Test->addAction(action_Run_test);
        menu_Test->addAction(actionTest2);
        menu_View->addAction(actionShow_Templates);
        menu_View->addAction(actionShow_model_in_tree);
        menu_View->addSeparator();
        menu_View->addAction(action_Expand_all_in_tree);
        menu_View->addAction(action_Collapse_all_in_tree);
        toolBar->addAction(actionTest);

        retranslateUi(MainWindow);
        QObject::connect(action_Run_test, SIGNAL(triggered()), MainWindow, SLOT(RunTest()));
        QObject::connect(actionShow_Templates, SIGNAL(triggered()), MainWindow, SLOT(toggleViewTemplateWidget()));
        QObject::connect(action_Expand_all_in_tree, SIGNAL(triggered()), MainWindow, SLOT(expandAllTreeTemplates()));
        QObject::connect(action_Collapse_all_in_tree, SIGNAL(triggered()), MainWindow, SLOT(collapseAllTreeTemplates()));
        QObject::connect(toolButtonExpandAll, SIGNAL(clicked()), MainWindow, SLOT(expandAllTreeTemplates()));
        QObject::connect(toolButtonCollapseAll, SIGNAL(clicked()), MainWindow, SLOT(collapseAllTreeTemplates()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ImBel", 0));
        exitAction->setText(QApplication::translate("MainWindow", "E&xit", 0));
        exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        insertRowAction->setText(QApplication::translate("MainWindow", "Insert Row", 0));
        insertRowAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+I, R", 0));
        removeRowAction->setText(QApplication::translate("MainWindow", "Remove Row", 0));
        removeRowAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+R, R", 0));
        insertColumnAction->setText(QApplication::translate("MainWindow", "Insert Column", 0));
        insertColumnAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+I, C", 0));
        removeColumnAction->setText(QApplication::translate("MainWindow", "Remove Column", 0));
        removeColumnAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+R, C", 0));
        insertChildAction->setText(QApplication::translate("MainWindow", "Insert Child", 0));
        insertChildAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        action_Run_test->setText(QApplication::translate("MainWindow", "&Run test", 0));
        action_Run_test->setShortcut(QApplication::translate("MainWindow", "Alt+T", 0));
        actionAnother->setText(QApplication::translate("MainWindow", "Another", 0));
        actionShow_Templates->setText(QApplication::translate("MainWindow", "Show &Templates", 0));
        actionShow_Templates->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", 0));
        actionShow_model_in_tree->setText(QApplication::translate("MainWindow", "Show model in tree", 0));
        actionAdd_a_new_border->setText(QApplication::translate("MainWindow", "Add a new border", 0));
        actionAdd_a_new_text->setText(QApplication::translate("MainWindow", "Add a new text", 0));
        actionAdd_a_new_shape->setText(QApplication::translate("MainWindow", "Add a new shape", 0));
        actionAdd_a_new_graphic->setText(QApplication::translate("MainWindow", "Add a new graphic", 0));
        actionAdd_a_new_template->setText(QApplication::translate("MainWindow", "Add a new &template", 0));
        action_Expand_all_in_tree->setText(QApplication::translate("MainWindow", "&Expand all in tree", 0));
        action_Expand_all_in_tree->setShortcut(QApplication::translate("MainWindow", "Ctrl++", 0));
        action_Collapse_all_in_tree->setText(QApplication::translate("MainWindow", "&Collapse all in tree", 0));
        action_Collapse_all_in_tree->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0));
        actionTest2->setText(QApplication::translate("MainWindow", "Test2", 0));
        actionTest->setText(QApplication::translate("MainWindow", "Test", 0));
#ifndef QT_NO_TOOLTIP
        actionTest->setToolTip(QApplication::translate("MainWindow", "This is a test", 0));
#endif // QT_NO_TOOLTIP
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0));
        action_Save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save &As", 0));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0));
        fileMenu->setTitle(QApplication::translate("MainWindow", "&File", 0));
        actionsMenu->setTitle(QApplication::translate("MainWindow", "&Actions", 0));
        menu_Test->setTitle(QApplication::translate("MainWindow", "&Test", 0));
        menu_View->setTitle(QApplication::translate("MainWindow", "&View", 0));
        dockWidgetTemplates->setWindowTitle(QApplication::translate("MainWindow", "Templates", 0));
        toolButton->setText(QApplication::translate("MainWindow", "...", 0));
#ifndef QT_NO_TOOLTIP
        toolButtonExpandAll->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Expand all branches of the tree.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        toolButtonExpandAll->setStatusTip(QApplication::translate("MainWindow", "Expand all braches of the template tree.", 0));
#endif // QT_NO_STATUSTIP
        toolButtonExpandAll->setText(QApplication::translate("MainWindow", "+", 0));
        toolButtonCollapseAll->setText(QApplication::translate("MainWindow", "-", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        dockWidgetPreferences->setWindowTitle(QApplication::translate("MainWindow", "Preferences", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
