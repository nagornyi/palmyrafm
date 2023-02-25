/****************************************************************************
** FileMainWindow meta object code from reading C++ file 'palmyrafm.h'
**
** Created: Sun Apr 30 13:34:41 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "palmyrafm.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *FileMainWindow::className() const
{
    return "FileMainWindow";
}

QMetaObject *FileMainWindow::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FileMainWindow( "FileMainWindow", &FileMainWindow::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString FileMainWindow::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FileMainWindow", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString FileMainWindow::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FileMainWindow", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* FileMainWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"directoryChanged", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "dirs", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"slotStartReadDir", 1, param_slot_1 };
    static const QUMethod slot_2 = {"slotReadNextDir", 0, 0 };
    static const QUMethod slot_3 = {"slotReadDirDone", 0, 0 };
    static const QUMethod slot_4 = {"cdUp", 0, 0 };
    static const QUMethod slot_5 = {"newFolder", 0, 0 };
    static const QUMethod slot_6 = {"cut", 0, 0 };
    static const QUMethod slot_7 = {"copy", 0, 0 };
    static const QUMethod slot_8 = {"paste", 0, 0 };
    static const QUMethod slot_9 = {"rename", 0, 0 };
    static const QUMethod slot_10 = {"remove", 0, 0 };
    static const QUMethod slot_11 = {"update", 0, 0 };
    static const QUMethod slot_12 = {"updateonce", 0, 0 };
    static const QUMethod slot_13 = {"about", 0, 0 };
    static const QUParameter param_slot_14[] = {
	{ "path", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"changePath", 1, param_slot_14 };
    static const QUMethod slot_15 = {"enableUp", 0, 0 };
    static const QUMethod slot_16 = {"disableUp", 0, 0 };
    static const QUMethod slot_17 = {"enableMkdir", 0, 0 };
    static const QUMethod slot_18 = {"disableMkdir", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "directoryChanged(const QString&)", &slot_0, QMetaData::Protected },
	{ "slotStartReadDir(int)", &slot_1, QMetaData::Protected },
	{ "slotReadNextDir()", &slot_2, QMetaData::Protected },
	{ "slotReadDirDone()", &slot_3, QMetaData::Protected },
	{ "cdUp()", &slot_4, QMetaData::Protected },
	{ "newFolder()", &slot_5, QMetaData::Protected },
	{ "cut()", &slot_6, QMetaData::Protected },
	{ "copy()", &slot_7, QMetaData::Protected },
	{ "paste()", &slot_8, QMetaData::Protected },
	{ "rename()", &slot_9, QMetaData::Protected },
	{ "remove()", &slot_10, QMetaData::Protected },
	{ "update()", &slot_11, QMetaData::Protected },
	{ "updateonce()", &slot_12, QMetaData::Protected },
	{ "about()", &slot_13, QMetaData::Protected },
	{ "changePath(const QString&)", &slot_14, QMetaData::Protected },
	{ "enableUp()", &slot_15, QMetaData::Protected },
	{ "disableUp()", &slot_16, QMetaData::Protected },
	{ "enableMkdir()", &slot_17, QMetaData::Protected },
	{ "disableMkdir()", &slot_18, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"FileMainWindow", parentObject,
	slot_tbl, 19,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_FileMainWindow.setMetaObject( metaObj );
    return metaObj;
}

void* FileMainWindow::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "FileMainWindow" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool FileMainWindow::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: directoryChanged((const QString&)static_QUType_QString.get(_o+1)); break;
    case 1: slotStartReadDir((int)static_QUType_int.get(_o+1)); break;
    case 2: slotReadNextDir(); break;
    case 3: slotReadDirDone(); break;
    case 4: cdUp(); break;
    case 5: newFolder(); break;
    case 6: cut(); break;
    case 7: copy(); break;
    case 8: paste(); break;
    case 9: rename(); break;
    case 10: remove(); break;
    case 11: update(); break;
    case 12: updateonce(); break;
    case 13: about(); break;
    case 14: changePath((const QString&)static_QUType_QString.get(_o+1)); break;
    case 15: enableUp(); break;
    case 16: disableUp(); break;
    case 17: enableMkdir(); break;
    case 18: disableMkdir(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool FileMainWindow::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool FileMainWindow::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool FileMainWindow::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *Copier::className() const
{
    return "Copier";
}

QMetaObject *Copier::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Copier( "Copier", &Copier::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Copier::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Copier", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Copier::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Copier", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Copier::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QVBox::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"Copier", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Copier.setMetaObject( metaObj );
    return metaObj;
}

void* Copier::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Copier" ) )
	return this;
    return QVBox::qt_cast( clname );
}

bool Copier::qt_invoke( int _id, QUObject* _o )
{
    return QVBox::qt_invoke(_id,_o);
}

bool Copier::qt_emit( int _id, QUObject* _o )
{
    return QVBox::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Copier::qt_property( int id, int f, QVariant* v)
{
    return QVBox::qt_property( id, f, v);
}

bool Copier::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *QtFileIconDrag::className() const
{
    return "QtFileIconDrag";
}

QMetaObject *QtFileIconDrag::metaObj = 0;
static QMetaObjectCleanUp cleanUp_QtFileIconDrag( "QtFileIconDrag", &QtFileIconDrag::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString QtFileIconDrag::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "QtFileIconDrag", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString QtFileIconDrag::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "QtFileIconDrag", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* QtFileIconDrag::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QIconDrag::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"QtFileIconDrag", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_QtFileIconDrag.setMetaObject( metaObj );
    return metaObj;
}

void* QtFileIconDrag::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "QtFileIconDrag" ) )
	return this;
    return QIconDrag::qt_cast( clname );
}

bool QtFileIconDrag::qt_invoke( int _id, QUObject* _o )
{
    return QIconDrag::qt_invoke(_id,_o);
}

bool QtFileIconDrag::qt_emit( int _id, QUObject* _o )
{
    return QIconDrag::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool QtFileIconDrag::qt_property( int id, int f, QVariant* v)
{
    return QIconDrag::qt_property( id, f, v);
}

bool QtFileIconDrag::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *QtFileIconView::className() const
{
    return "QtFileIconView";
}

QMetaObject *QtFileIconView::metaObj = 0;
static QMetaObjectCleanUp cleanUp_QtFileIconView( "QtFileIconView", &QtFileIconView::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString QtFileIconView::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "QtFileIconView", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString QtFileIconView::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "QtFileIconView", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* QtFileIconView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QIconView::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "dir", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"setDirectory", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "dir", &static_QUType_ptr, "QDir", QUParameter::In }
    };
    static const QUMethod slot_1 = {"setDirectory", 1, param_slot_1 };
    static const QUMethod slot_2 = {"newDirectory", 0, 0 };
    static const QUMethod slot_3 = {"cut_prev", 0, 0 };
    static const QUMethod slot_4 = {"copy_prev", 0, 0 };
    static const QUMethod slot_5 = {"rename_prev", 0, 0 };
    static const QUMethod slot_6 = {"remove_prev", 0, 0 };
    static const QUMethod slot_7 = {"update", 0, 0 };
    static const QUMethod slot_8 = {"updateonce", 0, 0 };
    static const QUParameter param_slot_9[] = {
	{ "item", &static_QUType_ptr, "QIconViewItem", QUParameter::In }
    };
    static const QUMethod slot_9 = {"cut_fin", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "item", &static_QUType_ptr, "QIconViewItem", QUParameter::In }
    };
    static const QUMethod slot_10 = {"copy_fin", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ "item", &static_QUType_ptr, "QIconViewItem", QUParameter::In }
    };
    static const QUMethod slot_11 = {"rename_fin", 1, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ "item", &static_QUType_ptr, "QIconViewItem", QUParameter::In }
    };
    static const QUMethod slot_12 = {"remove_fin", 1, param_slot_12 };
    static const QUMethod slot_13 = {"paste", 0, 0 };
    static const QUMethod slot_14 = {"currentDir", 0, 0 };
    static const QUMethod slot_15 = {"regupdate", 0, 0 };
    static const QUParameter param_slot_16[] = {
	{ "i", &static_QUType_ptr, "QIconViewItem", QUParameter::In }
    };
    static const QUMethod slot_16 = {"itemDoubleClicked", 1, param_slot_16 };
    static const QUParameter param_slot_17[] = {
	{ "e", &static_QUType_ptr, "QDropEvent", QUParameter::In },
	{ 0, &static_QUType_ptr, "QValueList<QIconDragItem>", QUParameter::In }
    };
    static const QUMethod slot_17 = {"slotDropped", 2, param_slot_17 };
    static const QUMethod slot_18 = {"viewLarge", 0, 0 };
    static const QUMethod slot_19 = {"viewDetail", 0, 0 };
    static const QUMethod slot_20 = {"viewBottom", 0, 0 };
    static const QUMethod slot_21 = {"viewRight", 0, 0 };
    static const QUMethod slot_22 = {"flowEast", 0, 0 };
    static const QUMethod slot_23 = {"flowSouth", 0, 0 };
    static const QUMethod slot_24 = {"itemTextTruncate", 0, 0 };
    static const QUMethod slot_25 = {"itemTextWordWrap", 0, 0 };
    static const QUMethod slot_26 = {"sortAscending", 0, 0 };
    static const QUMethod slot_27 = {"sortDescending", 0, 0 };
    static const QUMethod slot_28 = {"arrangeItemsInGrid", 0, 0 };
    static const QUParameter param_slot_29[] = {
	{ "item", &static_QUType_ptr, "QIconViewItem", QUParameter::In }
    };
    static const QUMethod slot_29 = {"slotRightPressed", 1, param_slot_29 };
    static const QUMethod slot_30 = {"openFolder", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "setDirectory(const QString&)", &slot_0, QMetaData::Public },
	{ "setDirectory(const QDir&)", &slot_1, QMetaData::Public },
	{ "newDirectory()", &slot_2, QMetaData::Public },
	{ "cut_prev()", &slot_3, QMetaData::Public },
	{ "copy_prev()", &slot_4, QMetaData::Public },
	{ "rename_prev()", &slot_5, QMetaData::Public },
	{ "remove_prev()", &slot_6, QMetaData::Public },
	{ "update()", &slot_7, QMetaData::Public },
	{ "updateonce()", &slot_8, QMetaData::Public },
	{ "cut_fin(QIconViewItem*)", &slot_9, QMetaData::Public },
	{ "copy_fin(QIconViewItem*)", &slot_10, QMetaData::Public },
	{ "rename_fin(QIconViewItem*)", &slot_11, QMetaData::Public },
	{ "remove_fin(QIconViewItem*)", &slot_12, QMetaData::Public },
	{ "paste()", &slot_13, QMetaData::Public },
	{ "currentDir()", &slot_14, QMetaData::Public },
	{ "regupdate()", &slot_15, QMetaData::Private },
	{ "itemDoubleClicked(QIconViewItem*)", &slot_16, QMetaData::Protected },
	{ "slotDropped(QDropEvent*,const QValueList<QIconDragItem>&)", &slot_17, QMetaData::Protected },
	{ "viewLarge()", &slot_18, QMetaData::Protected },
	{ "viewDetail()", &slot_19, QMetaData::Protected },
	{ "viewBottom()", &slot_20, QMetaData::Protected },
	{ "viewRight()", &slot_21, QMetaData::Protected },
	{ "flowEast()", &slot_22, QMetaData::Protected },
	{ "flowSouth()", &slot_23, QMetaData::Protected },
	{ "itemTextTruncate()", &slot_24, QMetaData::Protected },
	{ "itemTextWordWrap()", &slot_25, QMetaData::Protected },
	{ "sortAscending()", &slot_26, QMetaData::Protected },
	{ "sortDescending()", &slot_27, QMetaData::Protected },
	{ "arrangeItemsInGrid()", &slot_28, QMetaData::Protected },
	{ "slotRightPressed(QIconViewItem*)", &slot_29, QMetaData::Protected },
	{ "openFolder()", &slot_30, QMetaData::Protected }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"directoryChanged", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "dirs", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"startReadDir", 1, param_signal_1 };
    static const QUMethod signal_2 = {"readNextDir", 0, 0 };
    static const QUMethod signal_3 = {"readDirDone", 0, 0 };
    static const QUMethod signal_4 = {"enableUp", 0, 0 };
    static const QUMethod signal_5 = {"disableUp", 0, 0 };
    static const QUMethod signal_6 = {"enableMkdir", 0, 0 };
    static const QUMethod signal_7 = {"disableMkdir", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "directoryChanged(const QString&)", &signal_0, QMetaData::Private },
	{ "startReadDir(int)", &signal_1, QMetaData::Private },
	{ "readNextDir()", &signal_2, QMetaData::Private },
	{ "readDirDone()", &signal_3, QMetaData::Private },
	{ "enableUp()", &signal_4, QMetaData::Private },
	{ "disableUp()", &signal_5, QMetaData::Private },
	{ "enableMkdir()", &signal_6, QMetaData::Private },
	{ "disableMkdir()", &signal_7, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"QtFileIconView", parentObject,
	slot_tbl, 31,
	signal_tbl, 8,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_QtFileIconView.setMetaObject( metaObj );
    return metaObj;
}

void* QtFileIconView::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "QtFileIconView" ) )
	return this;
    return QIconView::qt_cast( clname );
}

// SIGNAL directoryChanged
void QtFileIconView::directoryChanged( const QString& t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

// SIGNAL startReadDir
void QtFileIconView::startReadDir( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 1, t0 );
}

// SIGNAL readNextDir
void QtFileIconView::readNextDir()
{
    activate_signal( staticMetaObject()->signalOffset() + 2 );
}

// SIGNAL readDirDone
void QtFileIconView::readDirDone()
{
    activate_signal( staticMetaObject()->signalOffset() + 3 );
}

// SIGNAL enableUp
void QtFileIconView::enableUp()
{
    activate_signal( staticMetaObject()->signalOffset() + 4 );
}

// SIGNAL disableUp
void QtFileIconView::disableUp()
{
    activate_signal( staticMetaObject()->signalOffset() + 5 );
}

// SIGNAL enableMkdir
void QtFileIconView::enableMkdir()
{
    activate_signal( staticMetaObject()->signalOffset() + 6 );
}

// SIGNAL disableMkdir
void QtFileIconView::disableMkdir()
{
    activate_signal( staticMetaObject()->signalOffset() + 7 );
}

bool QtFileIconView::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setDirectory((const QString&)static_QUType_QString.get(_o+1)); break;
    case 1: setDirectory((const QDir&)*((const QDir*)static_QUType_ptr.get(_o+1))); break;
    case 2: newDirectory(); break;
    case 3: cut_prev(); break;
    case 4: copy_prev(); break;
    case 5: rename_prev(); break;
    case 6: remove_prev(); break;
    case 7: update(); break;
    case 8: updateonce(); break;
    case 9: cut_fin((QIconViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 10: copy_fin((QIconViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 11: rename_fin((QIconViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 12: remove_fin((QIconViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 13: paste(); break;
    case 14: currentDir(); break;
    case 15: regupdate(); break;
    case 16: itemDoubleClicked((QIconViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 17: slotDropped((QDropEvent*)static_QUType_ptr.get(_o+1),(const QValueList<QIconDragItem>&)*((const QValueList<QIconDragItem>*)static_QUType_ptr.get(_o+2))); break;
    case 18: viewLarge(); break;
    case 19: viewDetail(); break;
    case 20: viewBottom(); break;
    case 21: viewRight(); break;
    case 22: flowEast(); break;
    case 23: flowSouth(); break;
    case 24: itemTextTruncate(); break;
    case 25: itemTextWordWrap(); break;
    case 26: sortAscending(); break;
    case 27: sortDescending(); break;
    case 28: arrangeItemsInGrid(); break;
    case 29: slotRightPressed((QIconViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 30: openFolder(); break;
    default:
	return QIconView::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool QtFileIconView::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: directoryChanged((const QString&)static_QUType_QString.get(_o+1)); break;
    case 1: startReadDir((int)static_QUType_int.get(_o+1)); break;
    case 2: readNextDir(); break;
    case 3: readDirDone(); break;
    case 4: enableUp(); break;
    case 5: disableUp(); break;
    case 6: enableMkdir(); break;
    case 7: disableMkdir(); break;
    default:
	return QIconView::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool QtFileIconView::qt_property( int id, int f, QVariant* v)
{
    return QIconView::qt_property( id, f, v);
}

bool QtFileIconView::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
