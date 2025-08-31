/****************************************************************************
** main.cpp
*****************************************************************************/

#include "palmyrafm.h"
#include <QApplication>

int main( int argc, char **argv )
{
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
