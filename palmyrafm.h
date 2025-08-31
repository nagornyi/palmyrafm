/****************************************************************************
** palmyrafm.h
*****************************************************************************/

#ifndef PALMYRAFM_H
#define PALMYRAFM_H

#include <QMainWindow>
#include <QListView>
#include <QTreeView>
#include <QWidget>
#include <QDrag>
#include <QStandardItem>
#include <QFileSystemModel>
#include <QProgressBar>
#include <QLabel>
#include <QComboBox>
#include <QToolButton>
#include <QTimer>
#include <QProcess>
#include <QMimeData>
#include <QDir>
#include <QFileInfo>
#include <QProgressDialog>
#include <QClipboard>
#include <QInputDialog>
#include <QLineEdit>
#include <QSizePolicy>
#include <QKeyEvent>

// Forward declarations
class QtFileIconView;
class DirectoryView;
class Copier;

/*****************************************************************************
 *
 * FileMainWindow - Main application window
 *
 *****************************************************************************/

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
    virtual void keyPressEvent(QKeyEvent *event) override;
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
    void goHome();
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
    void pathEditFinished();
    void enableUp();
    void disableUp();
    void enableMkdir();
    void disableMkdir();

private:
    QStringList copiedFiles;
    bool isCutOperation;
    
    bool copyDirectoryRecursively(const QString &sourceDir, const QString &targetDir, bool moveOperation = false);
};

/*****************************************************************************
 *
 * Copier - Helper class for file operations
 *
 *****************************************************************************/

class Copier : public QWidget
{
    Q_OBJECT

public:
    Copier();
    ~Copier() 
    {
        delete proc;
    }
    void copy();

private:
    QProcess *proc;
};

/*****************************************************************************
 *
 * QtFileIconDrag - drag and drop
 *
 *****************************************************************************/

class QtFileIconDrag : public QDrag
{
    Q_OBJECT

public:
    QtFileIconDrag( QWidget * dragSource, QObject* parent = nullptr );
    static bool canDecode( const QMimeData* e );
    void setUrls( const QStringList &urls );

private:
    QStringList urls;
};

/*****************************************************************************
 *
 * QtFileIconView - File list view using QListView
 *
 *****************************************************************************/

class QtFileIconView : public QListView
{
    Q_OBJECT

public:
    QtFileIconView( const QString &dir, QWidget *parent = nullptr );
    enum ViewMode { Large, Detail };
    void setViewMode( ViewMode m );
    ViewMode viewMode() const { return vm; }
    QDir currentDir();
    void itemDoubleClicked( const QModelIndex &index );

public slots:
    void setDirectory( const QString &dir );
    void setDirectory( const QDir &dir );
    void newDirectory();
    void cut_prev();
    void copy_prev();
    void rename_prev();
    void remove_prev();
    void updateonce();
    void cut_fin( QModelIndex item );
    void copy_fin( QModelIndex item );
    void rename_fin( QModelIndex item );
    void remove_fin( QModelIndex item );
    void paste();

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
    void slotDropped( QDropEvent *e );
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
    void arrangeItemsInGrid();
    void slotRightPressed( const QModelIndex &index );
    void openFolder();
    void regupdate();

protected:
    virtual QDrag *dragObject();
    virtual void keyPressEvent( QKeyEvent *e );
    
    QFileSystemModel *fileModel;
    QDir viewDir;
    int newFolderNum;
    ViewMode vm;
    void *openItem; // placeholder

private:
    QProcess *proc1;
    QTimer *internalTimer;
};

/*****************************************************************************
 *
 * DirectoryView - directory tree view
 *
 *****************************************************************************/

class DirectoryView : public QTreeView
{
    Q_OBJECT

public:
    DirectoryView( QWidget *parent = nullptr, bool sdo = false );
    bool showDirsOnly() { return dirsOnly; }

public slots:
    void setDir( const QString & );

signals:
    void folderSelected( const QString & );

protected slots:
    void slotFolderSelected( const QModelIndex &index );

private:
    bool dirsOnly;
    QFileSystemModel *model;
};

#endif // PALMYRAFM_H
