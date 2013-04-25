#include "delegate.h"
#include "propertystyle.h"
#include "datamodel.h"
#include "text.h"
#include <QDebug>
#include <qglobal.h>

PropertyDelegate::PropertyDelegate(QObject* parent)
{

}

void PropertyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{

    // Item text
    QModelIndex idxItem = index.model()->index(index.row(), M_ITEM, index.parent());
    QString itemText = idxItem.model()->data(idxItem,Qt::DisplayRole).toString();

    // Parent item text
    QModelIndex idxParent = index.parent();
    QString parentText = idxParent.model()->data(idxParent,Qt::DisplayRole).toString();

    // Item value
    QModelIndex idxValue = index.model()->index(index.row(), M_VALUE, index.parent());
    QString valueText = idxValue.model()->data(idxValue,Qt::DisplayRole).toString();

    // Index string
    QModelIndex idx = index.model()->index(index.row(), M_INDEX, index.parent());
    QString indexText = idx.model()->data(idx,Qt::DisplayRole).toString();

    bool isValueRow = false;
    if (indexText.length() > 0) isValueRow = true;

    // Check if top level item
    bool isTopLevel = false;
    bool is2ndLevel = false;
    bool is3rdLevel = false;
    QRegExp rx("^(FILE|IMAGE|BORDERS|TEXTS|SHAPES|GRAPHICS)$");
    if (rx.exactMatch(itemText) == true) isTopLevel = true;
    if (rx.exactMatch(parentText) == true) is2ndLevel = true;
    if (!isTopLevel && !is2ndLevel && !isValueRow) is3rdLevel = true;

    QColor headerColor = QColor(46, 90, 111, 50);
    QColor subHeaderColor = QColor(128, 128, 128, 25);
    QColor valueRowColor = QColor(0, 0, 0, 200);
    QColor borderColor = QColor(225, 225, 225, 200);

    QStyleOptionViewItem overrideOption(option);
    initStyleOption(&overrideOption, index);

    if (isValueRow || is3rdLevel) {
        overrideOption.palette.setColor(QPalette::Text, valueRowColor);
//        overrideOption.palette.setColor(QPalette::Base, Qt::black);
        QStyledItemDelegate::paint( painter, overrideOption, index );
    } else {
        QStyledItemDelegate::paint( painter, option, index );
    }

    painter->save();

//    QRect displayRect;
//    QRect textRect(option.rect);
//    textRect.adjust(2, 4, 0 , 0);
//    QFont font = option.font;
//    QColor level3Color = QColor(0, 0, 0, 200);
//    QColor valueRowColor = QColor(0, 0, 0, 200);

//    if (isTopLevel && index.column() == M_ITEM) {
//        qDebug() << "Item match: " << itemText;
////        font.setBold(true);
//        font.setLetterSpacing(QFont::AbsoluteSpacing, 2.0);
//        painter->setFont(font);
//        // now figure out where and how to write the column one items
//        painter->drawText(textRect, itemText);
//    }
//    else if (is2ndLevel && index.column() == M_ITEM) {
//        painter->drawText(textRect, itemText);
//    }
//    else if (is3rdLevel && index.column() == M_ITEM) {
//        painter->setPen(level3Color);
//        painter->drawText(textRect, itemText);
//    }
//    else if (index.column() == M_ITEM && !isTopLevel){
//        painter->setPen(valueRowColor);
//        painter->drawText(textRect, itemText);
//    }
//    else if (index.column() == M_VALUE && !isTopLevel){
//        painter->setPen(valueRowColor);
//        painter->drawText(textRect, valueText);
//    }
////    else if (isTopLevel != true && index.column() == M_VALUE){
////        painter->drawText(textRect, itemText);
////    }

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
        if (isTopLevel || is2ndLevel) painter->fillRect(fillRect, headerColor);      //
        else painter->fillRect(fillRect, subHeaderColor);
    }

    // paint the borders a custom color
    painter->setPen(borderColor);
    painter->drawLine( borderRect.topLeft(), borderRect.topRight() );
    painter->drawLine( borderRect.bottomLeft(), borderRect.bottomRight() );
    if (isValueRow)
        painter->drawLine( borderRect.topLeft(), borderRect.bottomLeft() );

    painter->restore();
}

QSize PropertyDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QSize a;
    a.setHeight(22);
    a.setWidth(150);
    return(a);
}

bool PropertyDelegate::eventFilter(QObject *object, QEvent *event)
{
    QStyledItemDelegate::eventFilter(object, event);
    QWidget *editor = qobject_cast<QWidget*>(object);

    if (!editor)
        return false;

    // This makes sure the last edited item is saved to the model if the user immediately shifts the
    // focus outside the parent object (such as the treeview that contains the delegates).  This does
    // not close the active delegate, which would be desireable, because the same event fires when
    // opening a combobox, so it would immediately close again and you are unable to edit.
    if (event->type() == QEvent::FocusOut) {
        emit commitData(editor);
//        emit closeEditor(editor, NoHint);
        return true;
    }

    return false;
}


//bool WidgetDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
//                 const QStyleOptionViewItem &option, const QModelIndex &index) const

QWidget* PropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    if (index.column() == 0) return 0;
    qDebug() << "WidgetDelegate::createEditor - Parent = " << parent;
    QModelIndex idx = index.model()->index(index.row(), M_INDEX, index.parent());
    QString indexText = idx.model()->data(idx, Qt::DisplayRole).toString();
    bool isValueRow = false;
    if (indexText.length() > 0) isValueRow = true;
    if (isValueRow == false) return 0;

    // Get the inputrange/list in a QStringList
    QModelIndex idxRange = index.model()->index(index.row(), M_RANGE, index.parent());
    QString rangeText = idxRange.model()->data(idxRange, Qt::DisplayRole).toString();
    rangeText.replace('"', "");
    QStringList inputList = rangeText.split(",");

    // Get the current value
    QString value = index.data(Qt::DisplayRole).toString();

    // determine type of widget from model (delegate column)
    QModelIndex idxD = index.model()->index(index.row(), M_DELEGATE, index.parent());
    QString delegateType = idxD.model()->data(idxD, Qt::DisplayRole).toString();
    if (delegateType == "Spinbox") {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setFrame(true);
        if (inputList[0] != "N/A") {
            editor->setMinimum(inputList[0].toInt());
            editor->setMaximum(inputList[1].toInt());
        }
        return editor;
    }
    if (delegateType == "Combobox") {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(inputList);
        editor->setEditable(false);
        editor->setInsertPolicy(QComboBox::InsertAtCurrent);
        editor->removeItem(editor->count());
        editor->setCurrentIndex(editor->findText(value));
        return editor;
    }
    if (delegateType == "Text"){
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    }
    if (delegateType == "Checkbox"){
        QCheckBox *editor = new QCheckBox(parent);
        return editor;
    }
    return 0;  // solution for now
    QStyledItemDelegate::createEditor(parent, option, index);
}

void PropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << "WidgetDelegate::setEditorData";
    QModelIndex idxV = index.model()->index(index.row(), 1, index.parent());
    QModelIndex idxD = index.model()->index(index.row(), 3, index.parent());
    QString delegateType = idxD.model()->data(idxD,Qt::DisplayRole).toString();
    if (delegateType == "Spinbox") {
        int value = idxV.model()->data(idxV,Qt::DisplayRole).toInt();
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setFocusPolicy(Qt::StrongFocus);
        spinBox->setValue(value);
        return;
    }
    if (delegateType == "Combobox") {
        QString value = idxV.model()->data(idxV,Qt::DisplayRole).toString();
        QComboBox *combobox = static_cast<QComboBox*>(editor);
        combobox->setCurrentIndex(combobox->findText(value));
        return;
    }
    if (delegateType == "Text") {
        QString value = idxV.model()->data(idxV,Qt::DisplayRole).toString();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(value);
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

void PropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    qDebug() << "WidgetDelegate::setModelData";
    QModelIndex idxD = index.model()->index(index.row(), M_DELEGATE, index.parent());
    QString delegateType = idxD.model()->data(idxD, Qt::DisplayRole).toString();
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
        qDebug() << "WidgetDelegate::setModelData for Combobox = " << value;
        return;
    }
    if (delegateType == "Text") {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        QString value = lineEdit->text();
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

void PropertyDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "WidgetDelegate::updateEditorGeometry";
    if (index.column() == 1){
        QRect widgetRect = option.rect;
        widgetRect.adjust(0, 1, 0, -1);
        editor->setGeometry(widgetRect);
    }
}

void PropertyDelegate::on_BaseDelegate_MouseOver(const QModelIndex &index) const
{
    qDebug() << "WidgetDelegate::on_BaseDelegate_MouseOver";
}

