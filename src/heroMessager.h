#ifndef MESSAGER_H
#define MESSAGER_H
//=====================================================================================
#include <QWidget>
#include <QtGui>
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
private:
	int showTime, hideTime;
	QTimer *showTimer, *hideTimer, *stayTimer;
	QRect desk;
};
//=====================================================================================
#endif
