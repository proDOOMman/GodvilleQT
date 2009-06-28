#ifndef DAIRYWINIMPL_H
#define DAIRYWINIMPL_H
//
#include <QWidget>
#include "ui_diarywin.h"
#include "hero.h"
//=====================================================================================
class diarywinimpl : public QWidget, public Ui::DiaryWin
{
Q_OBJECT
public:
	diarywinimpl();
	void setDiary(QList<SDiaryNote> diary);
	void saveDiary(QString);
	QString loadDiary();
protected:
	void showEvent(QShowEvent *event);
	void keyPressEvent(QKeyEvent *event);
private:
	QRect desk;
	QString oldrecs;
	int offset;
	bool first;

private slots:
    void on_downButton_released();
    void on_upButton_released();
};
//=====================================================================================
#endif
