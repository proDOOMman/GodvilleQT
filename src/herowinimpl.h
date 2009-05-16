#ifndef HEROWINIMPL_H
#define HEROWINIMPL_H
//=====================================================================================
#include <QWidget>
#include "ui_herowin.h"
#include "hero.h"
//=====================================================================================
class herowinimpl : public QWidget, public Ui::HeroWin
{
Q_OBJECT
public:
	herowinimpl(Hero *);
	void update();
protected:
	void showEvent(QShowEvent *event);
	void keyPressEvent(QKeyEvent *event);
private slots:
	void doGood();
	void doBad();
	void say();
private:
	void updateDiary();
	void updateItems();
	void updateEquipment();
	
	Hero *hero;
	QRect desk;
};
//=====================================================================================
#endif
