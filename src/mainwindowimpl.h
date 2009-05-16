#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "hero.h"
#include "statswinimpl.h"
//=====================================================================================
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
protected:
	void closeEvent(QCloseEvent *event);
private slots:
	void on_pushButton_clicked();
	void loginDone(QString);
        void proxySettings();
        void saveProxy();
private:
	Hero *hero;
	statswinimpl *stats;
        QSettings *s;

        QCheckBox *useProxy;
        QCheckBox *proxySocks5;
        QLineEdit *proxyAdress;
        QLineEdit *proxyPort;
        QLineEdit *proxyUserName;
        QLineEdit *proxyPass;
        QMainWindow *proxyWindow;
};
//=====================================================================================
#endif




