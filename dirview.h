/****************************************************************************
** $Id: palmyrafm/dirview.h   1.0   edited Jan 4 00:25 $
**
** Copyright (C) 2005 Artem Nahorny.    All rights reserved.
**
** This file is part of the Palmyra File Manager.  This program
** may be used and distributed under the GPL v.2.
**
*****************************************************************************/

/****************************************************************************
** Курсова робота
** студента групи П-01-51 ІП "Стратегія"
** Нагорного Артема
** з дисципліни "Основи Об"єктно Орієнтованого Програмування"
** 
** Тема:
** Створення файлового менеджера під ОС Linux
*****************************************************************************/

#ifndef DIRVIEW_H
#define DIRVIEW_H

// включення стандартних бібліотек
#include <qlistview.h>
#include <qstring.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtimer.h>

// оголошення класів програми
class QWidget;
class QDragEnterEvent;
class QDragMoveEvent;
class QDragLeaveEvent;
class QDropEvent;

/*****************************************************************************
 *
 * Class FileItem and its methods declaration
 *
 *****************************************************************************/

// оголошення класу FileItem та його методів, змінних і констант
class FileItem : public QListViewItem
{
public:
    FileItem( QListViewItem *parent, const QString &s1, const QString &s2 )
    : QListViewItem( parent, s1, s2 ), pix( 0 ) {}

    const QPixmap *pixmap( int i ) const;
#if !defined(Q_NO_USING_KEYWORD)
    using QListViewItem::setPixmap;
#endif
    void setPixmap( QPixmap *p );

private:
    QPixmap *pix;
};

/*****************************************************************************
 *
 * Class Directory and its methods declaration
 *
 *****************************************************************************/

// оголошення класу Directory та його методів, змінних і констант
class Directory : public QListViewItem
{
public:
    Directory( QListView * parent, const QString& filename );
    Directory( Directory * parent, const QString& filename, const QString &col2 )
    : QListViewItem( parent, filename, col2 ), pix( 0 ) {}
    Directory( Directory * parent, const QString& filename );

    QString text( int column ) const;

    QString fullName();

    void setOpen( bool );
    void setup();

    const QPixmap *pixmap( int i ) const;
#if !defined(Q_NO_USING_KEYWORD)
    using QListViewItem::setPixmap;
#endif
    void setPixmap( QPixmap *p );

private:
    QFile f;
    Directory * p;
    bool readable;
    bool showDirsOnly;
    QPixmap *pix;

};

/*****************************************************************************
 *
 * Class DirectoryView and its methods declaration
 *
 *****************************************************************************/

// оголошення класу DirectoryView та його методів, змінних і констант
class DirectoryView : public QListView
{
    Q_OBJECT

public:
    DirectoryView( QWidget *parent = 0, const char *name = 0, bool sdo = FALSE );
    bool showDirsOnly() { return dirsOnly; }

public slots:
    void setDir( const QString & );

signals:
    void folderSelected( const QString & );

protected slots:
    void slotFolderSelected( QListViewItem * );
    void openFolder();

protected:
    void contentsDragEnterEvent( QDragEnterEvent *e );
    void contentsDragMoveEvent( QDragMoveEvent *e );
    void contentsDragLeaveEvent( QDragLeaveEvent *e );
    void contentsDropEvent( QDropEvent *e );
    void contentsMouseMoveEvent( QMouseEvent *e );
    void contentsMousePressEvent( QMouseEvent *e );
    void contentsMouseReleaseEvent( QMouseEvent *e );

private:
    QString fullPath(QListViewItem* item);
    bool dirsOnly;
    QListViewItem *oldCurrent;
    QListViewItem *dropItem;
    QTimer* autoopen_timer;
    QPoint presspos;
    bool mousePressed;
};

#endif
