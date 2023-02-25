/****************************************************************************
** $Id: palmyrafm/palmyrafm.cpp   1.0   edited Jan 4 00:25 $
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

// включення заголовочних файлів

#include "palmyrafm.h"
#include "dirview.h"

#include <qsplitter.h>
#include <qprogressbar.h>
#include <qlabel.h>
#include <qstatusbar.h>
#include <qtoolbar.h>
#include <qcombobox.h>
#include <qtoolbutton.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qfile.h>
#include <qstring.h>
#include <qtextstream.h>
#include <qpainter.h>
#include <qstringlist.h>
#include <qpixmap.h>
#include <qmime.h>
#include <qstrlist.h>
#include <qdragobject.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <qpopupmenu.h>
#include <qcursor.h>
#include <qapplication.h>
#include <qwmatrix.h>
#include <qprocess.h>
#include <qobject.h>
#include <qvbox.h>
#include <stdlib.h>

// створення різноманітних значків для програми

static const char* remove_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "....*******....",
    "...*aaaaaaa*...",
    "***************",
    "*aaaaaa*aaaaaa*",
    "*aaaa*****aaaa*",
    "*a***********a*",
    "*a*aaaaaaaaa*a*",
    "*aa*aaaaaaa*aa*",
    "*aa*aaaaaaa*aa*",
    "*aaa*aaaaa*aaa*",
    "*aaa*aaaaa*aaa*",
    "*aaaa*****aaaa*",
    "***************"};

static const char* about_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "...**********..",
    "...**********..",
    "...**......**..",
    "...**......**..",
    "...**......**..",
    "...**********..",
    "...**********..",
    "...**..........",
    "...**...**.....",
    "...**...**.....",
    "...**...**.....",
    "...**...*****..",
    "...**...*****.."};

static const char* update_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "....*******....",
    "...*aaaaaaa*...",
    "***************",
    "***aaaaaaaa**a*",
    "*a**aaaaaa**aa*",
    "*aa**aaaa**aaa*",
    "*a****aa*****a*",
    "*a***********a*",
    "*a***********a*",
    "*aaa**aa**aaaa*",
    "*aa**aaaa**aaa*",
    "*a**aaaaaa**aa*",
    "***************"};

static const char* updateonce_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "....*******....",
    "...*aaa*aaa*...",
    "***************",
    "*aaaa***aaaaaa*",
    "*aaa****aaaaaa*",
    "*aaaaa**aaaaaa*",
    "*a***********a*",
    "*a***********a*",
    "*a***********a*",
    "*aaa**aa**aaaa*",
    "*aa**aaaa**aaa*",
    "*a**aaaaaa**aa*",
    "***************"};

static const char* paste_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "....*******....",
    "...*aaaaaaa*...",
    "***************",
    "*****aaaaaaaaa*",
    "*a***aaaaaaaaa*",
    "*aa**aaaaaaaaa*",
    "*aaa**aaaaaaaa*",
    "*aaaa**aaaaaaa*",
    "*aaa********aa*",
    "*aa**********a*",
    "*aa**aaaaaaa*a*",
    "*aaa***aaaaaaa*",
    "***************"};

static const char* copy_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "....*******....",
    "...*aaaaaaa*...",
    "***************",
    "*aaaaa*a*aaaaa*",
    "*aaaa**a**aaaa*",
    "*aaaa**a**aaaa*",
    "*aaa**aaa**aaa*",
    "*aa**aaaaa**aa*",
    "******aa*******",
    "*****aaaa******",
    "*aaa**aa**aaaa*",
    "*aaa**aa**aaaa*",
    "***************"};

static const char* rename_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "....*******....",
    "...*aaaaaaa*...",
    "***************",
    "*aaaaaaaaaaaaa*",
    "*aa*********aa*",
    "*aa***aaaaa*aa*",
    "*aa*********aa*",
    "*aaaaaaaaaaaaa*",
    "*aa*********aa*",
    "*aa******aa*aa*",
    "*aa*********aa*",
    "*aaaaaaaaaaaaa*",
    "***************"};

static const char* cut_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "....*******....",
    "...*aaaaaaa*...",
    "***************",
    "**aaaaaaaaaa*a*",
    "*a**aaaaaa**aa*",
    "*aa**aaa***aaa*",
    "*aaa**a**aaaaa*",
    "*aaa*****aaaaa*",
    "*aaa**aa**aaaa*",
    "*a****aaa****a*",
    "*a*aa*aaa*aa*a*",
    "*a****aaa****a*",
    "***************"};


static const char* cdtoparent_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "..*****........",
    ".*aaaaa*.......",
    "***************",
    "*aaaaaaaaaaaaa*",
    "*aaaa*aaaaaaaa*",
    "*aaa***aaaaaaa*",
    "*aa*****aaaaaa*",
    "*aaaa*aaaaaaaa*",
    "*aaaa*aaaaaaaa*",
    "*aaaa******aaa*",
    "*aaaaaaaaaaaaa*",
    "*aaaaaaaaaaaaa*",
    "***************"};

static const char* newfolder_xpm[] = {
    "15 14 4 1",
    "   c None",
    ".  c #000000",
    "+  c #FFFF00",
    "@  c #FFFFFF",
    "          .    ",
    "               ",
    "          .    ",
    "       .     . ",
    "  ....  . . .  ",
    " .+@+@.  . .   ",
    "..........  . .",
    ".@+@+@+@+@..   ",
    ".+@+@+@+@+. .  ",
    ".@+@+@+@+@.  . ",
    ".+@+@+@+@+.    ",
    ".@+@+@+@+@.    ",
    ".+@+@+@+@+.    ",
    "...........    "};

static const char * file_icon[]={
    "32 32 17 1",
    "# c #000000",
    "a c #ffffff",
    "j c #808080",
    "n c #a0a0a4",
    "g c #c0c0c0",
    "m c #004000",
    "o c #000000",
    "l c #004040",
    "k c #404000",
    "i c #c0c000",
    "h c #ffff00",
    "b c #ffffc0",
    "e c #ff8000",
    "f c #c05800",
    "c c #ffa858",
    "d c #ffdca8",
    ". c None",
    "................................",
    "................................",
    "................................",
    "................................",
    ".............#....###...........",
    "...###......#a##.#aba##.........",
    "..#cdb#....#aaaa#aaaaaa##.......",
    "..#ecdb#..#aaaa#aaaaaaaba##.....",
    "..#fecdb##aaaa#aaaaaaaaaaab##...",
    "...#fecdb#aaa#aaaaaaabaabaaaa##.",
    "....#fecdb#a#baaaaa#baaaaaabaaa#",
    ".....#fecdb#aaaaab#a##baaaaaaa#.",
    ".....##fecdb#bbba#aaaa##baaab#..",
    "....#bb#fecdb#ba#aaaaaaa##aa#...",
    "...#bbbb#fecdb##aaabaaaaaa##....",
    "..#bbbb#b#fecdb#aaaaaaabaaaa##..",
    ".#bbbb#bbb#fecdg#aaaaaaaaaaaba#.",
    "#hhbb#bbbbb#fegg#iiaaaaaaaaaaaa#",
    "#jhhhklibbbk#ggj#aaiiaaaaaaaaa#j",
    ".#mjhhhkmikab####aaabiiaaaaaa#j.",
    "...##jhhhmaaibbaaiibaaaiiaab#n..",
    ".....##j#baaaiiabaaiibaabaa#n...",
    "......##baibaabiibaaaiiabb#j....",
    "......#bbbbiiaabbiiaaaaabon.....",
    ".....#bbbbbbbiiabbaiiaab#n......",
    ".....#jbbbbbbbbiibaabba#n.......",
    "......##jbbbbbbbbiiaabmj........",
    "........##jbbbbbbbbbb#j.........",
    "..........##nbbbbbbbmj..........",
    "............##jbbbb#j...........",
    "..............#mjj#n............",
    "................##n............."};

static const char * folder_icon[]={
    "32 32 11 1",
    "# c #000000",
    "b c #c0c000",
    "d c #585858",
    "a c #ffff00",
    "i c #400000",
    "h c #a0a0a4",
    "e c #000000",
    "c c #ffffff",
    "f c #303030",
    "g c #c0c0c0",
    ". c None",
    "...###..........................",
    "...#aa##........................",
    ".###baaa##......................",
    ".#cde#baaa##....................",
    ".#cccdeebaaa##..##f.............",
    ".#cccccdeebaaa##aaa##...........",
    ".#cccccccdeebaaaaaaaa##.........",
    ".#cccccccccdeebababaaa#.........",
    ".#cccccgcgghhebbbbbbbaa#........",
    ".#ccccccgcgggdebbbbbbba#........",
    ".#cccgcgcgcgghdeebiebbba#.......",
    ".#ccccgcggggggghdeddeeba#.......",
    ".#cgcgcgcggggggggghghdebb#......",
    ".#ccgcggggggggghghghghd#b#......",
    ".#cgcgcggggggggghghghhd#b#......",
    ".#gcggggggggghghghhhhhd#b#......",
    ".#cgcggggggggghghghhhhd#b#......",
    ".#ggggggggghghghhhhhhhdib#......",
    ".#gggggggggghghghhhhhhd#b#......",
    ".#hhggggghghghhhhhhhhhd#b#......",
    ".#ddhhgggghghghhhhhhhhd#b#......",
    "..##ddhhghghhhhhhhhhhhdeb#......",
    "....##ddhhhghhhhhhhhhhd#b#......",
    "......##ddhhhhhhhhhhhhd#b#......",
    "........##ddhhhhhhhhhhd#b#......",
    "..........##ddhhhhhhhhd#b#......",
    "............##ddhhhhhhd#b###....",
    "..............##ddhhhhd#b#####..",
    "................##ddhhd#b######.",
    "..................##dddeb#####..",
    "....................##d#b###....",
    "......................####......"};

static const char * link_icon[]={
    "32 32 12 1",
    "# c #000000",
    "h c #a0a0a4",
    "b c #c00000",
    "d c #585858",
    "i c #400000",
    "c c #ffffff",
    "e c #000000",
    "g c #c0c0c0",
    "a c #ff0000",
    "f c #303030",
    "n c white",
    ". c None",
    "...###..........................",
    "...#aa##........................",
    ".###baaa##......................",
    ".#cde#baaa##....................",
    ".#cccdeebaaa##..##f.............",
    ".#cccccdeebaaa##aaa##...........",
    ".#cccccccdeebaaaaaaaa##.........",
    ".#cccccccccdeebababaaa#.........",
    ".#cccccgcgghhebbbbbbbaa#........",
    ".#ccccccgcgggdebbbbbbba#........",
    ".#cccgcgcgcgghdeebiebbba#.......",
    ".#ccccgcggggggghdeddeeba#.......",
    ".#cgcgcgcggggggggghghdebb#......",
    ".#ccgcggggggggghghghghd#b#......",
    ".#cgcgcggggggggghghghhd#b#......",
    ".#gcggggggggghghghhhhhd#b#......",
    ".#cgcggggggggghghghhhhd#b#......",
    ".#ggggggggghghghhhhhhhdib#......",
    ".#gggggggggghghghhhhhhd#b#......",
    ".#hhggggghghghhhhhhhhhd#b#......",
    ".#ddhhgggghghghhhhhhhhd#b#......",
    "..##ddhhghghhhhhhhhhhhdeb#......",
    "############hhhhhhhhhhd#b#......",
    "#nnnnnnnnnn#hhhhhhhhhhd#b#......",
    "#nnnnnnnnnn#hhhhhhhhhhd#b#......",
    "#nn#nn#nnnn#ddhhhhhhhhd#b#......",
    "#nn##n##nnn###ddhhhhhhd#b###....",
    "#nnn#####nn#..##ddhhhhd#b#####..",
    "#nnnnn##nnn#....##ddhhd#b######.",
    "#nnnnn#nnnn#......##dddeb#####..",
    "#nnnnnnnnnn#........##d#b###....",
    "############..........####......"};

static const char * folder_locked_icon[]={
    "32 32 12 1",
    "# c #000000",
    "g c #808080",
    "h c #c0c0c0",
    "f c #c05800",
    "c c #ffffff",
    "d c #585858",
    "b c #ffa858",
    "a c #ffdca8",
    "e c #000000",
    "i c #a0a0a4",
    "j c #c0c0c0",
    ". c None",
    "...###..........................",
    "...#aa##........................",
    ".###baaa##......................",
    ".#cde#baaa##....................",
    ".#cccdeeba#######...............",
    ".#cccccde##fffff##..............",
    ".#cccccc##fffgggg#..............",
    ".#ccccccc#ffg####a##............",
    ".#ccccchc#ffg#eebbaa##..........",
    ".#ccccccc#ffg#ddeebbba##........",
    ".#ccchccc#ffg#ihddeebbba##......",
    ".#cccccaa#ffg#ihhhddeeba##......",
    ".#chchhbbaafg#ihhhihidebb#......",
    ".#cchccbbbbaa#ihhihihid#b#......",
    ".#chchhbb#bbbaaiihihiid#b#......",
    ".#hchhcbb#fbbbafhiiiiid#b#......",
    ".#chchhbb#ffgbbfihiiiid#b#......",
    ".#hhhhhbb#ffg#bfiiiiiid#b#......",
    ".#hhhhhbbaffg#bfiiiiiid#b#......",
    ".#iihhhjbbaab#bfiiiiiid#b#......",
    ".#ddiihhh#bbbabfiiiiiid#b#......",
    "..##ddiih#ffbbbfiiiiiid#b#......",
    "....##ddi#ffg#biiiiiiid#b#......",
    "......##d#ffg#iiiiiiiid#b#......",
    "........##ffg#iiiiiiiid#b#......",
    ".........#ffg#iiiiiiiid#b#......",
    ".........#ffg#ddiiiiiid#b###....",
    ".........##fg###ddiiiid#b#####..",
    "...........####.##ddiid#b######.",
    "..................##dddeb#####..",
    "....................##d#b###....",
    "......................####......"};

// обнуління будь яких інших масивів для значків
static QPixmap *iconFolderLockedLarge = 0;
static QPixmap *iconFolderLarge = 0;
static QPixmap *iconFileLarge = 0;
static QPixmap *iconLinkLarge = 0;
static QPixmap *iconFolderLockedDetail = 0;
static QPixmap *iconFolderDetail = 0;
static QPixmap *iconFileDetail = 0;
static QPixmap *iconLinkDetail = 0;

// різноманітні допоміжні глобальні змінні та прапорці, що використовуються в утилітарних цілях

// рахівник зкопійованих до буферу обміну файлів
int cpcount=0;
// періодичне оновлення файлів у вікні з інтервалом у 1 сек. (вмк. або вимк.)
int update_files=-1;
// використовується при читанні файла конфігурації, щоб відрізняти ключ від параметра
int lineflag=1;
// універсальний допоміжний прапорець
int flag_new=0;
// прапорець, що дає програмі знати про процес копіювання для відповідного виведення повідомлення про завершення процесу
int fcp_flag=0;
// прапорець, що дає програмі знати про процес видалення файлів для відповідного виведення повідомлення про завершення процесу
int frm_flag=0;
// прапорець для недопущення виведення вищевказаних повідомлень декілька разів
int msg_flag=0;

// посередній буфер для трансферу імен файлів
QString cpitems=NULL;
// список для зчитування та запису ключів та параметрів з конфігураційного файла програми
QStringList conflines;
// шлях до конфігураційного файлу програми
QFile conffile( "/usr/local/palmyrafm/palmconf.conf" );
// тримач для отримання розширення файлів для відкриття
QFileInfo conffi;
// потік для читання - запису файлу конфігурації
QTextStream confstream( &conffile );
// поточний рядок файлу конфігурації
QString confline;
// розширення файлів для відкриття
QString confext;
// каталог розміщення конфігураційного файлу
QDir checkdir ( "/usr/local/palmyrafm" );
// початковий масив для заповнення файлу конфігурації
QString writeline[22];
// остаточний масив для запису в файл конфігурації
QStringList writelines;

// видалення непотрібних значків
static void cleanup()
{
    delete iconFolderLockedLarge;
    iconFolderLockedLarge = 0;
    delete iconFolderLarge;
    iconFolderLarge = 0;
    delete iconFileLarge;
    iconFileLarge = 0;
    delete iconLinkLarge;
    iconLinkLarge = 0;
    delete iconFolderLockedDetail;
    iconFolderLockedDetail = 0;
    delete iconFolderDetail;
    iconFolderDetail = 0;
    delete iconFileDetail;
    iconFileDetail = 0;
    delete iconLinkDetail;
    iconLinkDetail = 0;
}

// клас головного вікна програми
FileMainWindow::FileMainWindow() 
: QMainWindow()
{
    setup();
}

// метод показу гол. вікна програми
void FileMainWindow::show()
{
    QMainWindow::show();
}

// метод формування головного вікна програми
void FileMainWindow::setup()
{
    // розділювач лівої та правої панелей
    QSplitter *splitter = new QSplitter( this );
    // формування лівої панелі
    dirlist = new DirectoryView( splitter, "dirlist", TRUE );
    // додавання стовпчиків до лівої панелі
    dirlist->addColumn( "Name" );
    dirlist->addColumn( "Type" );
    // визначення корінного каталогу для лівої панелі
    Directory *root = new Directory( dirlist, "/" );
    // відкриття корінного каталогу
    root->setOpen( TRUE );
    // розділювач відходить на розмір лівої панелі
    splitter->setResizeMode( dirlist, QSplitter::KeepSize );
    // формування правої панелі
    fileview = new QtFileIconView( "/", splitter );
    // режим показу файлів "розширений" для правої панелі
    fileview->setSelectionMode( QIconView::Extended );
    // центральний віджет - розділювач
    setCentralWidget( splitter );
    // перша панель інструментів - з кнопками
    QToolBar *toolbar1 = new QToolBar( "tools", this, this, TRUE, 0, 0 );
    QPixmap pix;
    // кнопки з написами
    setUsesTextLabel(TRUE);
    // використовувати збільшені значки
    setUsesBigPixmaps( TRUE );
    // найменування панелі інструментів
    (void)new QLabel( tr( " Operations: " ), toolbar1 );
    // відступи
    toolbar1->addSeparator();
    toolbar1->addSeparator();
    // кнопка переходу на верхній каталог
    pix = QPixmap( cdtoparent_xpm );
    upButton = new QToolButton( pix,"Go Up" , "Go Up",
                this, SLOT( cdUp() ), toolbar1, "cd up" );
    // кнопка створення нової директорії
    pix = QPixmap( newfolder_xpm );
    mkdirButton = new QToolButton( pix,"New Folder" , "New Folder",
                   this, SLOT( newFolder() ), toolbar1, "new folder" );
    // відступи
    toolbar1->addSeparator();
    toolbar1->addSeparator();
    
    // кнопка вирізання файлів   
    pix = QPixmap( cut_xpm );
    mkdirButton = new QToolButton( pix,"Cut" , "Cut",
               this, SLOT( cut() ), toolbar1, "cut" );

    // кнопка копіювання файлів
    pix = QPixmap( copy_xpm );
    mkdirButton = new QToolButton( pix,"Copy" , "Copy",
               this, SLOT( copy() ), toolbar1, "copy" );

    // кнопка вставки файлів
    pix = QPixmap( paste_xpm );
    mkdirButton = new QToolButton( pix,"Paste" , "Paste",
               this, SLOT( paste() ), toolbar1, "paste" );
    
    // відступ
    toolbar1->addSeparator();

    // кнопка перейменування файла
    pix = QPixmap( rename_xpm );
    mkdirButton = new QToolButton( pix,"Rename" , "Rename",
               this, SLOT( rename() ), toolbar1, "rename" );

    // кнопка знищення файлів
    pix = QPixmap( remove_xpm );
    mkdirButton = new QToolButton( pix, "Delete", "Delete",
               this, SLOT( remove() ), toolbar1, "remove" );
    
    // відступи
    toolbar1->addSeparator();
    toolbar1->addSeparator();

    // кнопка увімкнення постійного оновлення файлів
    pix = QPixmap( update_xpm );
    mkdirButton = new QToolButton( pix,"Regular Update" , "Regular Update",                 this, SLOT( update() ), toolbar1, "update" );

    // кнопка одноразового оновлення файлів
    pix = QPixmap( updateonce_xpm );
    mkdirButton = new QToolButton( pix, "Update Once", "Update Once",
               this, SLOT( updateonce() ), toolbar1, "updateonce" );
    
    // кнопка виклику інформації про програму
    pix = QPixmap( about_xpm );
    mkdirButton = new QToolButton( pix, "ABOUT", "ABOUT",
               this, SLOT( about() ), toolbar1, "about" );

    // створення другої панелі інструментів - з шляхом до поточного каталогу
    QToolBar *toolbar = new QToolBar( this, "toolbar" );
    setRightJustification( TRUE );
    
    // найменування панелі
    (void)new QLabel( tr( " Path: " ), toolbar );

    // додавання елементу управління QComboBox
    pathCombo = new QComboBox( TRUE, toolbar );
    pathCombo->setAutoCompletion( TRUE );
    toolbar->setStretchableWidget( pathCombo );
    
    // поєднання певних сигналів програми з відповідними слотами
    connect( pathCombo, SIGNAL( activated( const QString & ) ),
        this, SLOT ( changePath( const QString & ) ) );
    connect( dirlist, SIGNAL( folderSelected( const QString & ) ),
         fileview, SLOT ( setDirectory( const QString & ) ) );
    connect( fileview, SIGNAL( directoryChanged( const QString & ) ),
         this, SLOT( directoryChanged( const QString & ) ) );
    connect( fileview, SIGNAL( startReadDir( int ) ),
         this, SLOT( slotStartReadDir( int ) ) );
    connect( fileview, SIGNAL( readNextDir() ),
         this, SLOT( slotReadNextDir() ) );
    connect( fileview, SIGNAL( readDirDone() ),
         this, SLOT( slotReadDirDone() ) );
    
    // додавання та конфігурація статусного рядка внизу екрана
    setDockEnabled( DockLeft, FALSE );
    setDockEnabled( DockRight, FALSE );
    label = new QLabel( statusBar() );
    statusBar()->addWidget( label, 2, TRUE );
    progress = new QProgressBar( statusBar() );
    statusBar()->addWidget( progress, 1, TRUE );

    // поєднання певних сигналів програми з відповідними слотами
    connect( fileview, SIGNAL( enableUp() ),
         this, SLOT( enableUp() ) );
    connect( fileview, SIGNAL( disableUp() ),
         this, SLOT( disableUp() ) );
    connect( fileview, SIGNAL( enableMkdir() ),
         this, SLOT( enableMkdir() ) );
    connect( fileview, SIGNAL( disableMkdir() ),
         this, SLOT( disableMkdir() ) );
}

// метод установки статусного рядка
void FileMainWindow::setPathCombo()
{
    QString dir = caption();
    int i = 0;
    bool found = FALSE;
    for ( i = 0; i < pathCombo->count(); ++i ) 
    {
        if ( pathCombo->text( i ) == dir) 
        {
            found = TRUE;
            break;
        }
    }

    if ( found ) pathCombo->setCurrentItem( i );
    else 
    {
        pathCombo->insertItem( dir );
        pathCombo->setCurrentItem( pathCombo->count() - 1 );
    }

}

// метод зміни напису у елементі - випадаючий список, відповідно до зміни каталогу
void FileMainWindow::directoryChanged( const QString &dir )
{
    setCaption( dir );
    setPathCombo();
}

// слот початку читання директорії
void FileMainWindow::slotStartReadDir( int dirs )
{
    label->setText( tr( " Reading Directory..." ) );
    progress->reset();
    progress->setTotalSteps( dirs );
}

// слот наступного кроку читання директорії
void FileMainWindow::slotReadNextDir()
{
    int p = progress->progress();
    progress->setProgress( ++p );
}

// слот остаточного кроку читання директорії
void FileMainWindow::slotReadDirDone()
{
    label->setText( tr( " Reading Directory Done." ) );
    progress->setProgress( progress->totalSteps() );
}

// метод переходу на верхній каталог
void FileMainWindow::cdUp()
{
    QDir dir = fileview->currentDir();
    dir.cd( ".." );
    fileview->setDirectory( dir );
}

// метод створення нової директорії
void FileMainWindow::newFolder()
{
    fileview->newDirectory();
}

// метод вирізання файлів
void FileMainWindow::cut ()
{
    fileview->cut_prev();
}

// метод копіювання файлів
void FileMainWindow::copy ()
{
    fileview->copy_prev();
}

// метод вставки файлів
void FileMainWindow::paste ()
{
    fileview->paste();
}

// метод перейменування файлів
void FileMainWindow::rename ()
{
    fileview->rename_prev();
}

// метод видалення файлів
void FileMainWindow::remove ()
{
    fileview->remove_prev();
}

// метод увімкнення періодичного оновлення файлів
void FileMainWindow::update ()
{
    fileview->update();
}

// метод одноразового оновлення файлів
void FileMainWindow::updateonce ()
{
    fileview->updateonce();
}

// метод виклику інформації про програму
void FileMainWindow::about ()
{
    QMessageBox::about(this,tr("About Palmyra File Manager"),
        tr("Palmyra File Manager v.1.0\n(c) 2005 Artem Nahorny aka nA[0]\nThis program is distributed under the terms of the GPL v.2\n\nAttention:\n    Configuration file named palmconf.conf is placed by program during first run\n  at /usr/local/palmyrafm directory, that is created also\n\nFormat of configuration file:\n  extension of a file\n   desired program to run a file"));   
}

// метод зміни поточного каталогу
void FileMainWindow::changePath( const QString &path )
{
    if ( QFileInfo( path ).exists() ) fileview->setDirectory( path );
    else setPathCombo();
}

// метод "освітлення" кнопки переходу на верхній рівень
void FileMainWindow::enableUp()
{
    upButton->setEnabled( TRUE );
}

// метод "затінення" кнопки переходу на верхній рівень
void FileMainWindow::disableUp()
{
    upButton->setEnabled( FALSE );
}

// метод "освітлення" кнопки створення каталогу
void FileMainWindow::enableMkdir()
{
    mkdirButton->setEnabled( TRUE );
}

// метод "затінення" кнопки створення каталогу
void FileMainWindow::disableMkdir()
{
    mkdirButton->setEnabled( FALSE );
}

/*****************************************************************************
 *
 * Class Copier
 *
 *****************************************************************************/

// клас, необхідний для копіювання при перетягуванні файлів
Copier::Copier()
{
    proc = new QProcess( this );
    proc->addArgument( "cd" );
}

// метод класу, що служить вищевказаним цілям при виклику з відповідного методу
void Copier::copy()
{
    proc->clearArguments();
    proc->addArgument("kwrite");
    proc->addArgument( "/sample.art" );
    proc->start();
}

/*****************************************************************************
 *
 * Class QtFileIconDrag
 *
 *****************************************************************************/

// клас, необхідний для організації перетягування файлів
QtFileIconDrag::QtFileIconDrag( QWidget * dragSource, const char* name )
    : QIconDrag( dragSource, name )
{
}

// метод класу, необхідний для повернення типу елементів каталогу для перетягування
const char* QtFileIconDrag::format( int i ) const
{
    if ( i == 0 ) return "application/x-qiconlist";
    else if ( i == 1 ) return "text/uri-list";
    else return 0;
}

// метод класу, необхідний для кодування імен файлів для здійснення операції перетягування
QByteArray QtFileIconDrag::encodedData( const char* mime ) const
{
    QByteArray a;
    if ( QString( mime ) == "application/x-qiconlist" ) 
    {
        a = QIconDrag::encodedData( mime );
    } 
    else if ( QString( mime ) == "text/uri-list" ) 
    {
        QString s = urls.join( "\r\n" );
        a.resize( s.length() );
        memcpy( a.data(), s.latin1(), s.length() );
    }
    return a;
}

// повернення значення можливості декодування імен файлів
bool QtFileIconDrag::canDecode( QMimeSource* e )
{
    return e->provides( "application/x-qiconlist" ) || e->provides( "text/uri-list" );
}

// метод додавання імен файлів до закодованого списку
void QtFileIconDrag::append( const QIconDragItem &item, const QRect &pr,
                 const QRect &tr, const QString &url )
{
    QIconDrag::append( item, pr, tr );
    QString ourUrl = url;    
    urls << QUriDrag::localFileToUri(ourUrl);
}

/*****************************************************************************
 *
 * Class QtFileIconViewItem
 *
 *****************************************************************************/

// клас підтримки відображення та управління елементами каталогу
QtFileIconViewItem::QtFileIconViewItem( QtFileIconView *parent, QFileInfo *fi )
    : QIconViewItem( parent, fi->fileName() ), itemFileName( fi->filePath() ),
      itemFileInfo( fi ), checkSetText( FALSE ), Copier()
{
    vm = QtFileIconView::Detail;
    QObject::connect ( &timer, SIGNAL( timeout() ),iconView(), SLOT( openFolder() ) );
        
    if ( itemFileInfo->isDir() ) itemType = Dir;
    else if ( itemFileInfo->isFile() ) itemType = File;
    if ( itemFileInfo->isSymLink() ) itemType = Link;
    viewModeChanged( ( (QtFileIconView*)iconView() )->viewMode() );
    if ( itemFileInfo->fileName() == "." || itemFileInfo->fileName() == ".." )
    setRenameEnabled( FALSE );
    checkSetText = TRUE;
}

// метод класу для виведення на екран назви елемента каталогу у певному шрифті та кольорі
void QtFileIconViewItem::paintItem( QPainter *p, const QColorGroup &cg )
{
    if ( itemFileInfo->isSymLink() )
    {
        QFont f( p->font() );
        f.setItalic( TRUE );
        p->setFont( f );
    }

    QIconViewItem::paintItem( p, cg );
}

// метод зміни режиму відображення елементів каталогу
void QtFileIconViewItem::viewModeChanged( QtFileIconView::ViewMode m )
{
    vm = m;
    setDropEnabled( itemType == Dir && QDir( itemFileName ).isReadable() );
    calcRect();
}

// метод для відображення елемента каталогу певним значком, у залежності від типу файла 
QPixmap *QtFileIconViewItem::pixmap() const
{
    switch ( itemType ) 
    {
        case Dir:
        {
            if ( !QDir( itemFileName ).isReadable() ) 
            {
                if ( vm == QtFileIconView::Detail ) return iconFolderLockedDetail;
                else return iconFolderLockedLarge;
            } 
            else 
            {
                if ( vm == QtFileIconView::Detail ) return iconFolderDetail;
                else return iconFolderLarge;
            }
        }
        case Link:
        {
            if ( vm == QtFileIconView::Detail ) return iconLinkDetail;
            else return iconLinkLarge;
        }
        default:
        {
            if ( vm == QtFileIconView::Detail ) return iconFileDetail;
            else return iconFileLarge;
        }
    }
}

// деструктор цього класу
QtFileIconViewItem::~QtFileIconViewItem()
{
    delete itemFileInfo;
}

// призначення тексту, яким підписані значки, що відображають елементи каталогу
void QtFileIconViewItem::setText( const QString &text )
{
    if ( checkSetText ) 
    {
        if ( text == "." || text == "." || text.isEmpty() ) return;
        QDir dir( itemFileInfo->dir() );
        if ( dir.rename( itemFileInfo->fileName(), text ) ) 
        {
            itemFileName = itemFileInfo->dirPath( TRUE ) + "/" + text;
            delete itemFileInfo;
            itemFileInfo = new QFileInfo( itemFileName );
            QIconViewItem::setText( text );
        }
    } 
    else 
    {
        QIconViewItem::setText( text );
    }
}

// метод для приймання закодованого списку URL перетягуваних елементів каталогу
bool QtFileIconViewItem::acceptDrop( const QMimeSource *e ) const
{
    if ( type() == Dir && e->provides( "text/uri-list" ) && dropEnabled() ) return TRUE;
    return FALSE;
}

// метод - обробник перетягуваних елементів каталогу, що декодує їх список URL
void QtFileIconViewItem::dropped( QDropEvent *e, const QValueList<QIconDragItem> & )
{
    timer.stop();
    if ( !QUriDrag::canDecode( e ) ) 
    {
        e->ignore();
        return;
    }

    QStringList lst;
    QUriDrag::decodeLocalFiles( e, lst );

    QString str;
    if ( e->action() == QDropEvent::Copy ) str = "Copy\n\n";
    else str = "Move\n\n";
    for ( uint i = 0; i < lst.count(); ++i ) str += QString( "   %1\n" ).arg( lst[i] );
    str += QString( "\n"
        "To\n\n"
        "   %1" ).arg( filename() );
    QMessageBox::information( iconView(), e->action() == QDropEvent::Copy ? "Copy" : "Move" , str, "Not Implemented" );
    e->acceptAction();
}

// метод для входу та визначення інтервалу входу перетягуваних елементів до каталога - цілі через певний проміжок часу
void QtFileIconViewItem::dragEntered()
{
    if ( type() != Dir || type() == Dir && !QDir( itemFileName ).isReadable() ) return;
    ( (QtFileIconView*)iconView() )->setOpenItem( this );
    timer.start( 1500 );
}

// метод для здійснення "відпускання" перетягуваних елементів у певному місці для вставки
void QtFileIconViewItem::dragLeft()
{
    if ( type() != Dir || type() == Dir && !QDir( itemFileName ).isReadable() ) return;
    timer.stop();
}

/*****************************************************************************
 *
 * Class QtFileIconView
 *
 *****************************************************************************/

// клас, методи якого реалізують всі операції з файлами
// тобто копіювання, знищення, оновлення, відкриття зовнішніми програмами, тощо
QtFileIconView::QtFileIconView( const QString &dir, QWidget *parent, const char *name )
    : QIconView( parent, name ), viewDir( dir ), newFolderNum( 0 )
{
    // створення нового екземпляру процесу для виклику зовнішніх програм
    // для здійснення операцій над файлами
    proc1 = new QProcess( this );
    proc1->addArgument( "cd" );
    
    // присвоєння значкам різних зображень
    if ( !iconFolderLockedLarge ) 
    {
        qAddPostRoutine( cleanup );
        QWMatrix m;
        m.scale( 0.6, 0.6 );
        QPixmap iconpix( folder_locked_icon );
        iconFolderLockedLarge = new QPixmap( folder_locked_icon );
        iconpix = iconpix.xForm( m );
        iconFolderLockedDetail = new QPixmap( iconpix );
        iconpix = QPixmap( folder_icon );
        iconFolderLarge = new QPixmap( folder_icon );
        iconpix = iconpix.xForm( m );
        iconFolderDetail = new QPixmap( iconpix );
        iconpix = QPixmap( file_icon );
        iconFileLarge = new QPixmap( file_icon );
        iconpix = iconpix.xForm( m );
        iconFileDetail = new QPixmap( iconpix );
        iconpix = QPixmap( link_icon );
        iconLinkLarge = new QPixmap( link_icon );
        iconpix = iconpix.xForm( m );
        iconLinkDetail = new QPixmap( iconpix );
    }
    // початковий режим відображення - малі значки
    vm = Detail;
    // встанговлення розміру сітки елементів каталогу
    setGridX( 75 );
    // режим здійснення розтягнення
    setResizeMode( Adjust );
    // початкове значення режиму укорочення назв елементів каталогу для зручності відображення
    setWordWrapIconText( FALSE );
    // створення внутрішнього таймеру програми
    internalTimer = new QTimer( this );
    // під"єднання сигналу, що видає таймер, до слоту, що прокликаний обробляти його
    connect( internalTimer, SIGNAL(timeout()), SLOT(regupdate()) );
    // запуск таймеру з видачею сигналу таймауту щосекунди
    internalTimer->start( 1000 );

    // під"єднання сигналів методів класу до відповідних слотів - обробників
    connect( this, SIGNAL( doubleClicked( QIconViewItem * ) ),
         this, SLOT( itemDoubleClicked( QIconViewItem * ) ) );
    connect( this, SIGNAL( returnPressed( QIconViewItem * ) ),
         this, SLOT( itemDoubleClicked( QIconViewItem * ) ) );
    connect( this, SIGNAL( dropped( QDropEvent *, const QValueList<QIconDragItem> & ) ),
         this, SLOT( slotDropped( QDropEvent *, const QValueList<QIconDragItem> & ) ) );
    connect( this, SIGNAL( contextMenuRequested( QIconViewItem *, const QPoint & ) ),
         this, SLOT( slotRightPressed( QIconViewItem * ) ) );

    // вимкнення горизонтальної прокрутки
    setHScrollBarMode( AlwaysOff );
    // вертикальну прокрутку - у автоматичний режим
    setVScrollBarMode( Auto );
    // призначення автоматичного розміщення значків
    setAutoArrange( TRUE );
    // увімкнення режиму сортування елементів каталогу
    setSorting( TRUE );
    // допоміжний параметр
    openItem = 0;
}

// метод класу, що здійснює автоматичне оновлення елементів каталогу щосекунди
// а також призначений слідкувати за процесом виконання у фоні операцій копіювання, переміщення та знищення файлів
void QtFileIconView::regupdate()
{
    // домоміжний прапорець, значення якого забороняє автооновлення при виділених елементах каталогу
    int flag_selected=0;
    
    // перевірка виділень
    for ( QtFileIconViewItem *item = (QtFileIconViewItem*)firstItem(); item; item = (QtFileIconViewItem*)item->nextItem() ) {
       if (item->isSelected()) {
        flag_selected=1;
        }
    }

    // перевірка стану операції копіювання файлів; якщо виконане, тоді виведення повідомлення про це
    if ((fcp_flag==1)&&(msg_flag==1))
    {
        if (proc1->isRunning()==FALSE) 
        {
                msg_flag=2;
                fcp_flag=0;
                QMessageBox::information( this, "Information", "Copying finished", "Well done");
                viewDir = QDir( viewDir.absPath() );
                readDir( viewDir );
        }
    }

    // перевірка стану операції знищення файлів; якщо виконане, тоді виведення повідомлення про це
    if ((frm_flag==1)&&(msg_flag==1))
    {
        if (proc1->isRunning()==FALSE) 
        {
                frm_flag=0;
                msg_flag=2;
                QMessageBox::information( this, "Information", "Deleting finished", "Well done");
                viewDir = QDir( viewDir.absPath() );
                readDir( viewDir );
        }
    }
    
    // автооновлення щосекунди, якщо немає виділень
    if((flag_selected==0)&&(update_files==1))
    {
        viewDir = QDir( viewDir.absPath() );
        readDir( viewDir );
    }
    flag_selected=0;
}

// метод класу, що запускає зовнішню програму копіювання або переміщення файлів
// після схвальної відповіді на запитання користувачеві
void QtFileIconView::copy1( QString cpdir )
{
    QMessageBox mb( "Copying",
        "Program is starting files copying process.\n"
        "Do you really want to proceed?",
        QMessageBox::Information,
        QMessageBox::Yes | QMessageBox::Default,
        QMessageBox::No,
        QMessageBox::Cancel | QMessageBox::Escape );
    mb.setButtonText( QMessageBox::Yes, "Copy" );
    mb.setButtonText( QMessageBox::No, "No" );
    switch( mb.exec() ) 
    {
        case QMessageBox::Yes:
            // save and exit
        proc1->addArgument( cpdir );
        proc1->start();
        fcp_flag=1;
        msg_flag=1; 
            break;
        case QMessageBox::No:
            // exit without saving
            break;
        case QMessageBox::Cancel:
            // don't save and don't exit
            break;
    }
}

// метод відкриття директорії
void QtFileIconView::openFolder()
{
    if ( !openItem ) return;
    if ( openItem->type() != QtFileIconViewItem::Dir || openItem->type() == QtFileIconViewItem::Dir && !QDir( openItem->itemFileName ).isReadable() ) return;
    openItem->timer.stop();
    setDirectory( openItem->itemFileName );
}

// метод призначення нової директорії по імені директорії, тобто її абсолютному шляху
void QtFileIconView::setDirectory( const QString &dir )
{
    viewDir = QDir( dir );
    readDir( viewDir );
}

// метод призначення нової директорії по тримачу директорії
void QtFileIconView::setDirectory( const QDir &dir )
{
    viewDir = dir;
    readDir( viewDir );
}

// метод створення нової директорії, згідно імені, яке вводить користувач
void QtFileIconView::newDirectory()
{
    setAutoArrange( FALSE );
    selectAll( FALSE );
    if ( viewDir.mkdir( QString( "New Folder %1" ).arg( ++newFolderNum ) ) ) 
    {
        QFileInfo *fi = new QFileInfo( viewDir, QString( "New Folder %1" ).arg( newFolderNum ) );
        QtFileIconViewItem *item = new QtFileIconViewItem( this, new QFileInfo( *fi ) );
        item->setKey( QString( "000000%1" ).arg( fi->fileName() ) );
        delete fi;
        repaintContents( contentsX(), contentsY(), contentsWidth(), contentsHeight(), FALSE );
        ensureItemVisible( item );
        item->setSelected( TRUE, TRUE );
        setCurrentItem( item );
        repaintItem( item );
        qApp->processEvents();
        item->rename();
    }
    setAutoArrange( TRUE );
}

// метод для отримання тримача на поточний каталог
QDir QtFileIconView::currentDir()
{
    return viewDir;
}

// метод для визначення правдивості твердження, що поточна директорія - коренева
static bool isRoot( const QString &s )
{
    if ( s == "/" ) return TRUE;
    return FALSE;
}

// метод для читання директорії
// також у ньому реалізовано перевірку існування файла конфігурації програми
// у відповідному каталогу та створення його у разі необхідності (при першому запуску програми)
// та заповнення первісними даними
void QtFileIconView::readDir( const QDir &dir )
{
    // перевірка існування каталогу
    // якщо не існує - створення його
    if ( !checkdir.exists() )
    {
        checkdir.mkdir("/usr/local/palmyrafm", TRUE);
    }
    // перевірка існування файла конфігурації
    if (conffile.exists()==FALSE)
    {
        // спроба створення порожнього файлу конфігурації шляхом відкриття файла у відповідному режимі
        if((conffile.open( IO_ReadWrite )==FALSE)&&(flag_new==0))
        {
            // виведення повідомлення про неможливість створення файлу у разі невдачі
            QMessageBox::information( this, "Attention", "Config file was not created, probably not enough rights!", "I'll check my rights");
            flag_new=1;
        }
        // закриття файлу конфігурації
        conffile.close();
        
        // занесення ключів та параметрів до файлу конфігурації, щодо відкриття файлів з
        // певним розширенням певними програмами
        writeline[0]="txt";
        writeline[1]="kwrite";
        writeline[2]="log";
        writeline[3]="kedit";
        writeline[4]="cpp";
        writeline[5]="gvim";
        writeline[6]="h";
        writeline[7]="emacs";
        writeline[8]="c";
        writeline[9]="gvim";
        writeline[10]="hpp";
        writeline[11]="emacs";
        writeline[12]="nao";
        writeline[13]="abiword";
        writeline[14]="doc";
        writeline[15]="kword";
        writeline[16]="xls";
        writeline[17]="gnumeric";
        writeline[18]="mp3";
        writeline[19]="xmms";
        writeline[20]="wma";
        writeline[21]="xmms";
        // процедура запису ключів та параметрів до проміжного списка, для наступного запису його в файл
        for (int cnter=0; cnter<=21; cnter++)
        {
            writelines += writeline[cnter];
        }
        // запис списка з ключами та параметрами до конфігураційного файла
        if ( conffile.open( IO_WriteOnly ) ) 
        {
            for ( QStringList::Iterator it = writelines.begin(); it != writelines.end(); ++it ) confstream << *it << "\n";
            conffile.close();
        }
    }
    // повернення, якщо директорія не читається
    if ( !dir.isReadable() ) return;
    // якщо кореневий каталог, то сигнал про затінення кнопки переміщення вгору
    if ( isRoot( dir.absPath() ) ) emit disableUp();
    // якщо не кореневий, то освітлення кнопки "вгору"
    else emit enableUp();
    // очищення вмісту головного вікна, знищення всіх елементів
    clear();
    // сигнал про зміну директорії
    emit directoryChanged( dir.absPath() );
    // формування нового списку елементів каталогу
    const QFileInfoList *filist = dir.entryInfoList( QDir::DefaultFilter, QDir::DirsFirst | QDir::Name );
    // посилка сигналу про початок читання лиректорії
    emit startReadDir( filist->count() );
    
    // створення ітератора елементів каталога
    QFileInfoListIterator it( *filist );
    // створення тримача для отримання інформації про файли
    QFileInfo *fi;
    // відміна дозволу на перейменування елементів на час читання каталогу
    bool allowRename = FALSE, allowRenameSet = FALSE;
    // власне процедура створення у головному вікні нових елементів каталога з використанням
    // ітератора та списка
    while ( ( fi = it.current() ) != 0 ) 
    {
        ++it;
        if ( fi && fi->fileName() == ".." && ( fi->dirPath() == "/" || fi->dirPath().isEmpty() ) ) continue;
        emit readNextDir();
        QtFileIconViewItem *item = new QtFileIconViewItem( this, new QFileInfo( *fi ) );
        if ( fi->isDir() ) item->setKey( QString( "000000%1" ).arg( fi->fileName() ) );
        else item->setKey( fi->fileName() );
        if ( !allowRenameSet ) 
        {
            if ( !QFileInfo( fi->absFilePath() ).isWritable() || item->text() == "." || item->text() == ".." )
            allowRename = FALSE;
            else allowRename = TRUE;
            if ( item->text() == "." || item->text() == ".." )
            allowRenameSet = FALSE;
            else allowRenameSet = TRUE;
        }
        // встановлення дозволу на перейменування елементів каталога
        item->setRenameEnabled( allowRename );
    }
    // якщо немає прав на запис каталогу - затінити кнопку створення нового каталога
    if ( !QFileInfo( dir.absPath() ).isWritable() ) emit disableMkdir();
    // у зворотньому разі - освітлити
    else emit enableMkdir();
    // посилка сигналу про закінчення читання каталога
    emit readDirDone();
}

// метод обробки подвійного клацання мишею
// для відкриття каталогів та файлів у зовнішніх програмах-редакторах
void QtFileIconView::itemDoubleClicked( QIconViewItem *i )
{
    QtFileIconViewItem *item = ( QtFileIconViewItem* )i;
    
    // якщо елемент - каталог, прочитати його
    if ( item->type() == QtFileIconViewItem::Dir ) 
    {
        viewDir = QDir( item->filename() );
        readDir( viewDir );
    } 
    // якщо елемент посилання на каталог - перейти по ньому і прочитати каталог
    else if ( item->type() == QtFileIconViewItem::Link &&
        QFileInfo( QFileInfo( item->filename() ).readLink() ).isDir() ) 
    {
        viewDir = QDir( QFileInfo( item->filename() ).readLink() );
        readDir( viewDir );
    }
    // якщо елемент - файл
    else
    {
        // якщо файл - виконуваний, відкрити його
        if (QFileInfo(item->filename()).isExecutable()==TRUE)
        {
            proc1->clearArguments();
            proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));
            proc1->start();
            // перевірка, якщо виконуваний файл має розширення
            // то не запускати його, а спробувати відкрити
            // ймовірно це пов"язано з некоректним копіюванням файлів з іншої файлової системи
            // аніж EXT2 чи EXT3
            if(QFileInfo(item->filename()).extension()!="")
            {
                if ( conffile.open( IO_ReadOnly ) )
                {
                    conffi.setFile( item->text() );
                    confext = conffi.extension( FALSE );
                    lineflag=0;
                    // відповідне читання конфігураційного файла для коректного відкриття
                    while ( !confstream.eof() )
                    {
                        confline = confstream.readLine();
                        if (lineflag==1)
                        {
                            proc1->clearArguments();
                            // додавання імені програми та як параметр - імені файла до командного рядка процесу
                            proc1->addArgument( QString( "%1" ).arg( confline.latin1() ));
                            proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));
                            // запуск процесу на виконання - відкриття файлу зовнішньою програмою
                            proc1->start();
                            lineflag=0;
                        }
                    // якщо параметр у файлі співпадає з розширенням поточного файла, призначення відповідного прапорця
                    if (confline.latin1()==confext) lineflag=1;
                    conflines += confline;
                    }
                // закриття конфігураційного файлу
                conffile.close();
                }
            }
        }
        // в іншому випадку, тобто коли файл не виконуваний, але має розширення
        else
        {
            if ( conffile.open( IO_ReadOnly ) )
            {
                conffi.setFile( item->text() );
                confext = conffi.extension( FALSE );
                lineflag=0;
                // відповідне читання конфігураційного файла для коректного відкриття
                while ( !confstream.eof() )
                {
                    confline = confstream.readLine();
                    if (lineflag==1)
                    {
                        proc1->clearArguments();
                        // додавання імені програми та як параметр - імені файла до командного рядка процесу
                        proc1->addArgument( QString( "%1" ).arg( confline.latin1() ));
                        proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));
                        // запуск процесу на виконання - відкриття файлу зовнішньою програмою
                        proc1->start();
                        lineflag=0;
                    }
                    // якщо параметр у файлі співпадає з розширенням поточного файла, призначення відповідного прапорця
                    if (confline.latin1()==confext) lineflag=1;
                    conflines += confline;
                }
                // закриття конфігураційного файлу
                conffile.close();
            }
        }
    }
}

// метод для забезпечення появи елемента списка каталога у новому каталозі
// при перетягуванні елементів каталога
// повертає об"єкт drag, що включає в себе інформацію про ім"я елементів списку та їх значки
QDragObject *QtFileIconView::dragObject()
{
    if ( !currentItem() ) return 0;

    QPoint orig = viewportToContents( viewport()->mapFromGlobal( QCursor::pos() ) );
    QtFileIconDrag *drag = new QtFileIconDrag( viewport() );
    drag->setPixmap( *currentItem()->pixmap(), QPoint( currentItem()->pixmapRect().width() / 2, currentItem()->pixmapRect().height() / 2 ) );
    for ( QtFileIconViewItem *item = (QtFileIconViewItem*)firstItem(); item; item = (QtFileIconViewItem*)item->nextItem() ) 
    {
        if ( item->isSelected() ) 
        {
            QIconDragItem id;
            id.setData( QCString( item->filename() ) );
            drag->append( id,
            QRect( item->pixmapRect( FALSE ).x() - orig.x(), item->pixmapRect( FALSE ).y() - orig.y(), item->pixmapRect().width(), item->pixmapRect().height() ),
            QRect( item->textRect( FALSE ).x() - orig.x(), item->textRect( FALSE ).y() - orig.y(), item->textRect().width(), item->textRect().height() ),
            QString( item->filename() ) );
        }
    }

    return drag;
}

// метод обробітку натиснення комбінацій клавіш
// реалізована комбінація ctrl-N для створення нового каталога
// (даний метод викликає метод створення каталога)
void QtFileIconView::keyPressEvent( QKeyEvent *e )
{
    if ( e->key() == Key_N && ( e->state() & ControlButton ) ) newDirectory();
    else QIconView::keyPressEvent( e );
}

// слот, що відповідає за приймання перетягнених елементів каталога
// та декодування закодованих у список URL шляхів файлів
// у локальні абсолютні шляхи
// результат роботи слота - виведення відповідного повідомлення
// тому що можливість такого копіювання ще не реалізована
// це лише початковий механізм
void QtFileIconView::slotDropped( QDropEvent *e, const QValueList<QIconDragItem> & )
{
    if ( openItem ) openItem->timer.stop();
    if ( !QUriDrag::canDecode( e ) ) 
    {
        e->ignore();
        return;
    }

    QStringList lst;
    QUriDrag::decodeLocalFiles( e, lst );

    QString str;
    if ( e->action() == QDropEvent::Copy )
    str = "Copy\n\n";
    else str = "Move\n\n";
    for ( uint i = 0; i < lst.count(); ++i )
    str += QString( "   %1\n" ).arg( QDir::convertSeparators(lst[i]) );
    str += QString( "\n"
    "To\n\n"
    "   %1" ).arg( viewDir.absPath() );

    // виведення повідомлення про неможливість здійснити операції з файлами
    QMessageBox::information( this, e->action() == QDropEvent::Copy ? "Copy" : "Move" , str, "Not Implemented" );
    if ( e->action() == QDropEvent::Move ) QMessageBox::information( this, "Remove2" , QDir::convertSeparators(lst.join("\n")), "Not Implemented" );
    e->acceptAction();
    openItem = 0;
}

// метод для увімкнення режиму показу великих значків
void QtFileIconView::viewLarge()
{
    setViewMode( Large );
}

// метод для умімкнення режиму показу маленьких значків
void QtFileIconView::viewDetail()
{
    setViewMode( Detail );
}

// метод для увімкнення режиму показу назви елемента каталога внизу від значка
void QtFileIconView::viewBottom()
{
    setItemTextPos( Bottom );
}

// метод для увімкнення режиму показу назви елемента каталога праворуч від значка
void QtFileIconView::viewRight()
{
    setItemTextPos( Right );
}

// метод для увімкнення режиму групування елементів каталога зліва-направо
void QtFileIconView::flowEast()
{
    setHScrollBarMode( AlwaysOff );
    setVScrollBarMode( Auto );
    setArrangement( LeftToRight );
}

// метод для увімкнення режиму групування елементів каталога згори-додолу
void QtFileIconView::flowSouth()
{
    setVScrollBarMode( AlwaysOff );
    setHScrollBarMode( Auto );
    setArrangement( TopToBottom );
}

// увімкнення режиму сортування по збільшенню
void QtFileIconView::sortAscending()
{
    sort( TRUE );
}

// увімкнення режиму сортування по зменшенню
void QtFileIconView::sortDescending()
{
    sort( FALSE );
}

// метод - перша стадія копіювання файлів при натисненні на відповідну кнопку
void QtFileIconView::copy_prev ()
{
    QtFileIconViewItem *item = (QtFileIconViewItem*)firstItem();
    QtFileIconView::copy_fin (item);
}

// метод - перша стадія переміщення файлів при натисненні на відповідну кнопку
void QtFileIconView::cut_prev ()
{
    QtFileIconViewItem *item = (QtFileIconViewItem*)firstItem();
    QtFileIconView::cut_fin (item);
}

// метод - перша стадія перейменування файлів при натисненні на відповідну кнопку
void QtFileIconView::rename_prev ()
{
    QtFileIconViewItem *item = (QtFileIconViewItem*)currentItem();
    QtFileIconView::rename_fin (item);
}

// метод - перша стадія знищення файлів при натисненні на відповідну кнопку
void QtFileIconView::remove_prev ()
{
    QtFileIconViewItem *item = (QtFileIconViewItem*)firstItem();
    QtFileIconView::remove_fin (item);
}

// метод - увімкнення або вимкнення режиму автооновлення елементів каталогу
void QtFileIconView::update ()
{
    update_files=-update_files;
}

// метод - завершальна стадія перейменування файлів при натисненні на відповідну кнопку
void QtFileIconView::rename_fin (QIconViewItem *item)
{
    item->rename(); 
}

// метод - завершальна стадія знищення файлів при натисненні на відповідну кнопку
void QtFileIconView::remove_fin (QIconViewItem *item)
{
    proc1->clearArguments();
    proc1->addArgument("rm");
    proc1->addArgument("-r");
    proc1->addArgument("-f");
    for ( item = QIconView::firstItem(); item; item = item->nextItem() ) 
    {
        if (item->isSelected()) 
        {
        proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));
        }
    }
    QMessageBox mb( "Deleting",
        "Program is starting files removing process.\n"
        "Do you really want to proceed?",
        QMessageBox::Information,
        QMessageBox::Yes | QMessageBox::Default,
        QMessageBox::No,
        QMessageBox::Cancel | QMessageBox::Escape );
    mb.setButtonText( QMessageBox::Yes, "Delete" );
    mb.setButtonText( QMessageBox::No, "No" );
    switch( mb.exec() ) 
    {
        case QMessageBox::Yes:
        proc1->start();
        frm_flag=1;
        msg_flag=1; 
            break;
        case QMessageBox::No:
        // exit without saving
            break;
        case QMessageBox::Cancel:
        // don't save and don't exit
            break;
    }

}

// метод - завершальна стадія копіювання файлів при натисненні на відповідну кнопку
void QtFileIconView::copy_fin (QIconViewItem *item)
{
    proc1->clearArguments();
    proc1->addArgument("cp");
    proc1->addArgument("-r");
    proc1->addArgument("-f");
    for ( item = QIconView::firstItem(); item; item = item->nextItem() ) 
    { 
    if (item->isSelected()) 
        {
        proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));   
        }
    }   
}

// метод - завершальна стадія переміщення файлів при натисненні на відповідну кнопку
void QtFileIconView::cut_fin (QIconViewItem *item)
{
    proc1->clearArguments();
    // додавання відповідних аргументів до командного рядка
    proc1->addArgument("mv");
    proc1->addArgument("-f");
    // занесення до аргументів командного рядка абсолютних шляхів виділених елементів
    for ( item = QIconView::firstItem(); item; item = item->nextItem() ) 
    { 
    if (item->isSelected()) 
        {
        proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));   
        }
    }
    QIconView::clearSelection ();
    viewDir = QDir( viewDir.absPath() );
    readDir( viewDir );
}

// перша стадія вставки файлів у нове місце
void QtFileIconView::paste()
{
    QtFileIconView::copy1(viewDir.absPath());
    viewDir = QDir( viewDir.absPath() );
    readDir( viewDir );
}

// метод одноразового оновлення вмісту каталога та елементів у вікні програми
void QtFileIconView::updateonce()
{
    viewDir = QDir( viewDir.absPath() );
    readDir( viewDir );
}

// увімкнення режиму скорочення виводу на екран довгих назв елементів
void QtFileIconView::itemTextTruncate()
{
    setWordWrapIconText( FALSE );
}

// увімкнення режиму повного виводу на екран довгих назв елементів
void QtFileIconView::itemTextWordWrap()
{
    setWordWrapIconText( TRUE );
}

// слот, що викликається при натисненні правої клавіші миші
// на елементі або пустому полі
void QtFileIconView::slotRightPressed( QIconViewItem *item )
{
    // тиснення на порожньому полі
    if ( !item ) 
    {
        // вивід на екран контекстного меню порожнього поля
        QPopupMenu menu( this );

        menu.insertItem( "&Huge items", this, SLOT( viewLarge() ) );
        menu.insertItem( "&Little items", this, SLOT( viewDetail() ) );
        menu.insertSeparator();
        menu.insertItem( "Text at the &bottom", this, SLOT( viewBottom() ) );
        menu.insertItem( "Text at the &right", this, SLOT( viewRight() ) );
        menu.insertSeparator();
        menu.insertItem( "Arrange l&eft to right", this, SLOT( flowEast() ) );
        menu.insertItem( "Arrange t&op to bottom", this, SLOT( flowSouth() ) );
        menu.insertSeparator();
        menu.insertItem( "&Truncate item text", this, SLOT( itemTextTruncate() ) );
        menu.insertItem( "&Wordwrap item text", this, SLOT( itemTextWordWrap() ) );
        menu.insertSeparator();
        menu.insertItem( "Arrange items in &grid", this, SLOT( arrangeItemsInGrid() ) );
        menu.insertSeparator();
        menu.insertItem( "Sort &ascending", this, SLOT( sortAscending() ) );
        menu.insertItem( "Sort &descending", this, SLOT( sortDescending() ) );
        menu.insertItem( "Paste", this, SLOT( paste() ) );

        menu.setMouseTracking( TRUE );
        menu.exec( QCursor::pos() );
    }
    else
    // тиснення на елементі каталогу 
    {
        // виведення контекстного меню елемента каталога
        QPopupMenu menu( this );

        int RENAME_ITEM = menu.insertItem( "Rename" );
        int REMOVE_ITEM = menu.insertItem( "Remove" );
        int COPY_ITEM = menu.insertItem( "Copy" );
        int MOVE_ITEM = menu.insertItem( "Cut" );
        int EDIT_ITEM = menu.insertItem( "Edit" );
        int VIEW_ITEM = menu.insertItem( "View" );

        menu.setMouseTracking( TRUE );
        int id = menu.exec( QCursor::pos() );

        // якщо ESC - повернення
        if ( id == -1 ) return;
        // перейменування елемента каталога
        if ( id == RENAME_ITEM && item->renameEnabled() ) 
        {
                item->rename();
        }
        else 
        // знищення елементів каталога
        if ( id == REMOVE_ITEM ) 
        {
            cpcount=0;
            proc1->clearArguments();
            // додавання аргументів до командного рядка процесу
            proc1->addArgument("rm");
            proc1->addArgument("-r");
            proc1->addArgument("-f");
            // додавання у якості аргументів командного рядка процесу абсолютних шляхів
            // виділених файлів
            for ( item = QIconView::firstItem(); item; item = item->nextItem() ) 
            {
                cpcount++;
                if (item->isSelected()) 
                {
                    proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));
                }
            }
            // виведення повідомлення про знищення файлів із запитанням користувачу
            QMessageBox mb( "Deleting",
                "Program is starting files removing process.\n"
                "Do you really want to proceed?",
                QMessageBox::Information,
                QMessageBox::Yes | QMessageBox::Default,
                QMessageBox::No,
                QMessageBox::Cancel | QMessageBox::Escape );
            mb.setButtonText( QMessageBox::Yes, "Delete" );
            mb.setButtonText( QMessageBox::No, "No" );
            // обробка натиснення кнопок
            switch( mb.exec() ) 
            {
                case QMessageBox::Yes:
                // запуск процесу знищення файлів
                proc1->start();
                frm_flag=1;
                msg_flag=1; 
                break;
                case QMessageBox::No:
                    break;
                case QMessageBox::Cancel:
                    break;
            }
        } 
        // копіювання файлів
        else if ( id == COPY_ITEM ) 
        {
            proc1->clearArguments();
            // додавання до командного рядка аргументів копіювання
            proc1->addArgument("cp");
            proc1->addArgument("-r");
            proc1->addArgument("-f");
            // додавання до командного рядка абсолютних шляхів файлів для копіювання
            for ( item = QIconView::firstItem(); item; item = item->nextItem() ) 
            { 
                if (item->isSelected()) 
                {
                    proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() )); 
                }
            }
        } 
        // переміщення файлів
        else if ( id == MOVE_ITEM ) 
        {
            proc1->clearArguments();
            // додавання до командного рядка аргументів переміщення
            proc1->addArgument("mv");
            proc1->addArgument("-f");
            // додавання до командного рядка абсолютних шляхів файлів для копіювання
            for ( item = QIconView::firstItem(); item; item = item->nextItem() )
            {
                if (item->isSelected())
                {
                    proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));
                }
            }
            QIconView::clearSelection ();
            // оновлення елементів каталогу 
            viewDir = QDir( viewDir.absPath() );
            readDir( viewDir );
        }
        // редагувати файл
        else if ( id == EDIT_ITEM )
        {
            proc1->clearArguments();
            // використовуємо редактор GVIM
            proc1->addArgument("gvim");
            proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));
            proc1->start();
        }
        // продивитись файл
        else if ( id == VIEW_ITEM )
        {
            proc1->clearArguments();
            // використовуємо редактор GVIM
            proc1->addArgument("gvim");
            // відкриття файла тільки для читання
            proc1->addArgument("-m");
            proc1->addArgument( QString( "%1/%2" ).arg( viewDir.absPath() ).arg( item->text() ));
            proc1->start();
        }
    }
}

// метод для призначення режиму відображення елементів каталогу у вікні програми
void QtFileIconView::setViewMode( ViewMode m )
{
    if ( m == vm ) return;
    vm = m;
    QtFileIconViewItem *item = (QtFileIconViewItem*)firstItem();
    for ( ; item; item = (QtFileIconViewItem*)item->nextItem() ) item->viewModeChanged( vm );
    arrangeItemsInGrid();
}
