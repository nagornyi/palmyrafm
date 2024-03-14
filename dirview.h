/****************************************************************************
** Copyright (C) 2005 Artem Nagornyi. All rights reserved
**
** This file is part of Palmyra File Manager. This program
** may be used and distributed under the GPL v2
*****************************************************************************/

#ifndef DIRVIEW_H
#define DIRVIEW_H

#include <QListView>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QPoint>
#include <QPixmap>
#include <QListViewItem>
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
class FileItem : public QListViewItem
{
public:
  FileItem(QListViewItem *parent, const QString &s1, const QString &s2)
    : QListViewItem(parent, s1, s2), pix(0) {}

  const QPixmap *pixmap(int i) const;
  void setPixmap(QPixmap *p);

private:
  QPixmap *pix;
};

/*****************************************************************************
 *
 * Class Directory and its methods declaration
 *
 *****************************************************************************/

// Declaration of class Directory and its methods, variables, and constants
class Directory : public QListViewItem
{
public:
  Directory(QListView *parent, const QString &filename);
  Directory(Directory *parent, const QString &filename, const QString &col2)
    : QListViewItem(parent, filename, col2), pix(0) {}
  Directory(Directory *parent, const QString &filename);

  QString text(int column) const;

  QString fullName();

  void setOpen(bool);
  void setup();

  const QPixmap *pixmap(int i) const;
  void setPixmap(QPixmap *p);

private:
  QFile f;
  Directory *p;
  bool readable;
  bool showDirsOnly;
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
  void slotFolderSelected(QListViewItem *);
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
  QString fullPath(QListViewItem *item);
  bool dirsOnly;
  QListViewItem *oldCurrent;
  QListViewItem *dropItem;
  QTimer *autoopen_timer;
  QPoint presspos;
  bool mousePressed;
};

#endif
