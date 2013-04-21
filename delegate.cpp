#include "delegate.h"
#include "datamodel.h"
#include <QDebug>

// Return no flags - therefore cannot edit
QWidget* NoEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                              const QModelIndex &index) const
{
    return 0;
}



void BaseDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{

    QModelIndex idx = index.model()->index(index.row(), INDEX, index.parent());
    QString indexText = idx.model()->data(idx,Qt::DisplayRole).toString();
    bool isValueRow = false;
    if (indexText.length() > 0) isValueRow = true;

    bool alternateRow = false;
    if(!(index.row()%2 == 0)) alternateRow = true;

    bool fillAlternatingRows = false;

    QRect borderRect(option.rect);
    if (index.column() == 0) borderRect.setLeft(1);
    borderRect.setBottom(borderRect.bottom()+1);

    QRect fillRect(borderRect);
    fillRect.adjust(0, -1, 0, -1);

    if (fillAlternatingRows) {
        if (alternateRow) painter->fillRect(fillRect, Qt::lightGray);
    }

    // Paint background for description header items (like File, Image etc)
    // They do not have an index therefore isValueRow = false
    if (isValueRow == false) {
        painter->fillRect(fillRect, QColor(98, 141, 191, 25));
    }

    // paint the borders a custom color
    painter->setPen(QColor(225, 225, 225, 200));
    painter->drawLine( borderRect.topLeft(), borderRect.topRight() );
    painter->drawLine( borderRect.bottomLeft(), borderRect.bottomRight() );
    if (isValueRow)
        painter->drawLine( borderRect.topLeft(), borderRect.bottomLeft() );

    // parent class runs
    QStyledItemDelegate::paint( painter, option, index );
}

QSize BaseDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
        QSize a;
        a.setHeight(24);
        a.setWidth(200);
        return(a);
}

bool WidgetDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                 const QStyleOptionViewItem &option, const QModelIndex &index)
{
    qDebug() << "WidgetDelegate::editorEvent: " << event->type() << "  Parent: " << this->parent();

    //QAbstractItemView::edit(index);

    return false;
}

QWidget* WidgetDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    qDebug() << "WidgetDelegate::createEditor - Parent = " << parent;
    QModelIndex idx = index.model()->index(index.row(), 2, index.parent());
    QString indexText = idx.model()->data(idx,Qt::DisplayRole).toString();
    bool isValueRow = false;
    if (indexText.length() > 0) isValueRow = true;
    if (isValueRow == false) return 0;

    // determine type of widget from model (delegate column)
    QModelIndex idxD = index.model()->index(index.row(), 3, index.parent());
    QString delegateType = idxD.model()->data(idxD,Qt::DisplayRole).toString();
    if (delegateType == "Spinbox") {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setFrame(true);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    if (delegateType == "Combobox") {
        QComboBox *editor = new QComboBox(parent);
        return editor;
    }
    if (delegateType == "Text"){
        QTextEdit *editor = new QTextEdit(parent);
        editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        return editor;
    }
    if (delegateType == "Checkbox"){
        QCheckBox *editor = new QCheckBox(parent);
        return editor;
    }
    return 0;  // solution for now
    QStyledItemDelegate::createEditor(parent, option, index);
}

void WidgetDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << "WidgetDelegate::setEditorData";
    QModelIndex idxV = index.model()->index(index.row(), 1, index.parent());
    QModelIndex idxD = index.model()->index(index.row(), 3, index.parent());
    QString delegateType = idxD.model()->data(idxD,Qt::DisplayRole).toString();
    if (delegateType == "Spinbox") {
        int value = idxV.model()->data(idxV,Qt::DisplayRole).toInt();
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
        return;
    }
    if (delegateType == "Combobox") {
        QString value = idxV.model()->data(idxV,Qt::DisplayRole).toString();
        QComboBox *combobox = static_cast<QComboBox*>(editor);
        combobox->addItem(value);
        return;
    }
    if (delegateType == "Text") {
        QString value = idxV.model()->data(idxV,Qt::DisplayRole).toString();
        QTextEdit *textEdit = static_cast<QTextEdit*>(editor);
        textEdit->append(value);
        return;
    }
    if (delegateType == "Checkbox"){
        QString value = idxV.model()->data(idxV,Qt::DisplayRole).toString();
        QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
        (value == "true") ? checkbox->setChecked(true) : checkbox->setChecked(false);
        return;
    }
    QStyledItemDelegate::setEditorData(editor,index);
}

void WidgetDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    qDebug() << "WidgetDelegate::setModelData";
    QModelIndex idxD = index.model()->index(index.row(), 3, index.parent());
    QString delegateType = idxD.model()->data(idxD,Qt::DisplayRole).toString();
    if (delegateType == "Spinbox") {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        int value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
        return;
    }
    if (delegateType == "Combobox") {
        QComboBox *combobox = static_cast<QComboBox*>(editor);
        QString value = combobox->currentText();
        model->setData(index, value, Qt::EditRole);
        return;
    }
    if (delegateType == "Text") {
        QTextEdit *textEdit = static_cast<QTextEdit*>(editor);
        QString value = textEdit->toPlainText();
        model->setData(index, value, Qt::EditRole);
        return;
    }
    if (delegateType == "Checkbox") {
        QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
        bool check = checkbox->isChecked();
        QString value;
        check ? value = "true" : value = "false";
        model->setData(index, value, Qt::EditRole);
        return;
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}

void WidgetDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "WidgetDelegate::updateEditorGeometry";
    QRect widgetRect = option.rect;
    widgetRect.adjust(0, 1, 0, -1);
    editor->setGeometry(widgetRect);
}

void WidgetDelegate::on_BaseDelegate_MouseOver(const QModelIndex &index) const
{
    qDebug() << "WidgetDelegate::on_BaseDelegate_MouseOver";
}

//void WidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
//                           const QModelIndex &index) const
//{
//    QModelIndex idxD = index.model()->index(index.row(), 3, index.parent());
//    QString delegateType = idxD.model()->data(idxD,Qt::DisplayRole).toString();
//    if (delegateType == "Slider") {
//        editor.
//    }
//}
