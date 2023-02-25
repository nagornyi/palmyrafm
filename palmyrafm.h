/****************************************************************************
** $Id: palmyrafm/palmyrafm.h   1.0   edited Jan 4 00:25 $
**
** Copyright (C) 2005 Artem Nahorny.	All rights reserved.
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

#ifndef PALMYRAFM_H
#define PALMYRAFM_H

// включення стандартних бібліотек
#include <qmainwindow.h>
#include <qiconset.h>
#include <qstring.h>
#include <qfileinfo.h>
#include <qdir.h>
#include <qtimer.h>
#include <qiconview.h>
#include <qprocess.h>
#include <qobject.h>
#include <qvbox.h>

// оголошення класів програми
class QtFileIconView;
class DirectoryView;
class QProgressBar;
class QLabel;
class QComboBox;
class QToolButton;
class QtFileIconView;
class QDragObject;
class QResizeEvent;
class Copier;

/*****************************************************************************
 *
 * Class FileMainWindow and its methods declaration
 *
 *****************************************************************************/

// оголошення класу FileMainWindow та його методів, змінних і констант
class FileMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	FileMainWindow();
	QtFileIconView *fileView() { return fileview; }
	DirectoryView *dirList() { return dirlist; }
	void show();
    
protected:
	void setup();
	void setPathCombo();
	QtFileIconView *fileview;
	DirectoryView *dirlist;
	QProgressBar *progress;
	QLabel *label;
	QComboBox *pathCombo;
	QToolButton *upButton, *mkdirButton;

protected slots:
	void directoryChanged( const QString & );
	void slotStartReadDir( int dirs );
	void slotReadNextDir();
	void slotReadDirDone();
	void cdUp();
	void newFolder();
	void cut();
	void copy();
	void paste();
	void rename();
	void remove();
	void update();
	void updateonce();
	void about();
	void changePath( const QString &path );
	void enableUp();
	void disableUp();
	void enableMkdir();
	void disableMkdir();
};

/*****************************************************************************
 *
 * Class Copier and its methods declaration
 *
 *****************************************************************************/

// оголошення класу Copier та його методів, змінних і констант
class Copier : public QVBox
{
	Q_OBJECT

public:
	Copier();
	~Copier() 
	{
		delete proc;
	};
	void copy();

private:
	QProcess *proc;
};

/*****************************************************************************
 *
 * Class QtFileIconDrag and its methods declaration
 *
 *****************************************************************************/

// оголошення класу QtFileIconDrag та його методів, змінних і констант
class QtFileIconDrag : public QIconDrag
{
	Q_OBJECT

public:
	QtFileIconDrag( QWidget * dragSource, const char* name = 0 );
	const char* format( int i ) const;
	QByteArray encodedData( const char* mime ) const;
	static bool canDecode( QMimeSource* e );
	void append( const QIconDragItem &item, const QRect &pr, const QRect &tr, const QString &url );

private:
    QStringList urls;
};

/*****************************************************************************
 *
 * Class QtFileIconView and its methods declaration
 *
 *****************************************************************************/

// оголошення класу QtFileIconView та його методів, змінних і констант
class QtFileIconViewItem;
class QTimer;
class QtFileIconView : public QIconView
{
	Q_OBJECT

friend class Copier;

public:
	QtFileIconView( const QString &dir, QWidget *parent = 0, const char *name = 0 );
	enum ViewMode { Large, Detail };
	void setViewMode( ViewMode m );
	ViewMode viewMode() const 
	{ 
		return vm; 
	}
	void setOpenItem( QtFileIconViewItem *i ) 
	{
		openItem = i;
	}
	void copy1(QString cpdir);
    

public slots:
	void setDirectory( const QString &dir );
	void setDirectory( const QDir &dir );
	void newDirectory();
	void cut_prev();
	void copy_prev();
	void rename_prev();
	void remove_prev();
	void update();
	void updateonce();
	void cut_fin( QIconViewItem *item );
	void copy_fin( QIconViewItem *item );
	void rename_fin( QIconViewItem *item );
	void remove_fin( QIconViewItem *item );
	void paste();
	QDir currentDir();

private slots:
	void regupdate ();

signals:
	void directoryChanged( const QString & );
	void startReadDir( int dirs );
	void readNextDir();
	void readDirDone();
	void enableUp();
	void disableUp();
	void enableMkdir();
	void disableMkdir();

protected slots:
	void itemDoubleClicked( QIconViewItem *i );
	void slotDropped( QDropEvent *e, const QValueList<QIconDragItem> & );
	void viewLarge();
	void viewDetail();
	void viewBottom();
	void viewRight();
	void flowEast();
	void flowSouth();
	void itemTextTruncate();
	void itemTextWordWrap();
	void sortAscending();
	void sortDescending(); 
	void arrangeItemsInGrid() 
	{
		QIconView::arrangeItemsInGrid( TRUE );
	}

	void slotRightPressed( QIconViewItem *item );
	void openFolder();
    

protected:
	void readDir( const QDir &dir );
	virtual QDragObject *dragObject();
	virtual void keyPressEvent( QKeyEvent *e );
	QDir viewDir;
	int newFolderNum;
  	QSize sz;
   	QPixmap pix;
   	ViewMode vm;
   	QtFileIconViewItem *openItem; 

private:
   	QProcess *proc1;
   	QTimer *internalTimer;
	
};

/*****************************************************************************
 *
 * Class QtFileIconViewItem and its methods declaration
 *
 *****************************************************************************/

// оголошення класу QtFileIconViewItem та його методів, змінних і констант
class QtFileIconViewItem : public QIconViewItem, public Copier
{

friend class QtFileIconView;
friend class FileMainWindow;
friend class Copier;

public:
   	enum ItemType 
	{
       	File = 0,
       	Dir,
       	Link
   	};

   	QtFileIconViewItem( QtFileIconView *parent, QFileInfo *fi );
  	virtual ~QtFileIconViewItem();
	ItemType type() const
   	{ 
		return itemType; 
	}
   	QString filename() const { return itemFileName; }
	virtual bool acceptDrop( const QMimeSource *e ) const;
	virtual void setText( const QString &text );
	virtual QPixmap *pixmap() const;
	virtual void dragEntered();
   	virtual void dragLeft();
	void viewModeChanged( QtFileIconView::ViewMode m );
   	void paintItem( QPainter *p, const QColorGroup &cg );

protected:
   	virtual void dropped( QDropEvent *e, const QValueList<QIconDragItem> & );
   	QString itemFileName;
   	QFileInfo *itemFileInfo;
   	ItemType itemType;
   	bool checkSetText;
   	QTimer timer;
   	QtFileIconView::ViewMode vm;
};


#endif
