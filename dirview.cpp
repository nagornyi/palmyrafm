/****************************************************************************
** dirview.cpp
*****************************************************************************/

#include "palmyrafm.h"
#include <QFileSystemModel>
#include <QHeaderView>

DirectoryView::DirectoryView(QWidget *parent, bool sdo)
    : QTreeView(parent), dirsOnly(sdo)
{
    model = new QFileSystemModel(this);
    model->setRootPath("/");
    
    if (dirsOnly) {
        model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    }
    
    setModel(model);
    setRootIndex(model->index("/"));
    
    // Hide size, type, and date columns for directory view
    hideColumn(1);
    hideColumn(2);
    hideColumn(3);
    
    connect(this, &QTreeView::clicked, this, &DirectoryView::slotFolderSelected);
}

void DirectoryView::setDir(const QString &path)
{
    setRootIndex(model->index(path));
}

void DirectoryView::slotFolderSelected(const QModelIndex &index)
{
    if (model->isDir(index)) {
        QString path = model->filePath(index);
        emit folderSelected(path);
    }
}
