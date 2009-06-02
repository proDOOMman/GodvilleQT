#ifndef STATSWINIMPL_H
#define STATSWINIMPL_H
//
#include <QWidget>
#include <QtGui>
#include <QCloseEvent>
#include "ui_statswin.h"
#include "hero.h"
#include "herowinimpl.h"
#include "diarywinimpl.h"
#include "heroMessager.h"
#include "Dialog.h"
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
        void closeEvent ( QCloseEvent * event );
private:
	Hero *hero;
	herowinimpl *hwin;
	diarywinimpl *diary;
	QSystemTrayIcon *tray;
	QRect desk;
	QTimer *timer;
	QAction *showmess;
	HeroMessager *mess;
        QDialog *settingsDialog;
	
private slots:
	void on_btInfo_pressed();
	void on_btDiary_pressed();
        void settings();
        void updateSettings();
};
//=====================================================================================
#endif

