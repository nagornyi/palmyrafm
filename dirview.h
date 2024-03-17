/****************************************************************************
** Copyright (C) 2005 Artem Nagornyi. All rights reserved
**
** This file is part of Palmyra File Manager. This program
** may be used and distributed under the GPL v2
*****************************************************************************/

#ifndef DIRVIEW_H
#define DIRVIEW_H

#include <QApplication>
#include <QListView>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QPoint>
#include <QPixmap>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMouseEvent>

class QWidget;
class QDragEnterEvent;
class QDragMoveEvent;
class QDragLeaveEvent;
class QDropEvent;
class QMouseEvent;

/*****************************************************************************
 *
 * Class FileItem and its methods declaration
 *
 *****************************************************************************/

// Declaration of class FileItem and its methods, variables, and constants
class FileItem : public QStandardItem
{
public:
    FileItem(QStandardItem *parent, const QString &s1, const QString &s2)
        : QStandardItem(s1 + " " + s2), pix(nullptr) {}

    const QPixmap *pixmap() const { return pix; }
    void setPixmap(QPixmap *p) { pix = p; }

private:
    QPixmap *pix;
};

/*****************************************************************************
 *
 * Class Directory and its methods declaration
 *
 *****************************************************************************/

// Declaration of class Directory and its methods, variables, and constants
class Directory : public QStandardItem
{
public:
    Directory(QStandardItem *parent, const QString &filename)
        : QStandardItem(filename), pix(nullptr) {}

    QString text() const { return QStandardItem::text(); }

    QString fullName() const { return text(); }

    const QPixmap *pixmap() const { return pix; }
    void setPixmap(QPixmap *p) { pix = p; }

private:
    QPixmap *pix;
};

/*****************************************************************************
 *
 * Class DirectoryView and its methods declaration
 *
 *****************************************************************************/

// Declaration of class DirectoryView and its methods, variables, and constants
class DirectoryView : public QListView
{
    Q_OBJECT

public:
    DirectoryView(QWidget *parent = nullptr, const char *name = nullptr, bool sdo = false);
    bool showDirsOnly() { return dirsOnly; }

public slots:
    void setDir(const QString &);

signals:
    void folderSelected(const QString &);

protected slots:
    void slotFolderSelected(QStandardItem *);
    void openFolder();

protected:
    void contentsDragEnterEvent(QDragEnterEvent *e);
    void contentsDragMoveEvent(QDragMoveEvent *e);
    void contentsDragLeaveEvent(QDragLeaveEvent *e);
    void contentsDropEvent(QDropEvent *e);
    void contentsMouseMoveEvent(QMouseEvent *e);
    void contentsMousePressEvent(QMouseEvent *e);
    void contentsMouseReleaseEvent(QMouseEvent *e);

private:
    QString fullPath(QStandardItem *item);
    bool dirsOnly;
    QStandardItem *oldCurrent;
    QStandardItem *dropItem;
    QTimer *autoopen_timer;
    QPoint presspos;
    bool mousePressed;
};

#endif
