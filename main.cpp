/****************************************************************************
** main.cpp
*****************************************************************************/

#include "palmyrafm.h"
#include <QApplication>
#include <QtMessageHandler>

void messageHandler(QtMsgType type, const QMessageLogContext & /*context*/, const QString &msg)
{
    // Filter out the "Message box contains detailed text" message
    if (msg.contains("Message box contains detailed text")) {
        return;
    }
    
    // Let other messages through to default handler
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", localMsg.constData());
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s\n", localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", localMsg.constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", localMsg.constData());
        abort();
    }
}

int main( int argc, char **argv )
{
    // Install custom message handler to filter unwanted Qt messages
    qInstallMessageHandler(messageHandler);
    
    QApplication a( argc, argv );
    
    // Create main window
    FileMainWindow mw;
    mw.resize( 680, 480 );
    
    // Set initial directory
    mw.fileView()->setDirectory( "/" );
    
    // Show window
    mw.show();
    
    return a.exec();
}
