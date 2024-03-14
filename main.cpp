/****************************************************************************
** Copyright (C) 2005 Artem Nagornyi. All rights reserved
**
** This file is part of Palmyra File Manager. This program
** may be used and distributed under the GPL v2
*****************************************************************************/

#include "palmyrafm.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QTranslator>
#include <QUrl>
#include <QVariant>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QListViewItem>
#include <QTimer>
#include <QPoint>
#include <QListView>

int main(int argc, char **argv)
{
  // клас програми
  QApplication a(argc, argv);
  // створення вікна допоміжного класу Copier, необхідного для копіювання при перетягуванні файлів чи каталогів
  Copier mywindow;
  // створення головного вікна
  FileMainWindow mw;
  // задання розмірів головному вікну
  mw.resize(680, 480);
  // початкова директорія файлового менеджера - корінний каталог
  mw.fileView()->setDirectory("/");
  // показ головного вікна
  mw.show();
  return QApplication::exec();
}
