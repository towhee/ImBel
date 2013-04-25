#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QObject>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QTreeView>
#include <QComboBox>

#include "delegate.h"
#include "datamodel.h"


class DataModel;

class PropertyEditor : public QObject
{
    Q_OBJECT

public:
    explicit PropertyEditor(QTreeView *treeView, QComboBox *combobox,
                            QString fileName,
                            QObject *parent = 0);

private:
    QTreeView *tree;
    QComboBox *filterbox;
    DataModel *dModel;

    PropertyDelegate *baseDelegate;

    void initTree();
    void updateTree(const QModelIndex &treeRootIndex);
//    void updateActions();

signals:
    
public slots:

    void showModelInTree();
    void on_tree_mouseMove(const QModelIndex &index) const;
    void on_filterbox_currentIndexChanged();
    void addTemplate();
    void addObject(QString name);
    void addBorder();
    void addText();
    void addShape();
    void addGraphic();
    bool saveFile();

//    void insertChild();
//    bool insertColumn(const QModelIndex &parent = QModelIndex());
//    void insertRow();
//    bool removeColumn(const QModelIndex &parent = QModelIndex());
    void removeRow();


private slots:
    void on_tree_clicked(const QModelIndex &index);
    bool readFile(QString fileName);

    
};

#endif // PROPERTYEDITOR_H
