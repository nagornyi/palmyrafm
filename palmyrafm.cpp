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
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QDrag>
#include <QMessageBox>
#include <QKeyEvent>
#include <QEvent>
#include <QMenu>
#include <QCursor>
#include <QMouseEvent>
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
#include <QRegularExpression>
#include <QDialog>
#include <QTabWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QPushButton>
#include <QHBoxLayout>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>
#include <cstdlib>

/*****************************************************************************
 *
 * FileMainWindow Implementation
 *
 *****************************************************************************/

FileMainWindow::FileMainWindow() 
: QMainWindow(), leftPaneSelectedRow(0), rightPaneSelectedRow(0), isCutOperation(false)
{
    setup();
}

void FileMainWindow::show()
{
    QMainWindow::show();
}

void FileMainWindow::setup()
{
    // Create central container widget for path displays and panes
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->setSpacing(2);
    
    // Create horizontal splitter for panes
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    
    // Create left pane layout with path display
    QWidget *leftContainer = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftContainer);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(2);
    
    leftPathEdit = new QLineEdit;
    leftPathEdit->setReadOnly(true);
    leftPathEdit->setClearButtonEnabled(false);
    leftPathEdit->setToolTip("Current directory in left pane");
    leftLayout->addWidget(leftPathEdit);
    
    leftPane = new QtFileIconView(QDir::homePath(), leftContainer);
    leftPane->setSelectionMode(QAbstractItemView::ExtendedSelection);
    leftPane->installEventFilter(this);
    leftPane->setContextMenuPolicy(Qt::NoContextMenu);
    leftLayout->addWidget(leftPane);
    
    // Create right pane layout with path display
    QWidget *rightContainer = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightContainer);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(2);
    
    rightPathEdit = new QLineEdit;
    rightPathEdit->setReadOnly(true);
    rightPathEdit->setClearButtonEnabled(false);
    rightPathEdit->setToolTip("Current directory in right pane");
    rightLayout->addWidget(rightPathEdit);
    
    rightPane = new QtFileIconView(QDir::homePath(), rightContainer);
    rightPane->setSelectionMode(QAbstractItemView::ExtendedSelection);
    rightPane->installEventFilter(this);
    rightPane->setContextMenuPolicy(Qt::NoContextMenu);
    rightLayout->addWidget(rightPane);

    // Add containers to splitter
    splitter->addWidget(leftContainer);
    splitter->addWidget(rightContainer);
    
    // Add splitter to main layout and set as central widget
    mainLayout->addWidget(splitter);
    setCentralWidget(centralWidget);
    
    // Track selection changes to maintain row indices per pane
    if (leftPane->selectionModel()) {
        connect(leftPane->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, [this](const QItemSelection &, const QItemSelection &) {
                    QModelIndexList rows = leftPane->selectionModel()->selectedRows();
                    if (!rows.isEmpty()) {
                        leftPaneSelectedRow = rows.first().row();
                    }
                });
    }
    if (rightPane->selectionModel()) {
        connect(rightPane->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, [this](const QItemSelection &, const QItemSelection &) {
                    QModelIndexList rows = rightPane->selectionModel()->selectedRows();
                    if (!rows.isEmpty()) {
                        rightPaneSelectedRow = rows.first().row();
                    }
                });
    }
    
    // Set equal sizes for both panes
    splitter->setSizes(QList<int>() << 1 << 1);
    
    // Set left pane as initially active
    activePane = leftPane;
    leftPane->setFocus();
    
    // Connect click events to track active pane
    connect(leftPane, &QTreeView::clicked, this, &FileMainWindow::leftPaneClicked);
    connect(rightPane, &QTreeView::clicked, this, &FileMainWindow::rightPaneClicked);
    
    // Connect directory changed signals
    connect(leftPane, &QtFileIconView::directoryChanged, this, &FileMainWindow::leftPaneDirectoryChanged);
    connect(rightPane, &QtFileIconView::directoryChanged, this, &FileMainWindow::rightPaneDirectoryChanged);
    
    setCentralWidget(splitter);
    
    // Create toolbar
    QToolBar *toolbar1 = addToolBar("Operations");
    
    // Home button
    QToolButton *homeButton = new QToolButton();
    homeButton->setText("Home");
    homeButton->setToolTip("Go to Home Directory");
    homeButton->setStyleSheet("QToolButton { background-color: gray; color: white; border: 1px solid #666666; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #a0a0a0; } QToolButton:pressed { background-color: #505050; }");
    connect(homeButton, &QToolButton::clicked, this, &FileMainWindow::goHome);
    toolbar1->addWidget(homeButton);
    
    // Up button
    upButton = new QToolButton();
    upButton->setText("Up");
    upButton->setToolTip("Go Up");
    upButton->setStyleSheet("QToolButton { background-color: gray; color: white; border: 1px solid #666666; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #a0a0a0; } QToolButton:pressed { background-color: #505050; }");
    connect(upButton, &QToolButton::clicked, this, &FileMainWindow::cdUp);
    toolbar1->addWidget(upButton);
    
    // New folder button
    mkdirButton = new QToolButton();
    mkdirButton->setText("New Folder");
    mkdirButton->setToolTip("New Folder");
    mkdirButton->setStyleSheet("QToolButton { background-color: gray; color: white; border: 1px solid #666666; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #a0a0a0; } QToolButton:pressed { background-color: #505050; }");
    connect(mkdirButton, &QToolButton::clicked, this, &FileMainWindow::newFolder);
    toolbar1->addWidget(mkdirButton);
    
    toolbar1->addSeparator();
    
    // File operations
    QToolButton *cutButton = new QToolButton();
    cutButton->setText("Cut");
    cutButton->setToolTip("Cut selected files");
    cutButton->setStyleSheet("QToolButton { background-color: orange; color: white; border: 1px solid #d4651f; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #ff8c00; } QToolButton:pressed { background-color: #cc5500; }");
    connect(cutButton, &QToolButton::clicked, this, &FileMainWindow::cut);
    toolbar1->addWidget(cutButton);
    
    QToolButton *copyButton = new QToolButton();
    copyButton->setText("Copy");
    copyButton->setToolTip("Copy selected files");
    copyButton->setStyleSheet("QToolButton { background-color: green; color: white; border: 1px solid #4a7c4a; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #32cd32; } QToolButton:pressed { background-color: #228b22; }");
    connect(copyButton, &QToolButton::clicked, this, &FileMainWindow::copy);
    toolbar1->addWidget(copyButton);
    
    QToolButton *pasteButton = new QToolButton();
    pasteButton->setText("Paste");
    pasteButton->setToolTip("Paste files");
    pasteButton->setStyleSheet("QToolButton { background-color: blue; color: white; border: 1px solid #4a4a7c; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #4169e1; } QToolButton:pressed { background-color: #191970; }");
    connect(pasteButton, &QToolButton::clicked, this, &FileMainWindow::paste);
    toolbar1->addWidget(pasteButton);
    
    QToolButton *deleteButton = new QToolButton();
    deleteButton->setText("Delete");
    deleteButton->setToolTip("Delete selected files");
    deleteButton->setStyleSheet("QToolButton { background-color: red; color: white; border: 1px solid #7c4a4a; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #dc143c; } QToolButton:pressed { background-color: #8b0000; }");
    connect(deleteButton, &QToolButton::clicked, this, &FileMainWindow::remove);
    toolbar1->addWidget(deleteButton);
    
    toolbar1->addSeparator();
    
    // Appearance button
    QToolButton *appearanceButton = new QToolButton();
    appearanceButton->setText("Appearance");
    appearanceButton->setToolTip("Change color theme");
    appearanceButton->setStyleSheet("QToolButton { background-color: #2f2f2f; color: white; border: 1px solid #1a1a1a; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #404040; } QToolButton:pressed { background-color: #1a1a1a; }");
    connect(appearanceButton, &QToolButton::clicked, this, &FileMainWindow::showAppearanceMenu);
    toolbar1->addWidget(appearanceButton);
    
    // About button
    QToolButton *aboutButton = new QToolButton();
    aboutButton->setText("About");
    aboutButton->setToolTip("About Palmyra File Manager");
    aboutButton->setStyleSheet("QToolButton { background-color: #2f2f2f; color: white; border: 1px solid #1a1a1a; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #404040; } QToolButton:pressed { background-color: #1a1a1a; }");
    connect(aboutButton, &QToolButton::clicked, this, &FileMainWindow::about);
    toolbar1->addWidget(aboutButton);
    
    toolbar1->addSeparator();
    
    // Exit button
    QToolButton *exitButton = new QToolButton();
    exitButton->setText("Exit");
    exitButton->setToolTip("Exit Application");
    exitButton->setStyleSheet("QToolButton { background-color: #2f2f2f; color: white; border: 1px solid #1a1a1a; border-radius: 4px; padding: 4px; } QToolButton:hover { background-color: #404040; } QToolButton:pressed { background-color: #1a1a1a; }");
    connect(exitButton, &QToolButton::clicked, this, &QWidget::close);
    toolbar1->addWidget(exitButton);
    
    // We no longer need a separate path toolbar as path displays are now above each pane
    
    // Status bar
    label = new QLabel(statusBar());
    statusBar()->addWidget(label);
    progress = new QProgressBar(statusBar());
    statusBar()->addWidget(progress);
    
    // Apply default theme after all widgets are created
    currentTheme = "Default";
    applyTheme(currentTheme);
    
    // Select first row in active pane
    QTimer::singleShot(0, this, [this]() {
        if (activePane && activePane->model()->rowCount() > 0) {
            QModelIndex index = activePane->model()->index(0, 0);
            activePane->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
            leftPaneSelectedRow = 0;
        }
    });
}

void FileMainWindow::setPathCombo()
{
    if (!activePane) return;
    
    QString dir = activePane->currentDir().absolutePath();

    // Update the appropriate path edit based on which pane is active
    QLineEdit *activePathEdit = (activePane == leftPane) ? leftPathEdit : rightPathEdit;
    QLineEdit *inactivePathEdit = (activePane == leftPane) ? rightPathEdit : leftPathEdit;
    
    // Set text and colors for path edits
    activePathEdit->setText(dir);
    activePathEdit->setStyleSheet(QString("QLineEdit { background-color: %1; color: %2; border: 1px solid %3; }")
                                 .arg(activePathColor, pathTextColor, pathBorderColor));
    
    inactivePathEdit->setStyleSheet(QString("QLineEdit { background-color: %1; color: %2; border: 1px solid %3; }")
                                   .arg(inactivePathColor, pathTextColor, pathBorderColor));
}

void FileMainWindow::activatePane(QtFileIconView *targetPane, int &targetSelectedRow, const QModelIndex &requestedIndex)
{
    if (!targetPane) {
        return;
    }

    if (activePane && activePane != targetPane) {
        QItemSelectionModel *previousSelectionModel = activePane->selectionModel();
        if (previousSelectionModel) {
            QModelIndexList previousRows = previousSelectionModel->selectedRows();
            if (!previousRows.isEmpty()) {
                int storedRow = previousRows.first().row();
                if (activePane == leftPane) {
                    leftPaneSelectedRow = storedRow;
                } else if (activePane == rightPane) {
                    rightPaneSelectedRow = storedRow;
                }
            }
        }
    }

    activePane = targetPane;
    activePane->setFocus();
    
    // Update pane styles to show active/inactive state
    updatePaneStyles();

    QAbstractItemModel *model = targetPane->model();
    QItemSelectionModel *selectionModel = targetPane->selectionModel();

    if (!model || !selectionModel) {
        setPathCombo();
        return;
    }

    int rowCount = model->rowCount();
    if (rowCount == 0) {
        selectionModel->clearSelection();
        targetSelectedRow = -1;
        setPathCombo();
        return;
    }

    QModelIndex indexToUse = requestedIndex;

    if (!indexToUse.isValid()) {
        QModelIndexList currentSelection = selectionModel->selectedRows();
        if (!currentSelection.isEmpty()) {
            indexToUse = currentSelection.first();
        } else {
            int desiredRow = targetSelectedRow;
            if (desiredRow < 0 || desiredRow >= rowCount) {
                desiredRow = 0;
            }
            indexToUse = model->index(desiredRow, 0);
        }
    }

    if (indexToUse.isValid()) {
        targetSelectedRow = indexToUse.row();
        selectionModel->select(indexToUse, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
        selectionModel->setCurrentIndex(indexToUse, QItemSelectionModel::NoUpdate);
        targetPane->setCurrentIndex(indexToUse);
        targetPane->scrollTo(indexToUse, QAbstractItemView::EnsureVisible);
    }

    setPathCombo();
}

void FileMainWindow::leftPaneClicked(const QModelIndex &index)
{
    activatePane(leftPane, leftPaneSelectedRow, index);
}

void FileMainWindow::rightPaneClicked(const QModelIndex &index)
{
    activatePane(rightPane, rightPaneSelectedRow, index);
}

void FileMainWindow::leftPaneDirectoryChanged(const QString &dir)
{
    // Always update the left path display
    leftPathEdit->setText(dir);
    
    if (activePane == leftPane) {
        setWindowTitle(dir);
        setPathCombo();
    }
    // Reset selection to first item on directory change
    leftPaneSelectedRow = 0;
    QTimer::singleShot(0, this, [this]() {
        if (leftPane->model()->rowCount() > 0) {
            QModelIndex index = leftPane->model()->index(0, 0);
            if (activePane == leftPane) {
                leftPane->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
            }
        } else {
            leftPaneSelectedRow = -1;
            if (leftPane->selectionModel()) {
                leftPane->selectionModel()->clearSelection();
            }
        }
    });
}

void FileMainWindow::rightPaneDirectoryChanged(const QString &dir)
{
    // Always update the right path display
    rightPathEdit->setText(dir);
    
    if (activePane == rightPane) {
        setWindowTitle(dir);
        setPathCombo();
    }
    // Reset selection to first item on directory change
    rightPaneSelectedRow = 0;
    QTimer::singleShot(0, this, [this]() {
        if (rightPane->model()->rowCount() > 0) {
            QModelIndex index = rightPane->model()->index(0, 0);
            if (activePane == rightPane) {
                rightPane->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
            }
        } else {
            rightPaneSelectedRow = -1;
            if (rightPane->selectionModel()) {
                rightPane->selectionModel()->clearSelection();
            }
        }
    });
}

void FileMainWindow::cdUp()
{
    if (!activePane) return;
    QString currentPath = activePane->currentDir().absolutePath();
    QDir parent = QDir(currentPath).absolutePath();
    parent.cdUp();
    activePane->setDirectory(parent.absolutePath());
}

void FileMainWindow::goHome()
{
    QString homePath = QDir::homePath();
    activePane->setDirectory(homePath);
}

void FileMainWindow::newFolder()
{
    bool ok;
    QString name = QInputDialog::getText(this, "New Folder", 
                                       "Enter folder name:", QLineEdit::Normal, 
                                       "New Folder", &ok);
    if (ok && !name.isEmpty()) {
        QString currentPath = activePane->currentDir().absolutePath();
        QString newFolderPath = currentPath + "/" + name;
        
        QDir dir;
        if (dir.mkpath(newFolderPath)) {
            activePane->viewport()->update();
            QMessageBox::information(this, "Success", "Folder created successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to create folder!");
        }
    }
}

void FileMainWindow::cut()
{
    QModelIndexList selected = activePane->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::information(this, "Cut", "No files selected!");
        return;
    }
    
    copiedFiles.clear();
    QFileSystemModel* model = activePane->fileSystemModel();
    
    for (const QModelIndex &index : selected) {
        if (index.column() == 0) { // Only process the first column to avoid duplicates
            QModelIndex sourceIndex = activePane->mapToSource(index);
            if (!sourceIndex.isValid()) {
                continue;
            }
            QString filePath = model->filePath(sourceIndex);
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
    QModelIndexList selected = activePane->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::information(this, "Copy", "No files selected!");
        return;
    }
    
    copiedFiles.clear();
    QFileSystemModel* model = activePane->fileSystemModel();
    
    for (const QModelIndex &index : selected) {
        if (index.column() == 0) { // Only process the first column to avoid duplicates
            QModelIndex sourceIndex = activePane->mapToSource(index);
            if (!sourceIndex.isValid()) {
                continue;
            }
            QString filePath = model->filePath(sourceIndex);
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
    
    QString targetDir = activePane->currentDir().absolutePath();
    
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
        
        activePane->viewport()->update();
    }
}

void FileMainWindow::rename()
{
    QMessageBox::information(this, "Rename", "Rename functionality");
}

void FileMainWindow::remove()
{
    QModelIndexList selected = activePane->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::information(this, "Delete", "No files selected!");
        return;
    }
    
    QStringList filesToDelete;
    QFileSystemModel* model = activePane->fileSystemModel();
    
    for (const QModelIndex &index : selected) {
        if (index.column() == 0) { // Only process the first column to avoid duplicates
            QModelIndex sourceIndex = activePane->mapToSource(index);
            if (!sourceIndex.isValid()) {
                continue;
            }
            QString filePath = model->filePath(sourceIndex);
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
        activePane->viewport()->update();
    }
}

void FileMainWindow::showAppearanceMenu()
{
    QMenu *menu = new QMenu(this);
    
    // Create theme actions
    QStringList themes;
    themes << "Default" << "Dark Blue" << "MC Classic" << "Sand" 
           << "Modarcon16" << "Dark Green" << "Nicedark" << "Gotar";
    
    for (const QString &theme : themes) {
        QAction *action = menu->addAction(theme);
        action->setCheckable(true);
        action->setChecked(theme == currentTheme);
        connect(action, &QAction::triggered, this, [this, theme]() {
            currentTheme = theme;
            applyTheme(theme);
        });
    }
    
    // Show menu at cursor position
    menu->exec(QCursor::pos());
    delete menu;
}

void FileMainWindow::applyTheme(const QString &themeName)
{
    QString paneStyle;
    QString paneBackground = "#d3d3d3";
    QString paneTextColor = "#000000";
    QString selectionBackground = "#0078d7";
    QString selectionForeground = "#ffffff";
    
    // Path display colors - default to lighter/darker versions of pane colors
    activePathColor = "#f0f0f0";      // Lighter than pane for active
    inactivePathColor = "#c0c0c0";    // Darker than pane for inactive
    pathTextColor = "#000000";        // Same as pane text
    pathBorderColor = "#808080";      // Same as pane border
    
    if (themeName == "Default") {
        // Default theme - light gray background, black text
        paneStyle = 
            "QTreeView {"
            "   background-color: #d3d3d3;"
            "   color: #000000;"
            "   alternate-background-color: #c0c0c0;"
            "   selection-background-color: #0078d7;"
            "   selection-color: #ffffff;"
            "   border: 1px solid #808080;"
            "}"
            "QHeaderView::section {"
            "   background-color: #a0a0a0;"
            "   color: #000000;"
            "   padding: 4px;"
            "   border: 1px solid #808080;"
            "}";
        paneBackground = "#d3d3d3";
        paneTextColor = "#000000";
        selectionBackground = "#0078d7";
        selectionForeground = "#ffffff";
        
        // Path colors for Default theme
        activePathColor = "#f0f0f0";
        inactivePathColor = "#c0c0c0";
        pathTextColor = "#000000";
        pathBorderColor = "#808080";
        
        // File type colors for Default theme
        fileColorDir = "#0000FF";        // Blue for directories
        fileColorExec = "#00AA00";       // Green for executables
        fileColorArchive = "#AA0000";    // Red for archives
        fileColorImage = "#AA00AA";      // Magenta for images
        fileColorVideo = "#00AAAA";      // Cyan for videos
        fileColorAudio = "#00AAAA";      // Cyan for audio
        fileColorDoc = "#AAAA00";        // Yellow for documents
        fileColorDefault = "#000000";    // Black for regular files
    }
    else if (themeName == "Dark Blue") {
        // Dark blue theme - classic MC look
        paneStyle = 
            "QTreeView {"
            "   background-color: #000080;"
            "   color: #00ffff;"
            "   alternate-background-color: #000060;"
            "   selection-background-color: #008080;"
            "   selection-color: #ffff00;"
            "   border: 1px solid #00ffff;"
            "}"
            "QHeaderView::section {"
            "   background-color: #000080;"
            "   color: #ffff00;"
            "   padding: 4px;"
            "   border: 1px solid #00ffff;"
            "}";
        paneBackground = "#000080";
        paneTextColor = "#00ffff";
        selectionBackground = "#008080";
        selectionForeground = "#ffff00";
        
        // Path colors for Dark Blue theme
        activePathColor = "#0000a0";
        inactivePathColor = "#000060";
        pathTextColor = "#00ffff";
        pathBorderColor = "#00ffff";
        
        // File type colors for Dark Blue theme (MC classic)
        fileColorDir = "#FFFFFF";        // White for directories
        fileColorExec = "#00FF00";       // Bright green for executables
        fileColorArchive = "#FF0000";    // Bright red for archives
        fileColorImage = "#FF00FF";      // Bright magenta for images
        fileColorVideo = "#00FFFF";      // Bright cyan for videos
        fileColorAudio = "#00FFFF";      // Bright cyan for audio
        fileColorDoc = "#FFFF00";        // Bright yellow for documents
        fileColorDefault = "#00FFFF";    // Cyan for regular files
    }
    else if (themeName == "MC Classic") {
        // Midnight Commander classic - dark blue with cyan
        paneStyle = 
            "QTreeView {"
            "   background-color: #000084;"
            "   color: #00ffff;"
            "   alternate-background-color: #000070;"
            "   selection-background-color: #008787;"
            "   selection-color: #ffffff;"
            "   border: 1px solid #00ffff;"
            "}"
            "QHeaderView::section {"
            "   background-color: #000084;"
            "   color: #ffff00;"
            "   padding: 4px;"
            "   border: 1px solid #00ffff;"
            "}";
        paneBackground = "#000084";
        paneTextColor = "#00ffff";
        selectionBackground = "#008787";
        selectionForeground = "#ffffff";
        
        // Path colors for MC Classic theme
        activePathColor = "#0000a0";
        inactivePathColor = "#000066";
        pathTextColor = "#00ffff";
        pathBorderColor = "#00ffff";
        
        // File type colors for MC Classic theme
        fileColorDir = "#FFFFFF";        // White for directories
        fileColorExec = "#00FF00";       // Bright green for executables
        fileColorArchive = "#FF0000";    // Bright red for archives
        fileColorImage = "#FF00FF";      // Bright magenta for images
        fileColorVideo = "#00FFFF";      // Bright cyan for videos
        fileColorAudio = "#00FFFF";      // Bright cyan for audio
        fileColorDoc = "#FFFF00";        // Bright yellow for documents
        fileColorDefault = "#00FFFF";    // Cyan for regular files
    }
    else if (themeName == "Sand") {
        // Sand theme - beige/tan colors
        paneStyle = 
            "QTreeView {"
            "   background-color: #e8d0a0;"
            "   color: #000000;"
            "   alternate-background-color: #d8c090;"
            "   selection-background-color: #c0a080;"
            "   selection-color: #000000;"
            "   border: 1px solid #a08060;"
            "}"
            "QHeaderView::section {"
            "   background-color: #c0a080;"
            "   color: #000000;"
            "   padding: 4px;"
            "   border: 1px solid #a08060;"
            "}";
        paneBackground = "#e8d0a0";
        paneTextColor = "#000000";
        selectionBackground = "#c0a080";
        selectionForeground = "#000000";
        
        // Path colors for Sand theme
        activePathColor = "#f8e0b0";
        inactivePathColor = "#d0b080";
        pathTextColor = "#000000";
        pathBorderColor = "#a08060";
        
        // File type colors for Sand theme
        fileColorDir = "#0000AA";        // Dark blue for directories
        fileColorExec = "#00AA00";       // Green for executables
        fileColorArchive = "#AA0000";    // Red for archives
        fileColorImage = "#AA00AA";      // Magenta for images
        fileColorVideo = "#00AAAA";      // Cyan for videos
        fileColorAudio = "#00AAAA";      // Cyan for audio
        fileColorDoc = "#AA5500";        // Orange for documents
        fileColorDefault = "#000000";    // Black for regular files
    }
    else if (themeName == "Modarcon16") {
        // Modarcon16 - modern dark theme
        paneStyle = 
            "QTreeView {"
            "   background-color: #1e1e1e;"
            "   color: #d4d4d4;"
            "   alternate-background-color: #252525;"
            "   selection-background-color: #264f78;"
            "   selection-color: #ffffff;"
            "   border: 1px solid #3e3e3e;"
            "}"
            "QHeaderView::section {"
            "   background-color: #2d2d2d;"
            "   color: #cccccc;"
            "   padding: 4px;"
            "   border: 1px solid #3e3e3e;"
            "}";
        paneBackground = "#1e1e1e";
        paneTextColor = "#d4d4d4";
        selectionBackground = "#264f78";
        selectionForeground = "#ffffff";
        
        // Path colors for Modarcon16 theme
        activePathColor = "#2d2d2d";
        inactivePathColor = "#181818";
        pathTextColor = "#d4d4d4";
        pathBorderColor = "#3e3e3e";
        
        // File type colors for Modarcon16 theme
        fileColorDir = "#569CD6";        // Blue for directories
        fileColorExec = "#4EC9B0";       // Teal for executables
        fileColorArchive = "#CE9178";    // Orange for archives
        fileColorImage = "#C586C0";      // Purple for images
        fileColorVideo = "#4FC1FF";      // Light blue for videos
        fileColorAudio = "#4FC1FF";      // Light blue for audio
        fileColorDoc = "#DCDCAA";        // Yellow for documents
        fileColorDefault = "#D4D4D4";    // Light gray for regular files
    }
    else if (themeName == "Dark Green") {
        // Dark green terminal style
        paneStyle = 
            "QTreeView {"
            "   background-color: #001a00;"
            "   color: #00ff00;"
            "   alternate-background-color: #002000;"
            "   selection-background-color: #004000;"
            "   selection-color: #00ff00;"
            "   border: 1px solid #00ff00;"
            "}"
            "QHeaderView::section {"
            "   background-color: #002a00;"
            "   color: #00ff00;"
            "   padding: 4px;"
            "   border: 1px solid #00ff00;"
            "}";
        paneBackground = "#001a00";
        paneTextColor = "#00ff00";
        selectionBackground = "#004000";
        selectionForeground = "#00ff00";
        
        // Path colors for Dark Green theme
        activePathColor = "#003000";
        inactivePathColor = "#001500";
        pathTextColor = "#00ff00";
        pathBorderColor = "#00ff00";
        
        // File type colors for Dark Green theme
        fileColorDir = "#00FF00";        // Bright green for directories
        fileColorExec = "#FFFF00";       // Yellow for executables
        fileColorArchive = "#FF0000";    // Red for archives
        fileColorImage = "#00FFFF";      // Cyan for images
        fileColorVideo = "#00AAAA";      // Dark cyan for videos
        fileColorAudio = "#00AAAA";      // Dark cyan for audio
        fileColorDoc = "#AAFF00";        // Light green for documents
        fileColorDefault = "#00AA00";    // Medium green for regular files
    }
    else if (themeName == "Nicedark") {
        // Nice dark theme with subtle colors
        paneStyle = 
            "QTreeView {"
            "   background-color: #2b2b2b;"
            "   color: #e0e0e0;"
            "   alternate-background-color: #323232;"
            "   selection-background-color: #4a6fa5;"
            "   selection-color: #ffffff;"
            "   border: 1px solid #555555;"
            "}"
            "QHeaderView::section {"
            "   background-color: #3c3c3c;"
            "   color: #e0e0e0;"
            "   padding: 4px;"
            "   border: 1px solid #555555;"
            "}";
        paneBackground = "#2b2b2b";
        paneTextColor = "#e0e0e0";
        selectionBackground = "#4a6fa5";
        selectionForeground = "#ffffff";
        
        // Path colors for Nicedark theme
        activePathColor = "#3c3c3c";
        inactivePathColor = "#222222";
        pathTextColor = "#e0e0e0";
        pathBorderColor = "#555555";
        
        // File type colors for Nicedark theme
        fileColorDir = "#6A9FB5";        // Blue for directories
        fileColorExec = "#90C695";       // Green for executables
        fileColorArchive = "#D28B71";    // Orange for archives
        fileColorImage = "#C586C0";      // Purple for images
        fileColorVideo = "#6FA8DC";      // Light blue for videos
        fileColorAudio = "#6FA8DC";      // Light blue for audio
        fileColorDoc = "#E5C07B";        // Yellow for documents
        fileColorDefault = "#E0E0E0";    // Light gray for regular files
    }
    else if (themeName == "Gotar") {
        // Gotar - amber on black
        paneStyle = 
            "QTreeView {"
            "   background-color: #000000;"
            "   color: #ffb000;"
            "   alternate-background-color: #0a0a0a;"
            "   selection-background-color: #ff8000;"
            "   selection-color: #000000;"
            "   border: 1px solid #ffb000;"
            "}"
            "QHeaderView::section {"
            "   background-color: #1a1a0a;"
            "   color: #ffb000;"
            "   padding: 4px;"
            "   border: 1px solid #ffb000;"
            "}";
        paneBackground = "#000000";
        paneTextColor = "#ffb000";
        selectionBackground = "#ff8000";
        selectionForeground = "#000000";
        
        // Path colors for Gotar theme
        activePathColor = "#1a1a0a";
        inactivePathColor = "#050505";
        pathTextColor = "#ffb000";
        pathBorderColor = "#ffb000";
        
        // File type colors for Gotar theme (amber on black)
        fileColorDir = "#FFFF00";        // Yellow for directories
        fileColorExec = "#00FF00";       // Green for executables
        fileColorArchive = "#FF8000";    // Orange for archives
        fileColorImage = "#FF00FF";      // Magenta for images
        fileColorVideo = "#00FFFF";      // Cyan for videos
        fileColorAudio = "#00FFFF";      // Cyan for audio
        fileColorDoc = "#FFD700";        // Gold for documents
        fileColorDefault = "#FFB000";    // Amber for regular files
    }

    paneStyle += QString(
        "QTreeView::item:selected:active {"
        "   background-color: %1;"
        "   color: %2;"
        "}"
        "QTreeView::item:selected:active:hover {"
        "   background-color: %1;"
        "   color: %2;"
        "}"
        "QTreeView::item:selected:focus {"
        "   background-color: %1;"
        "   color: %2;"
        "}"
        "QTreeView::item:selected:!active {"
        "   background-color: %3;"
        "   color: %4;"
        "}"
    ).arg(selectionBackground, selectionForeground, paneBackground, paneTextColor);
    
    // Store the current pane style
    currentPaneStyle = paneStyle;
    
    // Apply the theme to both panes based on active state
    updatePaneStyles();
    
    // Update file item delegates with theme colors
    if (leftPane && leftPane->getDelegate()) {
        leftPane->getDelegate()->setThemeColors(
            fileColorDir, fileColorExec, fileColorArchive, fileColorImage,
            fileColorVideo, fileColorAudio, fileColorDoc, fileColorDefault
        );
    }
    if (rightPane && rightPane->getDelegate()) {
        rightPane->getDelegate()->setThemeColors(
            fileColorDir, fileColorExec, fileColorArchive, fileColorImage,
            fileColorVideo, fileColorAudio, fileColorDoc, fileColorDefault
        );
    }
    
    // Force repaint to update colors
    if (leftPane) leftPane->viewport()->update();
    if (rightPane) rightPane->viewport()->update();
    
    // Update status bar if it exists
    if (label) {
        label->setText(QString("Theme changed to: %1").arg(themeName));
    }
}

void FileMainWindow::updatePaneStyles()
{
    // Determine which pane is active and inactive
    QtFileIconView *activePaneWidget = activePane;
    QtFileIconView *inactivePaneWidget = (activePane == leftPane) ? rightPane : leftPane;
    
    // Apply style to active pane (with visible selection)
    if (activePaneWidget) {
        activePaneWidget->setStyleSheet(currentPaneStyle);
    }
    
    // Apply style to inactive pane (with invisible selection)
    if (inactivePaneWidget) {
        inactivePaneWidget->setStyleSheet(currentPaneStyle);
    }
    
    // Update path display styles based on active state
    QLineEdit *activePathEdit = (activePane == leftPane) ? leftPathEdit : rightPathEdit;
    QLineEdit *inactivePathEdit = (activePane == leftPane) ? rightPathEdit : leftPathEdit;
    
    activePathEdit->setStyleSheet(QString("QLineEdit { background-color: %1; color: %2; border: 1px solid %3; }")
                                .arg(activePathColor, pathTextColor, pathBorderColor));
    inactivePathEdit->setStyleSheet(QString("QLineEdit { background-color: %1; color: %2; border: 1px solid %3; }")
                                  .arg(inactivePathColor, pathTextColor, pathBorderColor));
    
    // Force repaint to update selection appearance
    if (leftPane) leftPane->viewport()->update();
    if (rightPane) rightPane->viewport()->update();
}

void FileMainWindow::about()
{
    QDialog aboutDialog(this);
    aboutDialog.setWindowTitle("About PalmyraFM");
    aboutDialog.setFixedSize(550, 450);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(&aboutDialog);
    mainLayout->setSpacing(15);
    
    // Header with icon and title - centered
    QVBoxLayout *headerLayout = new QVBoxLayout();
    headerLayout->setAlignment(Qt::AlignCenter);
    
    // Application icon - centered
    QLabel *iconLabel = new QLabel();
    iconLabel->setAlignment(Qt::AlignCenter);
    QPixmap iconPixmap(":/icons/icons/palmyrafm.png");
    if (iconPixmap.isNull()) {
        iconPixmap.load("icons/palmyrafm.png");
    }
    if (!iconPixmap.isNull()) {
        iconLabel->setPixmap(iconPixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    headerLayout->addWidget(iconLabel);
    
    // Title and basic info - centered
    QLabel *titleLabel = new QLabel("<h2>PalmyraFM</h2>");
    titleLabel->setAlignment(Qt::AlignCenter);
    QLabel *versionLabel = new QLabel("<b>Version:</b> 1.0");
    versionLabel->setAlignment(Qt::AlignCenter);
    QLabel *descLabel = new QLabel("A dual-pane file manager for Linux and macOS");
    descLabel->setAlignment(Qt::AlignCenter);
    QLabel *copyrightLabel = new QLabel("© Artem Nagornyi, 2025");
    copyrightLabel->setAlignment(Qt::AlignCenter);
    
    headerLayout->addWidget(titleLabel);
    headerLayout->addWidget(versionLabel);
    headerLayout->addWidget(descLabel);
    headerLayout->addWidget(copyrightLabel);
    
    mainLayout->addLayout(headerLayout);
    
    // Tab widget for organized sections
    QTabWidget *tabWidget = new QTabWidget();
    
    // Keyboard shortcuts tab - complete list
    QWidget *shortcutsTab = new QWidget();
    QVBoxLayout *shortcutsLayout = new QVBoxLayout(shortcutsTab);
    QTextBrowser *shortcutsText = new QTextBrowser();
    shortcutsText->setReadOnly(true);
    shortcutsText->setMaximumHeight(300);  // Limit height to ensure scrollability
    shortcutsText->setHtml(
        "<table cellpadding='4' cellspacing='2'>"
        "<tr><td><b>F1</b></td><td>Show this About dialog</td></tr>"
        "<tr><td><b>Tab</b></td><td>Switch between left and right panels</td></tr>"
        "<tr><td><b>Home</b></td><td>Go to home directory</td></tr>"
        "<tr><td><b>Backspace</b></td><td>Go up directory</td></tr>"        
        "<tr><td><b>F7</b></td><td>Create new directory</td></tr>"    
        "<tr><td><b>Ctrl+X</b></td><td>Cut selected files</td></tr>"
        "<tr><td><b>Ctrl+C</b></td><td>Copy selected files</td></tr>"        
        "<tr><td><b>Ctrl+V</b></td><td>Paste files</td></tr>"
        "<tr><td><b>F8</b></td><td>Delete selected files</td></tr>"
        "<tr><td><b>Shift+Delete</b></td><td>Delete selected files</td></tr>"
        "<tr><td><b>F10</b></td><td>Exit application</td></tr>"
        "<tr><td><b>Enter</b></td><td>Enter directory / Open file</td></tr>"
        "</table>"
    );
    shortcutsLayout->addWidget(shortcutsText);
    tabWidget->addTab(shortcutsTab, "Keyboard Shortcuts");
    
    // License tab
    QWidget *licenseTab = new QWidget();
    QVBoxLayout *licenseLayout = new QVBoxLayout(licenseTab);
    QTextBrowser *licenseText = new QTextBrowser();
    licenseText->setReadOnly(true);
    licenseText->setOpenExternalLinks(true);  // Enable link opening
    licenseText->setHtml(
        "<p><b>License:</b> GNU General Public License v3.0</p>"
        "<p>This program is free software: you can redistribute it and/or modify it "
        "under the terms of the GNU General Public License as published by the "
        "Free Software Foundation, either version 3 of the License, or (at your option) "
        "any later version.</p>"
        "<p>For the complete license text, visit:<br>"
        "<a href='https://www.gnu.org/licenses/gpl-3.0.html'>https://www.gnu.org/licenses/gpl-3.0.html</a></p>"
    );
    licenseLayout->addWidget(licenseText);
    tabWidget->addTab(licenseTab, "License");
    
    // Qt Framework tab
    QWidget *qtTab = new QWidget();
    QVBoxLayout *qtLayout = new QVBoxLayout(qtTab);
    QTextBrowser *qtText = new QTextBrowser();
    qtText->setReadOnly(true);
    qtText->setOpenExternalLinks(true);  // Enable link opening
    qtText->setHtml(
        "<p><b>Qt Framework:</b></p>"
        "<p>This application uses the Qt framework under the GNU Lesser General Public License (LGPL) v3.</p>"
        "<p>Qt is a cross-platform application framework developed by The Qt Company.</p>"
        "<p><b>Qt Source Code:</b><br>"
        "<a href='https://www.qt.io/download-open-source'>https://www.qt.io/download-open-source</a></p>"
        "<p><b>Qt Licensing Information:</b><br>"
        "<a href='https://doc.qt.io/qt-6/licensing.html'>https://doc.qt.io/qt-6/licensing.html</a></p>"
        "<p><b>LGPL v3 License:</b><br>"
        "<a href='https://www.gnu.org/licenses/lgpl-3.0.html'>https://www.gnu.org/licenses/lgpl-3.0.html</a></p>"
    );
    qtLayout->addWidget(qtText);
    tabWidget->addTab(qtTab, "Qt Framework");
    
    mainLayout->addWidget(tabWidget);
    
    // Close button
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    QPushButton *closeButton = new QPushButton("Close");
    closeButton->setMinimumWidth(80);
    connect(closeButton, &QPushButton::clicked, &aboutDialog, &QDialog::accept);
    buttonLayout->addWidget(closeButton);
    mainLayout->addLayout(buttonLayout);
    
    aboutDialog.exec();
}

void FileMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Backspace:
            // Go up directory
            cdUp();
            break;
            
        case Qt::Key_Return:
        case Qt::Key_Enter:
            // Enter selected directory or open file
            {
                QModelIndexList selected = activePane->selectionModel()->selectedIndexes();
                if (!selected.isEmpty()) {
                    QModelIndex index = selected.first();
                    activePane->itemDoubleClicked(index);
                }
            }
            break;
            
        case Qt::Key_F7:
            // Create new directory
            newFolder();
            break;
            
        case Qt::Key_F8:
            // Remove files
            remove();
            break;
            
        case Qt::Key_F1:
            // Show About dialog
            about();
            break;
            
        case Qt::Key_F10:
            // Exit application
            QApplication::quit();
            break;
            
        case Qt::Key_C:
            if (event->modifiers() & Qt::ControlModifier) {
                // Ctrl+C: Copy files
                copy();
            } else {
                QMainWindow::keyPressEvent(event);
            }
            break;
            
        case Qt::Key_X:
            if (event->modifiers() & Qt::ControlModifier) {
                // Ctrl+X: Cut files
                cut();
            } else {
                QMainWindow::keyPressEvent(event);
            }
            break;
            
        case Qt::Key_V:
            if (event->modifiers() & Qt::ControlModifier) {
                // Ctrl+V: Paste files
                paste();
            } else {
                QMainWindow::keyPressEvent(event);
            }
            break;
            
        case Qt::Key_Insert:
            if (event->modifiers() & Qt::ShiftModifier) {
                // Shift+Insert: Paste files
                paste();
            } else {
                QMainWindow::keyPressEvent(event);
            }
            break;
            
        case Qt::Key_Delete:
            if (event->modifiers() & Qt::ShiftModifier) {
                // Shift+Delete: Delete files
                remove();
            } else {
                QMainWindow::keyPressEvent(event);
            }
            break;
            
        case Qt::Key_Tab:
            // Switch between left and right panes
            event->accept();  // Prevent default tab navigation
            if (activePane == leftPane) {
                activatePane(rightPane, rightPaneSelectedRow, QModelIndex());
            } else {
                activatePane(leftPane, leftPaneSelectedRow, QModelIndex());
            }
            return;  // Don't call parent handler
            
        default:
            // Pass other keys to parent
            QMainWindow::keyPressEvent(event);
            break;
    }
}

bool FileMainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == leftPane || obj == rightPane) {
        if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() != Qt::LeftButton) {
                return true;
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() != Qt::LeftButton) {
                return true;
            }
        } else if (event->type() == QEvent::ContextMenu) {
            return true;
        }
    }

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        
        // Handle Tab key to switch between panels
        if (keyEvent->key() == Qt::Key_Tab) {
            if (obj == leftPane || obj == rightPane) {
                // Switch between left and right panes
                if (activePane == leftPane) {
                    activatePane(rightPane, rightPaneSelectedRow, QModelIndex());
                } else {
                    activatePane(leftPane, leftPaneSelectedRow, QModelIndex());
                }
                return true;  // Event handled, don't propagate
            }
        }
    }
    
    // Pass event to base class for default handling
    return QMainWindow::eventFilter(obj, event);
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

/****************************************************************************
 *
 * FileSortProxyModel - keeps ".." entry pinned and hides it at root
 *
 *****************************************************************************/

class FileSortProxyModel : public QSortFilterProxyModel
{
public:
    explicit FileSortProxyModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent), currentPathIsRoot(false), currentSortOrder(Qt::AscendingOrder)
    {
        setDynamicSortFilter(true);
        setSortCaseSensitivity(Qt::CaseInsensitive);
    }

    void setCurrentPath(const QString &path)
    {
        currentPathIsRoot = QDir::cleanPath(path) == QDir::rootPath();
        invalidateFilter();
    }

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override
    {
        currentSortOrder = order;
        QSortFilterProxyModel::sort(column, order);
    }

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override
    {
        if (!currentPathIsRoot) {
            return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
        }

        QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
        if (!index.isValid()) {
            return false;
        }

        QString name = sourceModel()->data(index, QFileSystemModel::FileNameRole).toString();
        if (name == QStringLiteral("..")) {
            return false;
        }

        return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
    }

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override
    {
        QString leftName = sourceModel()->data(left, QFileSystemModel::FileNameRole).toString();
        QString rightName = sourceModel()->data(right, QFileSystemModel::FileNameRole).toString();

        const bool leftIsParent = (leftName == QStringLiteral(".."));
        const bool rightIsParent = (rightName == QStringLiteral(".."));

        if (leftIsParent || rightIsParent) {
            if (leftIsParent && rightIsParent) {
                return false;
            }
            if (currentSortOrder == Qt::AscendingOrder) {
                return leftIsParent;
            }
            // Descending order: treat ".." as largest to keep it first after order inversion
            return !leftIsParent;
        }

        return QSortFilterProxyModel::lessThan(left, right);
    }

private:
    bool currentPathIsRoot;
    Qt::SortOrder currentSortOrder;
};

/*****************************************************************************
 *
 * FileItemDelegate Implementation - MC-style file display
 *
 *****************************************************************************/

FileItemDelegate::FileItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    // Default colors (will be updated by theme)
    m_dirColor = "#FFFFFF";
    m_execColor = "#00FF00";
    m_archiveColor = "#FF0000";
    m_imageColor = "#FF00FF";
    m_videoColor = "#00FFFF";
    m_audioColor = "#00FFFF";
    m_docColor = "#FFFF00";
    m_defaultColor = "#FFFFFF";
}

void FileItemDelegate::setThemeColors(const QString &dirColor, const QString &execColor,
                                      const QString &archiveColor, const QString &imageColor,
                                      const QString &videoColor, const QString &audioColor,
                                      const QString &docColor, const QString &defaultColor)
{
    m_dirColor = dirColor;
    m_execColor = execColor;
    m_archiveColor = archiveColor;
    m_imageColor = imageColor;
    m_videoColor = videoColor;
    m_audioColor = audioColor;
    m_docColor = docColor;
    m_defaultColor = defaultColor;
}

QString FileItemDelegate::getFilePrefix(const QFileInfo &fileInfo) const
{
    // For "..", we return the full text including the prefix
    // to avoid duplication in paint method
    if (fileInfo.fileName() == "..") {
        return "/";
    }
    
    if (fileInfo.isDir()) {
        return "/";
    }
    
    if (fileInfo.isExecutable() && !fileInfo.isDir()) {
        return "*";
    }
    
    return "";
}

QColor FileItemDelegate::getFileColor(const QFileInfo &fileInfo) const
{
    if (fileInfo.fileName() == "..") {
        return QColor(m_dirColor);
    }
    
    if (fileInfo.isDir()) {
        return QColor(m_dirColor);
    }
    
    if (fileInfo.isExecutable() && !fileInfo.isDir()) {
        return QColor(m_execColor);
    }
    
    QString suffix = fileInfo.suffix().toLower();
    
    // Archive files
    if (suffix == "zip" || suffix == "tar" || suffix == "gz" || suffix == "bz2" || 
        suffix == "xz" || suffix == "7z" || suffix == "rar" || suffix == "tgz") {
        return QColor(m_archiveColor);
    }
    
    // Image files
    if (suffix == "jpg" || suffix == "jpeg" || suffix == "png" || suffix == "gif" || 
        suffix == "bmp" || suffix == "svg" || suffix == "webp" || suffix == "ico") {
        return QColor(m_imageColor);
    }
    
    // Video files
    if (suffix == "mp4" || suffix == "avi" || suffix == "mkv" || suffix == "mov" || 
        suffix == "wmv" || suffix == "flv" || suffix == "webm" || suffix == "m4v") {
        return QColor(m_videoColor);
    }
    
    // Audio files
    if (suffix == "mp3" || suffix == "wav" || suffix == "flac" || suffix == "ogg" || 
        suffix == "m4a" || suffix == "aac" || suffix == "wma") {
        return QColor(m_audioColor);
    }
    
    // Document files
    if (suffix == "pdf" || suffix == "doc" || suffix == "docx" || suffix == "txt" || 
        suffix == "odt" || suffix == "rtf" || suffix == "md") {
        return QColor(m_docColor);
    }
    
    return QColor(m_defaultColor);
}

void FileItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, 
                             const QModelIndex &index) const
{
    // Only customize column 0 (filename), let default delegate handle other columns
    if (index.column() != 0) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    
    // Get file info - handle proxy model
    QFileInfo fileInfo;
    const QAbstractItemModel *model = index.model();
    
    // Check if it's a proxy model and get the source model
    const QSortFilterProxyModel *proxyModel = qobject_cast<const QSortFilterProxyModel*>(model);
    if (proxyModel) {
        const QFileSystemModel *fsModel = qobject_cast<const QFileSystemModel*>(proxyModel->sourceModel());
        if (fsModel) {
            QModelIndex sourceIndex = proxyModel->mapToSource(index);
            fileInfo = fsModel->fileInfo(sourceIndex);
        }
    } else {
        // Direct file system model
        const QFileSystemModel *fsModel = qobject_cast<const QFileSystemModel*>(model);
        if (fsModel) {
            fileInfo = fsModel->fileInfo(index);
        }
    }
    
    // Fallback: use display role if we couldn't get fileInfo properly
    if (!fileInfo.exists() && !fileInfo.fileName().isEmpty()) {
        // Try to construct from display text - this is a last resort
        QString fileName = index.data(Qt::DisplayRole).toString();
        // This won't work well, but prevents crashes
        fileInfo = QFileInfo(fileName);
    }
    
    // Draw background based on selection and active state
    if (opt.state & QStyle::State_Selected) {
        if (opt.state & QStyle::State_Active) {
            // Active pane - show selection highlight
            painter->fillRect(opt.rect, opt.palette.highlight());
        } else {
            // Inactive pane - use background color (hide selection)
            painter->fillRect(opt.rect, opt.palette.base());
        }
    } else {
        painter->fillRect(opt.rect, opt.palette.base());
    }
    
    // Get prefix and color
    QString prefix = getFilePrefix(fileInfo);
    QColor textColor = getFileColor(fileInfo);
    
    // Use selection color if selected AND active
    if (opt.state & QStyle::State_Selected) {
        if (opt.state & QStyle::State_Active) {
            // Active pane - use highlight text color
            textColor = opt.palette.highlightedText().color();
        }
        // Inactive pane - keep the file type color
    }
    
    // Draw text with prefix
    painter->setPen(textColor);
    QString displayText = prefix + index.data(Qt::DisplayRole).toString();
    
    QRect textRect = opt.rect.adjusted(5, 0, -5, 0);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, displayText);
}

/*****************************************************************************
 *
 * QtFileIconView Implementation using QListView
 *
 *****************************************************************************/

QtFileIconView::QtFileIconView(const QString &dir, QWidget *parent)
    : QTreeView(parent)
{
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(QDir::rootPath());
    // Show .. but not .
    fileModel->setFilter(QDir::AllEntries | QDir::NoDot);
    
    proxyModel = new FileSortProxyModel(this);
    proxyModel->setSourceModel(fileModel);
    proxyModel->setCurrentPath(dir);
    setModel(proxyModel);
    setRootIndex(proxyModel->mapFromSource(fileModel->index(dir)));
    
    // Disable icons in the file system model
    fileModel->setOption(QFileSystemModel::DontUseCustomDirectoryIcons, true);
    
    // Create and set custom delegate for MC-style display
    itemDelegate = new FileItemDelegate(this);
    setItemDelegateForColumn(0, itemDelegate);
    
    // Configure tree view for Midnight Commander style
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setAlternatingRowColors(false);
    setSortingEnabled(true);
    setUniformRowHeights(true);
    setRootIsDecorated(false);
    setItemsExpandable(false);
    setExpandsOnDoubleClick(false);
    setIndentation(0);
    
    // Disable scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    // Disable icon display
    setIconSize(QSize(0, 0));
    
    // Show only Name, Size, and Modified columns
    hideColumn(1); // Hide Type column
    setColumnWidth(0, 250); // Name column - minimum width
    
    // Set header - Name stretches, Size and Modified auto-fit on the right
    header()->setStretchLastSection(false);
    header()->setSectionsMovable(false); // Prevent column reordering
    header()->setMinimumSectionSize(50); // Reduce minimum size for tighter fit
    header()->setDefaultSectionSize(80); // Reduce default size
    header()->setSectionResizeMode(0, QHeaderView::Stretch); // Name fills available space
    header()->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Size auto-fits content
    header()->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Modified auto-fits content
    header()->setSortIndicatorShown(true);
    header()->setSortIndicator(0, Qt::AscendingOrder);
    sortByColumn(0, Qt::AscendingOrder);
    
    viewDir = QDir(dir);
    newFolderNum = 1;
    
    proc1 = new QProcess(this);
    internalTimer = new QTimer(this);
    
    connect(this, &QAbstractItemView::doubleClicked, 
            this, &QtFileIconView::itemDoubleClicked);
    
    setDragDropMode(QAbstractItemView::DragDrop);
    setAcceptDrops(true);
    
    // Emit initial directory changed signal
    emit directoryChanged(dir);
}

void QtFileIconView::setDirectory(const QString &dir)
{
    viewDir = QDir(dir);
    if (proxyModel) {
        proxyModel->setCurrentPath(dir);
        QModelIndex sourceIndex = fileModel->index(dir);
        setRootIndex(proxyModel->mapFromSource(sourceIndex));
        sortByColumn(header()->sortIndicatorSection(), header()->sortIndicatorOrder());
    } else {
        setRootIndex(fileModel->index(dir));
    }
    emit directoryChanged(dir);
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
    QModelIndex sourceIndex = mapToSource(index);
    if (!sourceIndex.isValid()) {
        return;
    }

    if (fileModel->isDir(sourceIndex)) {
        QString path = fileModel->filePath(sourceIndex);
        setDirectory(path);
    } else {
        // Open file
        QString filePath = fileModel->filePath(sourceIndex);
        QProcess::startDetached("xdg-open", QStringList() << filePath);
    }
}

QModelIndex QtFileIconView::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!proxyModel) {
        return proxyIndex;
    }
    return proxyModel->mapToSource(proxyIndex);
}

void QtFileIconView::newDirectory()
{
    QMessageBox::information(this, "New Directory", "New directory functionality");
}

void QtFileIconView::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            {
                QModelIndexList selected = selectionModel()->selectedIndexes();
                if (!selected.isEmpty()) {
                    itemDoubleClicked(selected.first());
                    return;
                }
            }
            break;
    }
    
    // Pass other keys to parent
    QTreeView::keyPressEvent(e);
}

