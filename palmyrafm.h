/****************************************************************************
** palmyrafm.h
*****************************************************************************/

#ifndef PALMYRAFM_H
#define PALMYRAFM_H

#include <QMainWindow>
#include <QTreeView>
#include <QHeaderView>
#include <QWidget>
#include <QDrag>
#include <QStandardItem>
#include <QFileSystemModel>
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
#include <QSplitter>
#include <QMenu>
#include <QCursor>
#include <QSortFilterProxyModel>
#include <QStyledItemDelegate>
#include <QPainter>

// Forward declarations
class QtFileIconView;
class Copier;
class FileSortProxyModel;
class FileItemDelegate;

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
    QtFileIconView *fileView() { return activePane == leftPane ? leftPane : rightPane; }
    void show();
    
protected:
    void setup();
    void setPathCombo();
    void applyTheme(const QString &themeName);
    void updatePaneStyles();
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual bool eventFilter(QObject *obj, QEvent *event) override;
    QtFileIconView *leftPane;
    QtFileIconView *rightPane;
    QtFileIconView *activePane;
    QLabel *label;
    QLineEdit *leftPathEdit;  
    QLineEdit *rightPathEdit;
    QToolButton *upButton, *mkdirButton;
    QList<QToolButton*> toolbarButtons;  // All toolbar buttons for font updates
    QString currentTheme;
    QString currentPaneStyle;
    int leftPaneSelectedRow;
    int rightPaneSelectedRow;
    int currentFontSize;

    // Colors for active/inactive path displays
    QString activePathColor;
    QString inactivePathColor;
    QString pathTextColor;
    QString pathBorderColor;
    
    // File type colors for MC-style display
    QString fileColorDir;
    QString fileColorExec;
    QString fileColorArchive;
    QString fileColorImage;
    QString fileColorVideo;
    QString fileColorAudio;
    QString fileColorDoc;
    QString fileColorDefault;

protected slots:
    void leftPaneClicked(const QModelIndex &index);
    void rightPaneClicked(const QModelIndex &index);
    void leftPaneDirectoryChanged(const QString &path);
    void rightPaneDirectoryChanged(const QString &path);
    void cdUp();
    void goHome();
    void newFolder();
    void cut();
    void copy();
    void paste();
    void pasteToActive();
    void copyToOpposite();
    void moveToOpposite();
    void rename();
    void remove();
    void selectByPattern();
    void about();
    void showAppearanceMenu();

private:
    QStringList copiedFiles;
    bool isCutOperation;
    QString leftPaneCurrentDir;
    QString rightPaneCurrentDir;
    
    void activatePane(QtFileIconView *targetPane, int &targetSelectedRow, const QModelIndex &requestedIndex);
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
 * FileItemDelegate - Custom delegate for MC-style file display
 *
 *****************************************************************************/

class FileItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit FileItemDelegate(QObject *parent = nullptr);
    
    void paint(QPainter *painter, const QStyleOptionViewItem &option, 
               const QModelIndex &index) const override;
    
    void setThemeColors(const QString &dirColor, const QString &execColor,
                       const QString &archiveColor, const QString &imageColor,
                       const QString &videoColor, const QString &audioColor,
                       const QString &docColor, const QString &defaultColor);

private:
    QString getFilePrefix(const QFileInfo &fileInfo) const;
    QColor getFileColor(const QFileInfo &fileInfo) const;
    
    // Theme colors
    QString m_dirColor;
    QString m_execColor;
    QString m_archiveColor;
    QString m_imageColor;
    QString m_videoColor;
    QString m_audioColor;
    QString m_docColor;
    QString m_defaultColor;
};

/*****************************************************************************
 *
 * QtFileIconView - File list view using QListView
 *
 *****************************************************************************/

class QtFileIconView : public QTreeView
{
    Q_OBJECT

public:
    QtFileIconView( const QString &dir, QWidget *parent = nullptr );
    QDir currentDir();
    void itemDoubleClicked( const QModelIndex &index );
    QFileSystemModel *fileSystemModel() const { return fileModel; }
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    FileItemDelegate *getDelegate() const { return itemDelegate; }

public slots:
    void setDirectory( const QString &dir );
    void setDirectory( const QDir &dir );
    void newDirectory();

signals:
    void directoryChanged(const QString &path);

protected:
    virtual void keyPressEvent( QKeyEvent *e );
    
    QFileSystemModel *fileModel;
    FileSortProxyModel *proxyModel;
    FileItemDelegate *itemDelegate;
    QDir viewDir;
    int newFolderNum;

private:
    QProcess *proc1;
    QTimer *internalTimer;
};

#endif // PALMYRAFM_H
