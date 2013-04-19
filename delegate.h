#ifndef DELEGATE_H
#define DELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QSpinbox>
#include <QTextEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QSlider>
#include <QDial>


class BaseDelegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    BaseDelegate(QObject* parent=0): QStyledItemDelegate(parent) {}
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    enum modelColumns
    {
        DESCRIPTION, VALUE, INDEX, DELEGATE, HELPTIP
    };
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

signals:
    void statusUpdate(const QString &) const;

};

class NoEditDelegate: public BaseDelegate
{
    Q_OBJECT
public:
    NoEditDelegate(QObject* parent=0): BaseDelegate(parent) {}
    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const;
};

class WidgetDelegate: public BaseDelegate
{
    Q_OBJECT

public:
    WidgetDelegate(QObject* parent=0): BaseDelegate(parent) {}
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:
    void on_BaseDelegate_MouseOver(const QModelIndex &index) const;

};

#endif // DELEGATE_H
