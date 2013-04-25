#include "text.h"

Fonts::Fonts(QObject *parent) :
    QObject(parent)
{

}

//void Fonts::availableFonts()
//{
//    QFontDatabase database;
//     QTreeWidget fontTree;
//     fontTree.setColumnCount(2);
//     fontTree.setHeaderLabels(QStringList() << "Font" << "Smooth Sizes");

//     foreach (const QString &family, database.families()) {
//         QTreeWidgetItem *familyItem = new QTreeWidgetItem(&fontTree);
//         familyItem->setText(0, family);

//         foreach (const QString &style, database.styles(family)) {
//             QTreeWidgetItem *styleItem = new QTreeWidgetItem(familyItem);
//             styleItem->setText(0, style);

//             QString sizes;
//             foreach (int points, database.smoothSizes(family, style))
//                 sizes += QString::number(points) + " ";

//             styleItem->setText(1, sizes.trimmed());
//         }
//     }
//}
