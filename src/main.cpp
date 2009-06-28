#include <QApplication>
#include "mainwindowimpl.h"
#include "heroMessager.h"

void myMessageOutput(QtMsgType type, const char *msg)
{
#ifdef Q_WS_WIN
    QFile f("Debug.log");
#else
    QFile f(QDir::home().absoluteFilePath(".godville/Debug.log"));
#endif
    f.open(QIODevice::Append);
    switch (type) {
        case QtDebugMsg:
            f.write(("Debug: "+QString(msg)+"\n").toAscii());
            break;
        case QtWarningMsg:
            f.write(("Warning: "+QString(msg)+"\n").toAscii());
            break;
        case QtCriticalMsg:
            f.write(("Critical: "+QString(msg)+"\n").toAscii());
            break;
        case QtFatalMsg:
            f.write(("Fatal: "+QString(msg)+"\n").toAscii());
            abort();
    }
    f.close();
}
//
int main(int argc, char ** argv)
{
#ifdef Q_WS_WIN
        QFile::remove("Debug.log");
#else
        if(!QDir::home().exists(".godville"))
            QDir::home().mkdir(".godville");
        QFile::remove(QDir::home().absoluteFilePath(".godville/Debug.log"));
#endif
        //qInstallMsgHandler(myMessageOutput);
	QApplication app( argc, argv );
        QCoreApplication::setApplicationName("GodvilleQT");
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
        MainWindowImpl win;
        win.show();
        //app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();
}
