#include <QtGui>
#include <QtGlobal>
#include "diarywinimpl.h"
//=====================================================================================
diarywinimpl::diarywinimpl() 
: QWidget(0,0)
{
	setupUi(this);
	setWindowFlags(Qt::Tool);
	desk = qApp->desktop()->screenGeometry();
	move((desk.width()-width())/2, (desk.height()-height())/2);
}
//=====================================================================================
void diarywinimpl::showEvent(QShowEvent *event)
{
	desk = qApp->desktop()->screenGeometry();
	move((desk.width()-width())/2, (desk.height()-height())/2);
}
//=====================================================================================
void diarywinimpl::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) hide();
}
//=====================================================================================
void diarywinimpl::setDiary(QList<SDiaryNote> diary)
{
	/*diary.clear();
	for (int i = 0; i < 10; i++){
		SDiaryNote dn;
		
		dn.time = "12:00";
		dn.name = "Персонаж опять сморозил херню и почти помер";
		dn.details.append("Вести с полей");
		
		diary.append(dn);
	}*/
	text->setText("");
	QString str = "";
	for (int i = diary.count()-1; i >= 0; i--){
		SDiaryNote dn = diary.at(i);
		str += "<div style=\"font-weight: bold; margin-left: 0px;\">"+dn.time+"</div>"+
			   "<div style=\"margin-left:20px;\">"+dn.name+"</div>";
		for (int j = 0; j < dn.details.count(); j++)
			str += "<div style=\"margin-left: 30px;\"><i>"+dn.details.at(j)+"</i></div>";
	}
	text->setText(tr(str.toAscii()));
}
//=====================================================================================
