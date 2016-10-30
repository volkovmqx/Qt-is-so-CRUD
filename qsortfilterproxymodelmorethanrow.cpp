#include "qsortfilterproxymodelmorethanrow.h"
#include <QtSql>


QSortFilterProxyModelMoreThanRow::QSortFilterProxyModelMoreThanRow(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool QSortFilterProxyModelMoreThanRow::filterAcceptsRow(int sourceRow,const QModelIndex &sourceParent) const
 {
       QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
       QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
       QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);
       QModelIndex index3 = sourceModel()->index(sourceRow, 3, sourceParent);
       QModelIndex index4 = sourceModel()->index(sourceRow, 4, sourceParent);
       QModelIndex index5 = sourceModel()->index(sourceRow, 5, sourceParent);
       QModelIndex index6 = sourceModel()->index(sourceRow, 6, sourceParent);
       QModelIndex index7 = sourceModel()->index(sourceRow, 7, sourceParent);

     return (sourceModel()->data(index0).toString().contains(filterRegExp())
             || sourceModel()->data(index1).toString().contains(filterRegExp())
             || sourceModel()->data(index2).toString().contains(filterRegExp())
             || sourceModel()->data(index3).toString().contains(filterRegExp())
             || sourceModel()->data(index4).toString().contains(filterRegExp())
             || sourceModel()->data(index5).toString().contains(filterRegExp())
             || sourceModel()->data(index6).toString().contains(filterRegExp())
             || sourceModel()->data(index7).toString().contains(filterRegExp())
          );
 }
