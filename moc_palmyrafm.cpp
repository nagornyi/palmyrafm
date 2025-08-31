/****************************************************************************
** Meta object code from reading C++ file 'palmyrafm.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "palmyrafm.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'palmyrafm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileMainWindow_t {
    const uint offsetsAndSize[50];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_FileMainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_FileMainWindow_t qt_meta_stringdata_FileMainWindow = {
    {
QT_MOC_LITERAL(0, 14), // "FileMainWindow"
QT_MOC_LITERAL(15, 16), // "directoryChanged"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 16), // "slotStartReadDir"
QT_MOC_LITERAL(50, 4), // "dirs"
QT_MOC_LITERAL(55, 15), // "slotReadNextDir"
QT_MOC_LITERAL(71, 15), // "slotReadDirDone"
QT_MOC_LITERAL(87, 4), // "cdUp"
QT_MOC_LITERAL(92, 6), // "goHome"
QT_MOC_LITERAL(99, 9), // "newFolder"
QT_MOC_LITERAL(109, 3), // "cut"
QT_MOC_LITERAL(113, 4), // "copy"
QT_MOC_LITERAL(118, 5), // "paste"
QT_MOC_LITERAL(124, 6), // "rename"
QT_MOC_LITERAL(131, 6), // "remove"
QT_MOC_LITERAL(138, 6), // "update"
QT_MOC_LITERAL(145, 10), // "updateonce"
QT_MOC_LITERAL(156, 5), // "about"
QT_MOC_LITERAL(162, 10), // "changePath"
QT_MOC_LITERAL(173, 4), // "path"
QT_MOC_LITERAL(178, 16), // "pathEditFinished"
QT_MOC_LITERAL(195, 8), // "enableUp"
QT_MOC_LITERAL(204, 9), // "disableUp"
QT_MOC_LITERAL(214, 11), // "enableMkdir"
QT_MOC_LITERAL(226, 12) // "disableMkdir"

    },
    "FileMainWindow\0directoryChanged\0\0"
    "slotStartReadDir\0dirs\0slotReadNextDir\0"
    "slotReadDirDone\0cdUp\0goHome\0newFolder\0"
    "cut\0copy\0paste\0rename\0remove\0update\0"
    "updateonce\0about\0changePath\0path\0"
    "pathEditFinished\0enableUp\0disableUp\0"
    "enableMkdir\0disableMkdir"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileMainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  140,    2, 0x09,    1 /* Protected */,
       3,    1,  143,    2, 0x09,    3 /* Protected */,
       5,    0,  146,    2, 0x09,    5 /* Protected */,
       6,    0,  147,    2, 0x09,    6 /* Protected */,
       7,    0,  148,    2, 0x09,    7 /* Protected */,
       8,    0,  149,    2, 0x09,    8 /* Protected */,
       9,    0,  150,    2, 0x09,    9 /* Protected */,
      10,    0,  151,    2, 0x09,   10 /* Protected */,
      11,    0,  152,    2, 0x09,   11 /* Protected */,
      12,    0,  153,    2, 0x09,   12 /* Protected */,
      13,    0,  154,    2, 0x09,   13 /* Protected */,
      14,    0,  155,    2, 0x09,   14 /* Protected */,
      15,    0,  156,    2, 0x09,   15 /* Protected */,
      16,    0,  157,    2, 0x09,   16 /* Protected */,
      17,    0,  158,    2, 0x09,   17 /* Protected */,
      18,    1,  159,    2, 0x09,   18 /* Protected */,
      20,    0,  162,    2, 0x09,   20 /* Protected */,
      21,    0,  163,    2, 0x09,   21 /* Protected */,
      22,    0,  164,    2, 0x09,   22 /* Protected */,
      23,    0,  165,    2, 0x09,   23 /* Protected */,
      24,    0,  166,    2, 0x09,   24 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FileMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileMainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->directoryChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->slotStartReadDir((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->slotReadNextDir(); break;
        case 3: _t->slotReadDirDone(); break;
        case 4: _t->cdUp(); break;
        case 5: _t->goHome(); break;
        case 6: _t->newFolder(); break;
        case 7: _t->cut(); break;
        case 8: _t->copy(); break;
        case 9: _t->paste(); break;
        case 10: _t->rename(); break;
        case 11: _t->remove(); break;
        case 12: _t->update(); break;
        case 13: _t->updateonce(); break;
        case 14: _t->about(); break;
        case 15: _t->changePath((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->pathEditFinished(); break;
        case 17: _t->enableUp(); break;
        case 18: _t->disableUp(); break;
        case 19: _t->enableMkdir(); break;
        case 20: _t->disableMkdir(); break;
        default: ;
        }
    }
}

const QMetaObject FileMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_FileMainWindow.offsetsAndSize,
    qt_meta_data_FileMainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_FileMainWindow_t
, QtPrivate::TypeAndForceComplete<FileMainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *FileMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int FileMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 21;
    }
    return _id;
}
struct qt_meta_stringdata_Copier_t {
    const uint offsetsAndSize[2];
    char stringdata0[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Copier_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Copier_t qt_meta_stringdata_Copier = {
    {
QT_MOC_LITERAL(0, 6) // "Copier"

    },
    "Copier"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Copier[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Copier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject Copier::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Copier.offsetsAndSize,
    qt_meta_data_Copier,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Copier_t
, QtPrivate::TypeAndForceComplete<Copier, std::true_type>



>,
    nullptr
} };


const QMetaObject *Copier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Copier::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Copier.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Copier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_QtFileIconDrag_t {
    const uint offsetsAndSize[2];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QtFileIconDrag_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QtFileIconDrag_t qt_meta_stringdata_QtFileIconDrag = {
    {
QT_MOC_LITERAL(0, 14) // "QtFileIconDrag"

    },
    "QtFileIconDrag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtFileIconDrag[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void QtFileIconDrag::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject QtFileIconDrag::staticMetaObject = { {
    QMetaObject::SuperData::link<QDrag::staticMetaObject>(),
    qt_meta_stringdata_QtFileIconDrag.offsetsAndSize,
    qt_meta_data_QtFileIconDrag,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QtFileIconDrag_t
, QtPrivate::TypeAndForceComplete<QtFileIconDrag, std::true_type>



>,
    nullptr
} };


const QMetaObject *QtFileIconDrag::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtFileIconDrag::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtFileIconDrag.stringdata0))
        return static_cast<void*>(this);
    return QDrag::qt_metacast(_clname);
}

int QtFileIconDrag::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDrag::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_QtFileIconView_t {
    const uint offsetsAndSize[92];
    char stringdata0[501];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QtFileIconView_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QtFileIconView_t qt_meta_stringdata_QtFileIconView = {
    {
QT_MOC_LITERAL(0, 14), // "QtFileIconView"
QT_MOC_LITERAL(15, 16), // "directoryChanged"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 12), // "startReadDir"
QT_MOC_LITERAL(46, 4), // "dirs"
QT_MOC_LITERAL(51, 11), // "readNextDir"
QT_MOC_LITERAL(63, 11), // "readDirDone"
QT_MOC_LITERAL(75, 8), // "enableUp"
QT_MOC_LITERAL(84, 9), // "disableUp"
QT_MOC_LITERAL(94, 11), // "enableMkdir"
QT_MOC_LITERAL(106, 12), // "disableMkdir"
QT_MOC_LITERAL(119, 12), // "setDirectory"
QT_MOC_LITERAL(132, 3), // "dir"
QT_MOC_LITERAL(136, 4), // "QDir"
QT_MOC_LITERAL(141, 12), // "newDirectory"
QT_MOC_LITERAL(154, 8), // "cut_prev"
QT_MOC_LITERAL(163, 9), // "copy_prev"
QT_MOC_LITERAL(173, 11), // "rename_prev"
QT_MOC_LITERAL(185, 11), // "remove_prev"
QT_MOC_LITERAL(197, 10), // "updateonce"
QT_MOC_LITERAL(208, 7), // "cut_fin"
QT_MOC_LITERAL(216, 11), // "QModelIndex"
QT_MOC_LITERAL(228, 4), // "item"
QT_MOC_LITERAL(233, 8), // "copy_fin"
QT_MOC_LITERAL(242, 10), // "rename_fin"
QT_MOC_LITERAL(253, 10), // "remove_fin"
QT_MOC_LITERAL(264, 5), // "paste"
QT_MOC_LITERAL(270, 17), // "itemDoubleClicked"
QT_MOC_LITERAL(288, 5), // "index"
QT_MOC_LITERAL(294, 11), // "slotDropped"
QT_MOC_LITERAL(306, 11), // "QDropEvent*"
QT_MOC_LITERAL(318, 1), // "e"
QT_MOC_LITERAL(320, 9), // "viewLarge"
QT_MOC_LITERAL(330, 10), // "viewDetail"
QT_MOC_LITERAL(341, 10), // "viewBottom"
QT_MOC_LITERAL(352, 9), // "viewRight"
QT_MOC_LITERAL(362, 8), // "flowEast"
QT_MOC_LITERAL(371, 9), // "flowSouth"
QT_MOC_LITERAL(381, 16), // "itemTextTruncate"
QT_MOC_LITERAL(398, 16), // "itemTextWordWrap"
QT_MOC_LITERAL(415, 13), // "sortAscending"
QT_MOC_LITERAL(429, 14), // "sortDescending"
QT_MOC_LITERAL(444, 18), // "arrangeItemsInGrid"
QT_MOC_LITERAL(463, 16), // "slotRightPressed"
QT_MOC_LITERAL(480, 10), // "openFolder"
QT_MOC_LITERAL(491, 9) // "regupdate"

    },
    "QtFileIconView\0directoryChanged\0\0"
    "startReadDir\0dirs\0readNextDir\0readDirDone\0"
    "enableUp\0disableUp\0enableMkdir\0"
    "disableMkdir\0setDirectory\0dir\0QDir\0"
    "newDirectory\0cut_prev\0copy_prev\0"
    "rename_prev\0remove_prev\0updateonce\0"
    "cut_fin\0QModelIndex\0item\0copy_fin\0"
    "rename_fin\0remove_fin\0paste\0"
    "itemDoubleClicked\0index\0slotDropped\0"
    "QDropEvent*\0e\0viewLarge\0viewDetail\0"
    "viewBottom\0viewRight\0flowEast\0flowSouth\0"
    "itemTextTruncate\0itemTextWordWrap\0"
    "sortAscending\0sortDescending\0"
    "arrangeItemsInGrid\0slotRightPressed\0"
    "openFolder\0regupdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtFileIconView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  236,    2, 0x06,    1 /* Public */,
       3,    1,  239,    2, 0x06,    3 /* Public */,
       5,    0,  242,    2, 0x06,    5 /* Public */,
       6,    0,  243,    2, 0x06,    6 /* Public */,
       7,    0,  244,    2, 0x06,    7 /* Public */,
       8,    0,  245,    2, 0x06,    8 /* Public */,
       9,    0,  246,    2, 0x06,    9 /* Public */,
      10,    0,  247,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    1,  248,    2, 0x0a,   11 /* Public */,
      11,    1,  251,    2, 0x0a,   13 /* Public */,
      14,    0,  254,    2, 0x0a,   15 /* Public */,
      15,    0,  255,    2, 0x0a,   16 /* Public */,
      16,    0,  256,    2, 0x0a,   17 /* Public */,
      17,    0,  257,    2, 0x0a,   18 /* Public */,
      18,    0,  258,    2, 0x0a,   19 /* Public */,
      19,    0,  259,    2, 0x0a,   20 /* Public */,
      20,    1,  260,    2, 0x0a,   21 /* Public */,
      23,    1,  263,    2, 0x0a,   23 /* Public */,
      24,    1,  266,    2, 0x0a,   25 /* Public */,
      25,    1,  269,    2, 0x0a,   27 /* Public */,
      26,    0,  272,    2, 0x0a,   29 /* Public */,
      27,    1,  273,    2, 0x09,   30 /* Protected */,
      29,    1,  276,    2, 0x09,   32 /* Protected */,
      32,    0,  279,    2, 0x09,   34 /* Protected */,
      33,    0,  280,    2, 0x09,   35 /* Protected */,
      34,    0,  281,    2, 0x09,   36 /* Protected */,
      35,    0,  282,    2, 0x09,   37 /* Protected */,
      36,    0,  283,    2, 0x09,   38 /* Protected */,
      37,    0,  284,    2, 0x09,   39 /* Protected */,
      38,    0,  285,    2, 0x09,   40 /* Protected */,
      39,    0,  286,    2, 0x09,   41 /* Protected */,
      40,    0,  287,    2, 0x09,   42 /* Protected */,
      41,    0,  288,    2, 0x09,   43 /* Protected */,
      42,    0,  289,    2, 0x09,   44 /* Protected */,
      43,    1,  290,    2, 0x09,   45 /* Protected */,
      44,    0,  293,    2, 0x09,   47 /* Protected */,
      45,    0,  294,    2, 0x09,   48 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, 0x80000000 | 13,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   28,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   28,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtFileIconView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtFileIconView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->directoryChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->startReadDir((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->readNextDir(); break;
        case 3: _t->readDirDone(); break;
        case 4: _t->enableUp(); break;
        case 5: _t->disableUp(); break;
        case 6: _t->enableMkdir(); break;
        case 7: _t->disableMkdir(); break;
        case 8: _t->setDirectory((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->setDirectory((*reinterpret_cast< std::add_pointer_t<QDir>>(_a[1]))); break;
        case 10: _t->newDirectory(); break;
        case 11: _t->cut_prev(); break;
        case 12: _t->copy_prev(); break;
        case 13: _t->rename_prev(); break;
        case 14: _t->remove_prev(); break;
        case 15: _t->updateonce(); break;
        case 16: _t->cut_fin((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 17: _t->copy_fin((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 18: _t->rename_fin((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 19: _t->remove_fin((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 20: _t->paste(); break;
        case 21: _t->itemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 22: _t->slotDropped((*reinterpret_cast< std::add_pointer_t<QDropEvent*>>(_a[1]))); break;
        case 23: _t->viewLarge(); break;
        case 24: _t->viewDetail(); break;
        case 25: _t->viewBottom(); break;
        case 26: _t->viewRight(); break;
        case 27: _t->flowEast(); break;
        case 28: _t->flowSouth(); break;
        case 29: _t->itemTextTruncate(); break;
        case 30: _t->itemTextWordWrap(); break;
        case 31: _t->sortAscending(); break;
        case 32: _t->sortDescending(); break;
        case 33: _t->arrangeItemsInGrid(); break;
        case 34: _t->slotRightPressed((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 35: _t->openFolder(); break;
        case 36: _t->regupdate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtFileIconView::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtFileIconView::directoryChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QtFileIconView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtFileIconView::startReadDir)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QtFileIconView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtFileIconView::readNextDir)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QtFileIconView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtFileIconView::readDirDone)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QtFileIconView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtFileIconView::enableUp)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QtFileIconView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtFileIconView::disableUp)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QtFileIconView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtFileIconView::enableMkdir)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QtFileIconView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtFileIconView::disableMkdir)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject QtFileIconView::staticMetaObject = { {
    QMetaObject::SuperData::link<QListView::staticMetaObject>(),
    qt_meta_stringdata_QtFileIconView.offsetsAndSize,
    qt_meta_data_QtFileIconView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QtFileIconView_t
, QtPrivate::TypeAndForceComplete<QtFileIconView, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QDir &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QDropEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *QtFileIconView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtFileIconView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtFileIconView.stringdata0))
        return static_cast<void*>(this);
    return QListView::qt_metacast(_clname);
}

int QtFileIconView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void QtFileIconView::directoryChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtFileIconView::startReadDir(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QtFileIconView::readNextDir()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QtFileIconView::readDirDone()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QtFileIconView::enableUp()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QtFileIconView::disableUp()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QtFileIconView::enableMkdir()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QtFileIconView::disableMkdir()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
struct qt_meta_stringdata_DirectoryView_t {
    const uint offsetsAndSize[14];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DirectoryView_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DirectoryView_t qt_meta_stringdata_DirectoryView = {
    {
QT_MOC_LITERAL(0, 13), // "DirectoryView"
QT_MOC_LITERAL(14, 14), // "folderSelected"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 6), // "setDir"
QT_MOC_LITERAL(37, 18), // "slotFolderSelected"
QT_MOC_LITERAL(56, 11), // "QModelIndex"
QT_MOC_LITERAL(68, 5) // "index"

    },
    "DirectoryView\0folderSelected\0\0setDir\0"
    "slotFolderSelected\0QModelIndex\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DirectoryView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   35,    2, 0x0a,    3 /* Public */,
       4,    1,   38,    2, 0x09,    5 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void DirectoryView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DirectoryView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->folderSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->setDir((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->slotFolderSelected((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DirectoryView::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DirectoryView::folderSelected)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DirectoryView::staticMetaObject = { {
    QMetaObject::SuperData::link<QTreeView::staticMetaObject>(),
    qt_meta_stringdata_DirectoryView.offsetsAndSize,
    qt_meta_data_DirectoryView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DirectoryView_t
, QtPrivate::TypeAndForceComplete<DirectoryView, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>


>,
    nullptr
} };


const QMetaObject *DirectoryView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DirectoryView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DirectoryView.stringdata0))
        return static_cast<void*>(this);
    return QTreeView::qt_metacast(_clname);
}

int DirectoryView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DirectoryView::folderSelected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
