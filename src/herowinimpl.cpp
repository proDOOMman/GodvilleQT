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
        //lbHero->setText(tr(hero->name.toAscii()));
        lbHero->setText(hero->name);
	lbGod->setText(hero->godName);
        //lbHail->setText(tr(hero->hail.toAscii()));
        lbHail->setText(hero->hail);
        //lbChar->setText(tr(hero->caracter.toAscii()));
        lbChar->setText(hero->caracter);
        //lbAge->setText(tr(hero->age.toAscii()));
        lbAge->setText(hero->age);
	lbLevel->setText(str.setNum(hero->level));
	pbLevel->setValue(hero->expa);
	lbHealth->setText(str.setNum(hero->health)+" / "+str.setNum(hero->healthAll));
	if (hero->healthAll > 0)
		pbHealth->setValue(int((float(hero->health) / float(hero->healthAll))*100.00));
	lbQuest->setText(tr("№ ")+str.setNum(hero->quest));
	pbQuest->setValue(hero->questPercent);
        //lbQuestName->setText(tr(hero->questName.toAscii()));
        lbQuestName->setText(hero->questName);
        //lbMoney->setText(tr("Капитал: ")+tr(hero->money.toAscii()));
        lbMoney->setText(tr("Капитал: ")+hero->money);
        //lbKills->setText(tr("Убито монстров: ")+tr(hero->kills.toAscii()));
        lbKills->setText(tr("Убито монстров: ")+hero->kills);
	lbDeaths->setText(str.setNum(hero->deaths));
        //lbDist->setText(tr(hero->cityDistance.toAscii()));
        lbDist->setText(hero->cityDistance);
        //lbBricks->setText(tr(hero->bricks.toAscii()));
        lbBricks->setText(hero->bricks);
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
        //lbDiary->setText(tr(str.toAscii()));
        lbDiary->setText(str);
}
//=====================================================================================
void herowinimpl::updateItems()
{
	lbItems->setText("");
        //QString str = "<UL>";
        QString str;
	for (int i = 0; i < hero->items.count();i++){
                //str += "<LI>"+hero->items.at(i);
                str += trUtf8("• ") + hero->items.at(i) + '\n';
	}
	if (hero->items.count() == 0)
                str = trUtf8("<div style=\"font-weight: bold;\"><center>Пусто</center></div>");
        //else str += "</UL>";
        str.remove(str.length(),1);
        //lbItems->setText(tr(str.toAscii()));
        lbItems->setText(str);
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
                                str += trUtf8("Оружие");
				break;
			case 1:
                                str += trUtf8("Щит");
				break;
			case 2:
                                str += trUtf8("Голова");
				break;
			case 3:
                                str += trUtf8("Тело");
				break;
			case 4:
                                str += trUtf8("Руки");
				break;
			case 5:
                                str += trUtf8("Ноги");
				break;
			case 6:
                                str += trUtf8("Талисман");
				break;
		}
                //str += "</div><div style=\"margin-left:20px;\">"+hero->equipment.at(i)+"</div>";
                str += "</div><div style=\"margin-left:5px;\">"+hero->equipment.at(i)+"</div>";
	}
	if (hero->equipment.count() == 0)
                str = trUtf8("<div style=\"font-weight: bold;\"><center>Пусто</center></div>");
        //lbEquip->setText(tr(str.toAscii()));
        lbEquip->setText(str);
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

void herowinimpl::on_pushButton_2_released()
{

}
