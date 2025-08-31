/****************************************************************************
** palmyrafm - Palmyra File Manager
*****************************************************************************/

#include "palmyrafm.h"

#include <QApplication>
#include <QSplitter>
#include <QProgressBar>
#include <QLabel>
#include <QStatusBar>
#include <QToolBar>
#include <QComboBox>
#include <QToolButton>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QPainter>
#include <QStringList>
#include <QPixmap>
#include <QMimeData>
#include <QDrag>
#include <QMessageBox>
#include <QKeyEvent>
#include <QMenu>
#include <QCursor>
#include <QTransform>
#include <QProcess>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QUrl>
#include <QIcon>
#include <QFileSystemModel>
#include <QProgressDialog>
#include <QClipboard>
#include <QInputDialog>
#include <QLineEdit>
#include <QThread>
#include <cstdlib>

/*****************************************************************************
 *
 * FileMainWindow Implementation
 *
 *****************************************************************************/

FileMainWindow::FileMainWindow() 
: QMainWindow(), isCutOperation(false)
{
    setup();
}

void FileMainWindow::show()
{
    QMainWindow::show();
}

void FileMainWindow::setup()
{
    // Create central splitter widget
    QSplitter *splitter = new QSplitter(this);
    
    // Create directory tree view (left panel)
    dirlist = new DirectoryView(splitter, true);
    
    // Create file list view (right panel) 
    fileview = new QtFileIconView("/", splitter);
    fileview->setSelectionMode(QAbstractItemView::ExtendedSelection);
    
    setCentralWidget(splitter);
    
    // Create toolbar
    QToolBar *toolbar1 = addToolBar("Operations");
    
    // Up button
    upButton = new QToolButton();
    upButton->setText("Up");
    upButton->setToolTip("Go Up");
    connect(upButton, &QToolButton::clicked, this, &FileMainWindow::cdUp);
    toolbar1->addWidget(upButton);
    
    // Home button
    QToolButton *homeButton = new QToolButton();
    homeButton->setText("Home");
    homeButton->setToolTip("Go to Home Directory");
    connect(homeButton, &QToolButton::clicked, this, &FileMainWindow::goHome);
    toolbar1->addWidget(homeButton);
    
    // New folder button
    mkdirButton = new QToolButton();
    mkdirButton->setText("New Folder");
    mkdirButton->setToolTip("New Folder");
    connect(mkdirButton, &QToolButton::clicked, this, &FileMainWindow::newFolder);
    toolbar1->addWidget(mkdirButton);
    
    toolbar1->addSeparator();
    
    // File operations
    QToolButton *cutButton = new QToolButton();
    cutButton->setText("Cut");
    cutButton->setToolTip("Cut selected files");
    connect(cutButton, &QToolButton::clicked, this, &FileMainWindow::cut);
    toolbar1->addWidget(cutButton);
    
    QToolButton *copyButton = new QToolButton();
    copyButton->setText("Copy");
    copyButton->setToolTip("Copy selected files");
    connect(copyButton, &QToolButton::clicked, this, &FileMainWindow::copy);
    toolbar1->addWidget(copyButton);
    
    QToolButton *pasteButton = new QToolButton();
    pasteButton->setText("Paste");
    pasteButton->setToolTip("Paste files");
    connect(pasteButton, &QToolButton::clicked, this, &FileMainWindow::paste);
    toolbar1->addWidget(pasteButton);
    
    QToolButton *deleteButton = new QToolButton();
    deleteButton->setText("Delete");
    deleteButton->setToolTip("Delete selected files");
    connect(deleteButton, &QToolButton::clicked, this, &FileMainWindow::remove);
    toolbar1->addWidget(deleteButton);
    
    // Path toolbar
    QToolBar *pathToolbar = addToolBar("Path");
    pathToolbar->addWidget(new QLabel("Path: "));
    
    pathCombo = new QComboBox();
    pathCombo->setEditable(true);
    pathCombo->setMinimumWidth(300);
    pathCombo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pathCombo->setInsertPolicy(QComboBox::NoInsert);
    
    // Connect path navigation
    connect(pathCombo, QOverload<const QString &>::of(&QComboBox::textActivated),
            this, &FileMainWindow::changePath);
    connect(pathCombo->lineEdit(), &QLineEdit::returnPressed,
            this, &FileMainWindow::pathEditFinished);
    
    pathToolbar->addWidget(pathCombo);
    
    // Connect signals - use overloaded function pointers to resolve ambiguity
    connect(dirlist, &DirectoryView::folderSelected,
            fileview, QOverload<const QString &>::of(&QtFileIconView::setDirectory));
    connect(fileview, &QtFileIconView::directoryChanged,
            this, &FileMainWindow::directoryChanged);
    
    // Status bar
    label = new QLabel(statusBar());
    statusBar()->addWidget(label);
    progress = new QProgressBar(statusBar());
    statusBar()->addWidget(progress);
}

void FileMainWindow::setPathCombo()
{
    QString dir = windowTitle();
    pathCombo->clear();
    
    // Add current directory
    pathCombo->addItem(dir);
    
    // Add parent directories for quick navigation
    QDir currentDir(dir);
    QString parentPath = currentDir.absolutePath();
    while (currentDir.cdUp()) {
        parentPath = currentDir.absolutePath();
        if (parentPath != dir && parentPath != "/") {
            pathCombo->addItem(parentPath);
        }
        if (parentPath == "/") {
            pathCombo->addItem("/");
            break;
        }
    }
    
    pathCombo->setCurrentIndex(0);
    pathCombo->setToolTip(QString("Current path: %1\nClick dropdown for parent directories").arg(dir));
    
    // Set the line edit text to show the full path
    pathCombo->lineEdit()->setText(dir);
    pathCombo->lineEdit()->setCursorPosition(pathCombo->lineEdit()->text().length());
}

void FileMainWindow::directoryChanged(const QString &dir)
{
    setWindowTitle(dir);
    setPathCombo();
}

void FileMainWindow::slotStartReadDir(int dirs)
{
    progress->setMaximum(dirs);
    progress->setValue(0);
}

void FileMainWindow::slotReadNextDir()
{
    progress->setValue(progress->value() + 1);
}

void FileMainWindow::slotReadDirDone()
{
    progress->setValue(progress->maximum());
}

void FileMainWindow::cdUp()
{
    QString currentPath = fileview->currentDir().absolutePath();
    QDir parent = QDir(currentPath).absolutePath();
    parent.cdUp();
    fileview->setDirectory(parent.absolutePath());
}

void FileMainWindow::goHome()
{
    QString homePath = QDir::homePath();
    fileview->setDirectory(homePath);
}

void FileMainWindow::newFolder()
{
    bool ok;
    QString name = QInputDialog::getText(this, "New Folder", 
                                       "Enter folder name:", QLineEdit::Normal, 
                                       "New Folder", &ok);
    if (ok && !name.isEmpty()) {
        QString currentPath = fileview->currentDir().absolutePath();
        QString newFolderPath = currentPath + "/" + name;
        
        QDir dir;
        if (dir.mkpath(newFolderPath)) {
            fileview->updateonce();
            QMessageBox::information(this, "Success", "Folder created successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to create folder!");
        }
    }
}

void FileMainWindow::cut()
{
    QModelIndexList selected = fileview->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::information(this, "Cut", "No files selected!");
        return;
    }
    
    copiedFiles.clear();
    QFileSystemModel* model = qobject_cast<QFileSystemModel*>(fileview->model());
    
    for (const QModelIndex &index : selected) {
        if (index.column() == 0) { // Only process the first column to avoid duplicates
            QString filePath = model->filePath(index);
            copiedFiles << filePath;
        }
    }
    
    isCutOperation = true;
    
    // Store in clipboard for external apps
    QClipboard *clipboard = QApplication::clipboard();
    QMimeData *mimeData = new QMimeData;
    QList<QUrl> urls;
    for (const QString &path : copiedFiles) {
        urls << QUrl::fromLocalFile(path);
    }
    mimeData->setUrls(urls);
    clipboard->setMimeData(mimeData);
    
    label->setText(QString("Cut %1 file(s)").arg(copiedFiles.size()));
}

void FileMainWindow::copy()
{
    QModelIndexList selected = fileview->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::information(this, "Copy", "No files selected!");
        return;
    }
    
    copiedFiles.clear();
    QFileSystemModel* model = qobject_cast<QFileSystemModel*>(fileview->model());
    
    for (const QModelIndex &index : selected) {
        if (index.column() == 0) { // Only process the first column to avoid duplicates
            QString filePath = model->filePath(index);
            copiedFiles << filePath;
        }
    }
    
    isCutOperation = false;
    
    // Store in clipboard for external apps
    QClipboard *clipboard = QApplication::clipboard();
    QMimeData *mimeData = new QMimeData;
    QList<QUrl> urls;
    for (const QString &path : copiedFiles) {
        urls << QUrl::fromLocalFile(path);
    }
    mimeData->setUrls(urls);
    clipboard->setMimeData(mimeData);
    
    label->setText(QString("Copied %1 file(s)").arg(copiedFiles.size()));
}

void FileMainWindow::paste()
{
    if (copiedFiles.isEmpty()) {
        QMessageBox::information(this, "Paste", "No files to paste!");
        return;
    }
    
    QString targetDir = fileview->currentDir().absolutePath();
    
    // Create progress dialog
    QProgressDialog *progressDialog = new QProgressDialog(this);
    progressDialog->setWindowTitle(isCutOperation ? "Moving Files..." : "Copying Files...");
    progressDialog->setLabelText("Preparing file operation...");
    progressDialog->setRange(0, copiedFiles.size());
    progressDialog->setValue(0);
    progressDialog->setModal(true);
    progressDialog->show();
    
    QApplication::processEvents();
    
    bool success = true;
    int processed = 0;
    
    for (const QString &sourcePath : copiedFiles) {
        if (progressDialog->wasCanceled()) {
            success = false;
            break;
        }
        
        QFileInfo sourceInfo(sourcePath);
        QString targetPath = targetDir + "/" + sourceInfo.fileName();
        
        // Handle name conflicts
        int counter = 1;
        QString baseName = sourceInfo.baseName();
        QString extension = sourceInfo.completeSuffix();
        QString originalTargetPath = targetPath;
        
        while (QFile::exists(targetPath)) {
            if (sourceInfo.isDir()) {
                targetPath = targetDir + "/" + baseName + QString("_%1").arg(counter);
            } else {
                targetPath = targetDir + "/" + baseName + QString("_%1").arg(counter) + 
                           (extension.isEmpty() ? "" : "." + extension);
            }
            counter++;
        }
        
        progressDialog->setLabelText(QString("%1: %2")
                                   .arg(isCutOperation ? "Moving" : "Copying")
                                   .arg(sourceInfo.fileName()));
        
        if (sourceInfo.isDir()) {
            // Copy/move directory recursively
            success = copyDirectoryRecursively(sourcePath, targetPath, isCutOperation);
        } else {
            // Copy/move file
            if (isCutOperation) {
                success = QFile::rename(sourcePath, targetPath);
            } else {
                success = QFile::copy(sourcePath, targetPath);
            }
        }
        
        if (!success) {
            QMessageBox::warning(this, "Error", 
                                QString("Failed to %1 %2")
                                .arg(isCutOperation ? "move" : "copy")
                                .arg(sourceInfo.fileName()));
            break;
        }
        
        processed++;
        progressDialog->setValue(processed);
        QApplication::processEvents();
    }
    
    progressDialog->close();
    delete progressDialog;
    
    if (success) {
        QString operation = isCutOperation ? "moved" : "copied";
        label->setText(QString("Successfully %1 %2 file(s)").arg(operation).arg(processed));
        
        if (isCutOperation) {
            copiedFiles.clear(); // Clear after successful move
        }
        
        fileview->updateonce();
    }
}

void FileMainWindow::rename()
{
    QMessageBox::information(this, "Rename", "Rename functionality");
}

void FileMainWindow::remove()
{
    QModelIndexList selected = fileview->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::information(this, "Delete", "No files selected!");
        return;
    }
    
    QStringList filesToDelete;
    QFileSystemModel* model = qobject_cast<QFileSystemModel*>(fileview->model());
    
    for (const QModelIndex &index : selected) {
        if (index.column() == 0) { // Only process the first column to avoid duplicates
            QString filePath = model->filePath(index);
            filesToDelete << filePath;
        }
    }
    
    // Confirmation dialog
    int ret = QMessageBox::question(this, "Confirm Delete", 
                                   QString("Are you sure you want to delete %1 file(s)?")
                                   .arg(filesToDelete.size()),
                                   QMessageBox::Yes | QMessageBox::No,
                                   QMessageBox::No);
    
    if (ret != QMessageBox::Yes) {
        return;
    }
    
    // Create progress dialog
    QProgressDialog *progressDialog = new QProgressDialog(this);
    progressDialog->setWindowTitle("Deleting Files...");
    progressDialog->setLabelText("Preparing deletion...");
    progressDialog->setRange(0, filesToDelete.size());
    progressDialog->setValue(0);
    progressDialog->setModal(true);
    progressDialog->show();
    
    QApplication::processEvents();
    
    bool success = true;
    int processed = 0;
    
    for (const QString &filePath : filesToDelete) {
        if (progressDialog->wasCanceled()) {
            success = false;
            break;
        }
        
        QFileInfo fileInfo(filePath);
        progressDialog->setLabelText(QString("Deleting: %1").arg(fileInfo.fileName()));
        
        if (fileInfo.isDir()) {
            QDir dir(filePath);
            success = dir.removeRecursively();
        } else {
            QFile file(filePath);
            success = file.remove();
        }
        
        if (!success) {
            QMessageBox::warning(this, "Error", 
                                QString("Failed to delete %1").arg(fileInfo.fileName()));
            break;
        }
        
        processed++;
        progressDialog->setValue(processed);
        QApplication::processEvents();
    }
    
    progressDialog->close();
    delete progressDialog;
    
    if (success) {
        label->setText(QString("Successfully deleted %1 file(s)").arg(processed));
        fileview->updateonce();
    }
}

void FileMainWindow::update()
{
    fileview->updateonce();
}

void FileMainWindow::updateonce()
{
    fileview->updateonce();
}

void FileMainWindow::about()
{
    QMessageBox::about(this, "About Palmyra FM", 
                       "PalmyraFM is a simple, two-pane file manager for Linux"
                       "by Artem Nagornyi (2025)");
}

void FileMainWindow::changePath(const QString &path)
{
    fileview->setDirectory(path);
}

void FileMainWindow::pathEditFinished()
{
    QString newPath = pathCombo->lineEdit()->text();
    QDir dir(newPath);
    
    if (dir.exists()) {
        fileview->setDirectory(dir.absolutePath());
    } else {
        // Reset to current directory if invalid path
        pathCombo->lineEdit()->setText(fileview->currentDir().absolutePath());
        QMessageBox::warning(this, "Invalid Path", 
                           QString("Path does not exist: %1").arg(newPath));
    }
}

void FileMainWindow::enableUp()
{
    upButton->setEnabled(true);
}

void FileMainWindow::disableUp()
{
    upButton->setEnabled(false);
}

void FileMainWindow::enableMkdir()
{
    mkdirButton->setEnabled(true);
}

void FileMainWindow::disableMkdir()
{
    mkdirButton->setEnabled(false);
}

bool FileMainWindow::copyDirectoryRecursively(const QString &sourceDir, const QString &targetDir, bool moveOperation)
{
    QDir source(sourceDir);
    QDir target(targetDir);
    
    if (!target.exists()) {
        if (!target.mkpath(".")) {
            return false;
        }
    }
    
    QStringList files = source.entryList(QDir::Files | QDir::NoDotAndDotDot);
    for (const QString &file : files) {
        QString sourcePath = source.absoluteFilePath(file);
        QString targetPath = target.absoluteFilePath(file);
        
        if (moveOperation) {
            if (!QFile::rename(sourcePath, targetPath)) {
                return false;
            }
        } else {
            if (!QFile::copy(sourcePath, targetPath)) {
                return false;
            }
        }
    }
    
    QStringList subdirs = source.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &subdir : subdirs) {
        QString sourceSubDir = source.absoluteFilePath(subdir);
        QString targetSubDir = target.absoluteFilePath(subdir);
        
        if (!copyDirectoryRecursively(sourceSubDir, targetSubDir, moveOperation)) {
            return false;
        }
    }
    
    // If it's a move operation, remove the source directory after copying
    if (moveOperation) {
        return source.removeRecursively();
    }
    
    return true;
}

/*****************************************************************************
 *
 * Copier Implementation
 *
 *****************************************************************************/

Copier::Copier() : QWidget()
{
    proc = new QProcess(this);
}

void Copier::copy()
{
    QStringList args;
    args << "/sample.art";
    proc->start("kwrite", args);
}

/*****************************************************************************
 *
 * QtFileIconDrag Implementation
 *
 *****************************************************************************/

QtFileIconDrag::QtFileIconDrag(QWidget *dragSource, QObject *parent)
    : QDrag(dragSource)
{
    Q_UNUSED(parent)
    QMimeData *mimeData = new QMimeData;
    setMimeData(mimeData);
}

bool QtFileIconDrag::canDecode(const QMimeData *e)
{
    return e->hasUrls();
}

void QtFileIconDrag::setUrls(const QStringList &urlList)
{
    urls = urlList;
    QList<QUrl> urlObjects;
    for (const QString &url : urlList) {
        urlObjects << QUrl::fromLocalFile(url);
    }
    mimeData()->setUrls(urlObjects);
}

/*****************************************************************************
 *
 * QtFileIconView Implementation using QListView
 *
 *****************************************************************************/

QtFileIconView::QtFileIconView(const QString &dir, QWidget *parent)
    : QListView(parent), vm(Large), openItem(nullptr)
{
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(dir);
    setModel(fileModel);
    setRootIndex(fileModel->index(dir));
    
    viewDir = QDir(dir);
    newFolderNum = 1;
    
    proc1 = new QProcess(this);
    internalTimer = new QTimer(this);
    
    connect(this, &QAbstractItemView::doubleClicked, 
            this, &QtFileIconView::itemDoubleClicked);
    
    setDragDropMode(QAbstractItemView::DragDrop);
    setAcceptDrops(true);
}

void QtFileIconView::setViewMode(ViewMode m)
{
    vm = m;
    if (m == Large) {
        QListView::setViewMode(QListView::IconMode);
        setIconSize(QSize(48, 48));
    } else {
        QListView::setViewMode(QListView::ListMode);
        setIconSize(QSize(16, 16));
    }
}

void QtFileIconView::setDirectory(const QString &dir)
{
    viewDir = QDir(dir);
    setRootIndex(fileModel->index(dir));
    emit directoryChanged(dir);
    
    if (dir == "/") {
        emit disableUp();
    } else {
        emit enableUp();
    }
    
    emit enableMkdir();
}

void QtFileIconView::setDirectory(const QDir &dir)
{
    setDirectory(dir.absolutePath());
}

QDir QtFileIconView::currentDir()
{
    return viewDir;
}

void QtFileIconView::itemDoubleClicked(const QModelIndex &index)
{
    if (fileModel->isDir(index)) {
        QString path = fileModel->filePath(index);
        setDirectory(path);
    } else {
        // Open file
        QString filePath = fileModel->filePath(index);
        QProcess::startDetached("xdg-open", QStringList() << filePath);
    }
}

void QtFileIconView::newDirectory()
{
    QMessageBox::information(this, "New Directory", "New directory functionality");
}

void QtFileIconView::updateonce()
{
    // QFileSystemModel refreshes automatically, but we can force it
    QString currentPath = viewDir.absolutePath();
    setDirectory(currentPath);
}

void QtFileIconView::cut_prev()
{
    QMessageBox::information(this, "Cut", "Cut operation");
}

void QtFileIconView::copy_prev()
{
    QMessageBox::information(this, "Copy", "Copy operation");
}

void QtFileIconView::rename_prev()
{
    QMessageBox::information(this, "Rename", "Rename operation");
}

void QtFileIconView::remove_prev()
{
    QMessageBox::information(this, "Remove", "Remove operation");
}

void QtFileIconView::paste()
{
    QMessageBox::information(this, "Paste", "Paste operation");
}

void QtFileIconView::cut_fin(QModelIndex item)
{
    Q_UNUSED(item)
}

void QtFileIconView::copy_fin(QModelIndex item)
{
    Q_UNUSED(item)
}

void QtFileIconView::rename_fin(QModelIndex item)
{
    Q_UNUSED(item)
}

void QtFileIconView::remove_fin(QModelIndex item)
{
    Q_UNUSED(item)
}

void QtFileIconView::slotDropped(QDropEvent *e)
{
    Q_UNUSED(e)
    QMessageBox::information(this, "Drop", "Drop operation");
}

void QtFileIconView::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_N && (e->modifiers() & Qt::ControlModifier)) {
        newDirectory();
    } else {
        QListView::keyPressEvent(e);
    }
}

QDrag *QtFileIconView::dragObject()
{
    // Drag implementation
    QtFileIconDrag *drag = new QtFileIconDrag(this);
    QStringList urls;
    
    QModelIndexList selected = selectedIndexes();
    for (const QModelIndex &index : selected) {
        urls << fileModel->filePath(index);
    }
    
    drag->setUrls(urls);
    return drag;
}

// Placeholder implementations for various slots
void QtFileIconView::viewLarge() { setViewMode(Large); }
void QtFileIconView::viewDetail() { setViewMode(Detail); }
void QtFileIconView::viewBottom() { }
void QtFileIconView::viewRight() { }
void QtFileIconView::flowEast() { }
void QtFileIconView::flowSouth() { }
void QtFileIconView::itemTextTruncate() { }
void QtFileIconView::itemTextWordWrap() { }
void QtFileIconView::sortAscending() { fileModel->sort(0, Qt::AscendingOrder); }
void QtFileIconView::sortDescending() { fileModel->sort(0, Qt::DescendingOrder); }
void QtFileIconView::arrangeItemsInGrid() { }
void QtFileIconView::slotRightPressed(const QModelIndex &index) { Q_UNUSED(index) }
void QtFileIconView::openFolder() { }
void QtFileIconView::regupdate() { updateonce(); }
