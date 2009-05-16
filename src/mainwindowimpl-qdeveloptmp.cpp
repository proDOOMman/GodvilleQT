#include <QtGui>
#include <QtGlobal>
#include "mainwindowimpl.h"
//=====================================================================================
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, Qt::WindowStaysOnTopHint)
{
	setupUi(this);
	setWindowFlags(Qt::Tool);
	
	QRect desk = qApp->desktop()->screenGeometry();
	move((desk.width()-width())/2, (desk.height()-height())/2);
	
	hero = new Hero();
	connect(hero, SIGNAL(done(QString)), this, SLOT(loginDone(QString)));
	connect(passLine, SIGNAL(returnPressed()), this, SLOT(on_pushButton_clicked()));
	setTabOrder(logLine, passLine);
	setTabOrder(passLine, pushButton);
	setTabOrder(pushButton, logLine);
}
//=====================================================================================
void MainWindowImpl::closeEvent(QCloseEvent *event)
{
	qApp->quit();
}
//=====================================================================================
void MainWindowImpl::on_pushButton_clicked()
{
	pushButton->setText(tr("Логинимся..."));
	pushButton->setDisabled(true);
	hero->login(logLine->text(), passLine->text());
}
//=====================================================================================
void MainWindowImpl::loginDone(QString s)
{
	if (s == "login"){
		if (!hero->logedin){
			pushButton->setText(tr("OK"));
			pushButton->setDisabled(false);
			QMessageBox msgBox;
			msgBox.setWindowTitle(tr("Ошика!"));
			msgBox.setText(tr("Неверный логин или пароль.\nА может на сервере че поменялось или поломалось..."));
			msgBox.exec();
		} else {
			disconnect(hero, SIGNAL(done(QString)), this, SLOT(loginDone(QString)));
			stats = new statswinimpl(hero);
			stats->show();
			hide();
		}
	}
}
//=====================================================================================
