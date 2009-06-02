#ifndef MESSAGER_H
#define MESSAGER_H
//=====================================================================================
#include <QWidget>
#include <QtGui>
#ifndef Q_OS_WIN32
#include <QtDBus>
#include <QDBusConnection>
#endif
#include "ui_messager.h"
//=====================================================================================
class HeroMessager : public QWidget, public Ui::MessageWin
{
Q_OBJECT
public:
	HeroMessager();
	void open(QString head, QString text);
private slots:
	void showT();
	void hideT();
	void stay();
#ifndef Q_OS_WIN32
        void knotifySend(QString head, QString text);
#endif
private:
	int showTime, hideTime;
	QTimer *showTimer, *hideTimer, *stayTimer;
	QRect desk;
        QString notifyType;
};
//=====================================================================================
#endif
