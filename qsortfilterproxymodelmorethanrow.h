#ifndef QSORTFILTERPROXYMODELMORETHANROW_H
#define QSORTFILTERPROXYMODELMORETHANROW_H

#include <QtSql>

class QSortFilterProxyModelMoreThanRow : public QSortFilterProxyModel
{
public:
     QSortFilterProxyModelMoreThanRow(QObject *parent = 0);
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif // QSORTFILTERPROXYMODELMORETHANROW_H
