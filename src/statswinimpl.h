#ifndef STATSWINIMPL_H
#define STATSWINIMPL_H
//
#include <QWidget>
#include <QtGui>
#include "ui_statswin.h"
#include "hero.h"
#include "herowinimpl.h"
#include "diarywinimpl.h"
#include "heroMessager.h"
//=====================================================================================
class statswinimpl : public QWidget, public Ui::StatsWin
{
Q_OBJECT
public:
	statswinimpl(Hero *);
	void updateInfo();
	
public slots:
	void hideshow();
	void loginDone(QString);
	void update();
	void trayActivated(QSystemTrayIcon::ActivationReason);
	void stayontopToggle(bool);
protected:
	void keyPressEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *event);
        void moveEvent(QMoveEvent * event);
private:
	Hero *hero;
	herowinimpl *hwin;
	diarywinimpl *diary;
	QSystemTrayIcon *tray;
	QRect desk;
	QTimer *timer;
	QAction *showmess;
	HeroMessager *mess;
	
private slots:
	void on_btInfo_pressed();
	void on_btDiary_pressed();
};
//=====================================================================================
#endif

