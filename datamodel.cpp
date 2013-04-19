
#include <QtWidgets>

#include "dataitem.h"
#include "datamodel.h"

//! [0]
DataModel::DataModel(const QStringList &headers, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    // Build the array ds[][] that holds the data structure for each template
    // object: file, image, border, text, shape and graphic.  This is used to build
    // new objects (file, image, border, text, shape and graphic)
    initDataStructure();

    // Read data from data file into the model
    // Start with the headers
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    // create the root
    rootItem = new DataItemItem(rootData);
    rootItem->insertChildren(0, 1, 5);
    rootItem->child(0)->setData(0, "root");

    // populate the model from the data file
    readFileData(data.split(QString("\n")), rootItem);
    appendAttributeColumnData(index(0, 0, QModelIndex()));
}
//! [0]

//! [1]
DataModel::~DataModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int DataModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}
//! [2]

QVariant DataModel::data(const QModelIndex &index, int role) const
{
{/*
    The data structure:

    data(0) = item description
    data(1) = item value
    data(2) = item string index (concat of all generation item descriptions
    data(3) = item delegate to use
    data(4) = item help tip
 */}
    if (!index.isValid())
        return QVariant();

    if (role == Qt::StatusTipRole || role == Qt::ToolTipRole){
        DataItemItem *item = getItem(index);
        emit mouseOverItem(index);
//        mouseOverItem(index);
        return item->data(M_HELPTIP).toString();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole){
        DataItemItem *item = getItem(index);
        return item->data(index.column());
     }

    return QVariant();
}

//void DataModel::mouseOverItem(const QModelIndex &index) const
//{
//    emit(index);
//}

//! [3]
Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [3]

//void DataModel::setFlags(Qt::ItemFlags flags)
//{
//    setData((int) flags, Qt::UserRole - 1);
//}

DataItemItem *DataModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        DataItemItem *item = static_cast<DataItemItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}


QVariant DataModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//! [5]
QModelIndex DataModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
//! [5]

//! [6]
    DataItemItem *parentItem = getItem(parent);

    DataItemItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
//! [6]

bool DataModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool DataModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    DataItemItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex DataModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DataItemItem *childItem = getItem(index);
    DataItemItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool DataModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool DataModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    DataItemItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int DataModel::rowCount(const QModelIndex &parent) const
{
    DataItemItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
//! [8]

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    DataItemItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool DataModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

// Algorithm to walk a tree structure
void DataModel::walkTree(const QModelIndex &row)
{
    if (this->hasChildren()) {
        for (int i = 0; i < rowCount(row); ++i){
            walkTree(this->index(i,0,row));
        }
    }
}


void DataModel::readFileData(const QStringList &lines, DataItemItem *parent)
{
    QList<DataItemItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int lineNumber = 0;

    while (lineNumber < lines.count()) {
        int position = 0;
        while (position < lines[lineNumber].length()) {
            if (lines[lineNumber].mid(position, 1) != "*")
                break;
            ++position;
        }

        QString lineData = lines[lineNumber].mid(position).trimmed();

        if (!lineData.isEmpty()) {

            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            DataItemItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column){
                if (columnData[column] == "N/A") columnData[column] = "";
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
            }
        }

        ++lineNumber;
    }
}

QString DataModel::getDelegate(const QModelIndex &index) const
{
    DataItemItem *item = getItem(index);
    return item->data(3).toString();
}

QString DataModel::getHelpTip(const QModelIndex &index) const
{
    DataItemItem *item = getItem(index);
    return item->data(4).toString();
}

QModelIndex DataModel::findModelRow(QModelIndex &startRow, QString name)
{
    QModelIndexList sList = match(startRow, Qt::DisplayRole, name, 1,Qt::MatchRecursive);
    return sList[0];
}

QString DataModel::star(int count)
{
    QString s = "";
    if (count > 0)
        for (int i = 0; i < count; ++i)
            s.append("*");
    return s;
}

void DataModel::serializeModelData(const QModelIndex &idx, int level, QString &fileText)
{
    QString objectText = this->data(idx, Qt::DisplayRole).toString();
    QModelIndex idx1 = this->index(idx.row(), M_VALUE, idx.parent());
    QString valueText = this->data(idx1, Qt::DisplayRole).toString();
    QModelIndex idx2 = this->index(idx.row(), M_INDEX, idx.parent());
    QString indexText = this->data(idx2, Qt::DisplayRole).toString();

    if (level > 0) {    // do not save root, it is created in constructor
        QString rowText = star(level);
        rowText.append(objectText);
        // Check if attribute row with values and and index
        if (indexText.length() > 0) {
            if (valueText.length() == 0) valueText = "N/A";
            rowText.append(QString("\t%1").arg(valueText));
            rowText.append(QString("\t%1").arg(indexText));
        }
        rowText.append("\n");
        fileText.append(rowText);
    }

    if (this->hasChildren()) {
        int nRows = rowCount(idx);
        for (int nRow = 0; nRow < nRows; ++nRow){
            serializeModelData(this->index(nRow, 0, idx), level+1, fileText);
        }
    }
}

void DataModel::initDataStructure()
{
    /*
    The data for each template is stored in a file called ImBel.txt.  It holds the tree structure
    for each template object (image, border etc) that has been added for the template.  This
    function, initDataStructure, holds the master list of the attributes for each template object
    in the QList ds of QStringList (each line).  The attributes include instructions on what to add when a new template
    object (border, shape etc) are added by the user, including all the properties, delegates,
    help tips and an IndexCode that is useful for lookups.

    ds takes the form ds[row][column]

    Columns are enumerated by DSF as LEVEL0, LEVEL1, LEVEL2, INDEX, DELEGATE, HELPTIP

    Therefore ds[17][HELPTIP] = the help tip in the 17th row.
              ds[17][INDEX] = the index code, which might be "ImageTint"

              Search for the appropriate INDEX to find the right row, then get column
    */
    QFile file(":/ImBel Data Structure.txt");
    file.open(QIODevice::ReadOnly);
    QString dsTxt = file.readAll();
    QStringList lines = dsTxt.split(QString("\n"));
    dataStructureRows = lines.length();
    for (int line = 1; line < lines.length(); ++line)
    {
        QStringList columnList = lines[line].split("\t", QString::SkipEmptyParts);
        ds.append(columnList);
    }
}

QModelIndex DataModel::addTemplateToModel(QString name)
{
/*
Adds a new template to the model, which is reflected in comboBoxTemplates.
See comments in initDataStructure() and addTemplateObjectToModel()
*/
    QModelIndex modelRootIndex = index(0,0,QModelIndex());
    DataItemItem *rootItem = getItem(modelRootIndex);
    int newRowIndex = rootItem->childCount();
    rootItem->insertChildren(rootItem->childCount(), 1, 1);
    QModelIndex newTemplate = index(newRowIndex, 0, modelRootIndex);
    setData(newTemplate, name, Qt::EditRole);
    addTemplateObjectToModel(newTemplate, "File");
    addTemplateObjectToModel(newTemplate, "Image");
    addTemplateObjectToModel(newTemplate, "Borders");
    addTemplateObjectToModel(newTemplate, "Texts");
    addTemplateObjectToModel(newTemplate, "Shapes");
    addTemplateObjectToModel(newTemplate, "Graphics");
    return newTemplate;
}

void DataModel::addTemplateObject(QModelIndex &rootTemplate, QString name)
{
    // Find the template object parent
    QString searchFor;
    if (name == "Border")  searchFor = "Borders";
    if (name == "Text")  searchFor = "Texts";
    if (name == "Shape")  searchFor = "Shapes";
    if (name == "Graphic")  searchFor = "Graphics";
    QModelIndex objectParent = findModelRow(rootTemplate, searchFor);
    addTemplateObjectToModel(objectParent, name);
}


void DataModel::addTemplateObjectToModel(QModelIndex &parent, QString objectName)
{
    {
    /*
    All the information required to manage the templates is contained in the tab
    deliminated text file "ImBel Data Structure.txt" which resides in the QRC.  This file
    is loaded into a QList ds of QStringList. SEE initDataStructure().  Here is a sample
    of part of the text section of the file:

    Level0	Level1          Level2  IndexCode           Delegate                Help tip
    Text	Source          N/A     TextSource          Combobox + Button       N/A
    Text	Text            N/A     TextText            Text                    N/A
    Text	Font            N/A     TextFont            Combobox                N/A
    Text	Size            N/A     TextSize            Slider                  N/A
    Text	Color           N/A     TextColor           Color picker            N/A
    Text	Opacity         N/A     TextOpacity         Slider                  N/A
    Text	Blending mode	N/A     TextBlending mode	Combobox                N/A
    Text	Halo            Size	TextHaloSize        Slider                  N/A
    Text	Halo            Color	TextHaloColor       Color picker            N/A
    Text	Halo            Opacity	TextHaloOpacity     Slider                  N/A
    Text	Halo            Fade	TextHaloFade        Slider                  N/A

    addTemplateObjectToModel reads the data and adds it to the model.  It is then up to
    the user to enter property values.  Since blanks are not considered in a tab delimited file
    "N/A is used and ignored in the translation into the model.  In this case, the data will be
    converted to look like this:

    Text
        Source                  // No 2nd level because Level2 = N/A
        Text
        Font
        Size
        Color
        Opacity
        Blending mode
        Halo                    // 2nd level from here on
            Size
            Color
            Opacity
            Fade

    The IndexCode and help tips are loaded into hidden columns.  The Index code is used for
    lookups back into QList ds[][].

     **/
    }
    // Append the passed index to the template item
    // If it is a border, text, shape or graphic find out how many already exist
    // and append a number ie Border6
    QString objectTreeName = objectName;

    DataItemItem *rootItem = getItem(parent);
    rootItem->insertChildren(rootItem->childCount(), 1, 3);
    QRegExp rx("^(Border|Text|Shape|Graphic)$");
    if (rx.exactMatch(objectName) == true)
        objectTreeName.append(QString("%1").arg(rootItem->childCount()));
    rootItem->child(rootItem->childCount() - 1)->setData(0, objectTreeName);
    // Point to the new item1
    DataItemItem *parentItem1 = rootItem->child(rootItem->childCount()-1);
    // Point to the 2nd level as required
    DataItemItem *parentItem2;
    // Pointer to use
    DataItemItem *parentItem;
    DataItemItem *currentItem;

    bool createRow;
    bool isColumnData;
    parentItem2 = parentItem1;

    for (int row = 0; row < ds.length() - 1; ++row)
    {
        if (ds[row][D_LEVEL0] == objectName) {
            // ds[row][1] = level 0 tree branch, ds[row][2] = level 1 tree branch
//            qDebug() << ds[row][INDEX];
            for (int col = 1; col < 3; ++col){
                parentItem = parentItem1;
                createRow = true;
                isColumnData = false;
                // Set things up if Level1
                if (col == D_LEVEL1 && ds[row][D_LEVEL2] == "N/A")
                    isColumnData = true;
                if (row > 0)
                    if (col == D_LEVEL1 && ds[row][col] == ds[row-1][col])
                        createRow = false;

                // Set things up if Level2
                if (col == D_LEVEL2) {
                    if (ds[row][D_LEVEL2] == "N/A")
                        createRow = false;
                    else {
                        isColumnData = true;
                        if (row > 0)
                            parentItem = parentItem2;
                    }
                }
                if (col == D_LEVEL2 && row == 0)
                        parentItem = parentItem2;

                // Create a new row, either a child or a sibling
                if (createRow == true) {

                    {
//                        QString s1 = ds[row][2];
//                        pad(s1, 20);
//                        QString s2 = ds[row][3];
//                        pad(s2, 20);
//                        QString s3 = parentItem2->data(0).toString();
//                        pad(s3, 20);
//                        QString s4 = parentItem->data(0).toString();
//                        pad(s4, 20);
//                    qDebug() << "Row: " << row << "\tCol: " << col
//                             << "\tchildCount: " << parentItem->childCount()
//                             << "\tisColumnData: " << isColumnData
//                             << "\tLevel)0: " << s1
//                             << "\tLevel_1: " << s2
//                             << "\tparentItem2: " << s3
//                             << "parentItem: " << s4
//                             << "Delegate: " << ds[row][DELEGATE];
                    }
                    parentItem->insertChildren(parentItem->childCount(), 1, 5);
                    currentItem = parentItem->child(parentItem->childCount() - 1);
                    currentItem->setData(0, ds[row][col]);
                    if (isColumnData == true) {
                        currentItem->setData(M_INDEX, ds[row][D_INDEX]);
                        currentItem->setData(M_DELEGATE, ds[row][D_DELEGATE]);
                        currentItem->setData(M_HELPTIP, ds[row][D_HELPTIP]);
                    }
                    if (col == D_LEVEL1)
                        parentItem2 = parentItem->child(parentItem->childCount()-1);
                }
            }
        }
    }
}

void DataModel::appendAttributeColumnData(QModelIndex &index)
/*
    Add the delegate and helptip information from the data structure to the model
*/
{
    QModelIndex indexIndex = this->index(index.row(), M_INDEX, index.parent());
    QString rowIndex = (this->data(indexIndex, Qt::DisplayRole)).toString();
    // only attributes with values have an INDEX description.
    if (rowIndex.length() > 0) {
        int rowDS = findRowInDS(rowIndex);
        QModelIndex delegateIndex = index.model()->index(index.row(), 3, index.parent());
        QModelIndex helptipIndex = index.model()->index(index.row(), 4, index.parent());
        this->setData(delegateIndex, ds[rowDS][D_DELEGATE]);
        this->setData(helptipIndex, ds[rowDS][D_HELPTIP]);
    }
    if (hasChildren(index)){
        int nSiblings = rowCount(index);
        for (int sibling = 0; sibling < nSiblings; ++sibling) {
            appendAttributeColumnData(this->index(sibling, 0, index));
        }
    }
}

int DataModel::findRowInDS(QString indexText)
{
    for (int row = 0; row < ds.length() - 1; ++row)
        if (ds[row][D_INDEX] == indexText)
            return row;
}

void DataModel::pad(QString &text, int length)
{
    int currentLength = text.length();
    int padAmount = length - currentLength;

    if (padAmount > 0)
        for (int i=0; i < padAmount; ++i)
            text.append(" ");
    return;
}

void DataModel::show_ds()
{
//    for (int row = 0; row < ds.length(); ++row)
//        qDebug()
}


/*
void WriteIndex( const QAbstractItemModel & model, const QModelIndex & index, QTextStream & stream, int level )
{
    stream << level <<  index.row() << index.column() << index.data() << endl( stream );
    qDebug() << level <<
    if ( model.hasChildren( index ) )
    {
       int nRows = model.rowCount( index );
       int nCols = model.columnCount( index );
       for ( int nRow = 0; nRow < nRows; ++nRow )
       {
            for ( int nCol = 0; nCol < nCols; ++nCol )
            {
                WriteIndex( model, model.index( nRow, nCol, index ), stream, level + 1 );
            }
       }
    }
}*/

