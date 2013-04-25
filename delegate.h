#ifndef DELEGATE_H
#define DELEGATE_H
#include <QtCore/qobject.h>
#include <QtWidgets/qstyleoption.h>

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

#include <QItemDelegate>
#include <QPainter>
#include <QPalette>
#include <QStyleOptionViewItem>
#include <QSpinbox>
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QSlider>
#include <QDial>

// Same enum in datamodel.h - MUST UPDATE BOTH
enum DSF                 // Data Structure Field
{
    D_LEVEL0, D_LEVEL1, D_LEVEL2, D_INDEX, D_DELEGATE, D_RANGE, D_HELPTIP
};
enum modelColumns
{
    M_ITEM, M_VALUE, M_INDEX, M_DELEGATE, M_RANGE, M_HELPTIP
};

//class PropertyStyle;

class PropertyDelegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit PropertyDelegate(QObject* parent=0);
//    ~BaseDelegate();

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool eventFilter(QObject *object, QEvent *event);

private:
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QWidget *currentEditor;

public slots:
    void on_BaseDelegate_MouseOver(const QModelIndex &index) const;

signals:
    void statusUpdate(const QString &) const;

};


#endif // DELEGATE_H
