#include <QtGui>
#include <QtGlobal>
#include "herowinimpl.h"
//=====================================================================================
herowinimpl::herowinimpl(Hero *h) 
: QWidget(0,0)
{
	setupUi(this);
	hero = h;
	setWindowFlags(Qt::Tool);
	desk = qApp->desktop()->screenGeometry();
	move((desk.width()-width())/2, (desk.height()-height())/2);
	connect(btGood, SIGNAL(released()), this, SLOT(doGood()));
	connect(btBad, SIGNAL(released()), this, SLOT(doBad()));
	connect(btSay, SIGNAL(released()), this, SLOT(say()));
}
//=====================================================================================
void herowinimpl::showEvent(QShowEvent *event)
{
	desk = qApp->desktop()->screenGeometry();
	move((desk.width()-width())/2, (desk.height()-height())/2);
}
//=====================================================================================
void herowinimpl::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) hide();
}
//=====================================================================================
void herowinimpl::update()
{
	QString str;
	lbHero->setText(tr(hero->name.toAscii()));
	lbGod->setText(tr(hero->godName.toAscii()));
	lbHail->setText(tr(hero->hail.toAscii()));
	lbChar->setText(tr(hero->caracter.toAscii()));
	lbAge->setText(tr(hero->age.toAscii()));
	lbLevel->setText(str.setNum(hero->level));
	pbLevel->setValue(hero->expa);
	lbHealth->setText(str.setNum(hero->health)+" / "+str.setNum(hero->healthAll));
	if (hero->healthAll > 0)
		pbHealth->setValue(int((float(hero->health) / float(hero->healthAll))*100.00));
	lbQuest->setText(tr("№ ")+str.setNum(hero->quest));
	pbQuest->setValue(hero->questPercent);
	lbQuestName->setText(tr(hero->questName.toAscii()));
	lbMoney->setText(tr("Капитал: ")+tr(hero->money.toAscii()));
	lbKills->setText(tr("Убито монстров: ")+tr(hero->kills.toAscii()));
	lbDeaths->setText(str.setNum(hero->deaths));
	lbDist->setText(tr(hero->cityDistance.toAscii()));
	lbBricks->setText(tr(hero->bricks.toAscii()));
	pbPrane->setValue(hero->prane);
	
	updateDiary();
	updateItems();
	updateEquipment();
}
//=====================================================================================
void herowinimpl::updateDiary()
{
	lbDiary->setText("");
	QString str = "";
	int end = hero->tmpdiary.count();
	if (hero->tmpdiary.count() > 7) end = 7;
	for (int i = hero->tmpdiary.count()-1; i >= hero->tmpdiary.count()-end; i--){
		SDiaryNote dn = hero->tmpdiary.at(i);
		str += "<div style=\"font-weight: bold; margin-left: 0px;\">"+dn.time+"</div>"+
			   "<div style=\"margin-left:20px;\">"+dn.name+"</div>";
	}
	lbDiary->setText(tr(str.toAscii()));
}
//=====================================================================================
void herowinimpl::updateItems()
{
	lbItems->setText("");
	QString str = "<UL>";
	for (int i = 0; i < hero->items.count();i++){
		str += "<LI>"+hero->items.at(i);
	}
	if (hero->items.count() == 0)
		str = "<div style=\"font-weight: bold;\"><center>Пусто</center></div>";
	else str += "</UL>";
	lbItems->setText(tr(str.toAscii()));
}
//=====================================================================================
void herowinimpl::updateEquipment()
{
	lbEquip->setText("");
	QString str = "";
	for (int i = 0; i < hero->equipment.count();i++){
		str += "<div style=\"font-weight: bold; margin-left: 0px;\">";
		switch(i){
			case 0:
				str += "Оружие";
				break;
			case 1:
				str += "Щит";
				break;
			case 2:
				str += "Голова";
				break;
			case 3:
				str += "Тело";
				break;
			case 4:
				str += "Руки";
				break;
			case 5:
				str += "Ноги";
				break;
			case 6:
				str += "Талисман";
				break;
		}
		str += "</div><div style=\"margin-left:20px;\">"+hero->equipment.at(i)+"</div>";
	}
	if (hero->equipment.count() == 0)
		str = "<div style=\"font-weight: bold;\"><center>Пусто</center></div>";
	lbEquip->setText(tr(str.toAscii()));
}
//=====================================================================================
void herowinimpl::doGood()
{
	hero->doGood();
}
//=====================================================================================
void herowinimpl::doBad()
{
	hero->doBad();
}
//=====================================================================================
void herowinimpl::say()
{
	if (leFrase->text() != "") hero->say(leFrase->text());
	leFrase->setText("");
	btSay->setEnabled(false);
}
//=====================================================================================
