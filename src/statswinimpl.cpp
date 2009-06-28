#include "statswinimpl.h"
//=====================================================================================

statswinimpl::statswinimpl(Hero *h) 
: QWidget(0,0)
{
	setupUi(this);
	hero = h;
	hwin = new herowinimpl(hero);
	diary = new diarywinimpl();
	
	stayontopToggle(false);
	connect(hero, SIGNAL(done(QString)), this, SLOT(loginDone(QString)));
	
	//трей

#ifdef Q_WS_WIN
        QResource res = QResource("bin/icon.bmp");
#else
        QResource res = QResource("src/icon_128.png");
#endif
	QPixmap pix;
        pix.loadFromData(res.data(), res.size());
	QIcon ico = QIcon(pix);
	tray = new QSystemTrayIcon(ico);
	tray->setVisible(true);
	connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
	
	//меню
	QMenu *menu = new QMenu();
	QAction *hideshow = menu->addAction(tr("Скрыть/Показать"));
	connect(hideshow, SIGNAL(triggered()), this, SLOT(hideshow()));
	menu->addSeparator();
	showmess = menu->addAction(tr("Показывать сообщения"));
	showmess->setCheckable(true);
	showmess->setChecked(true);
	QAction *stayontop = menu->addAction(tr("Поверх всех окон"));
	stayontop->setCheckable(true);
	stayontop->setChecked(false);
	connect(stayontop, SIGNAL(toggled(bool)), this, SLOT(stayontopToggle(bool)));
	menu->addSeparator();
	
	QAction *herotrbt = menu->addAction(tr("Герой"));
	connect(herotrbt, SIGNAL(triggered()), this, SLOT(on_btInfo_pressed()));
	QAction *diarytrbt = menu->addAction(tr("Дневник"));
	connect(diarytrbt, SIGNAL(triggered()), this, SLOT(on_btDiary_pressed()));
	menu->addSeparator();

        settingsDialog = new Dialog(this);
        connect(settingsDialog,SIGNAL(accepted()),this,SLOT(updateSettings()));
        QAction *settingstrbt = menu->addAction(tr("Настройки"));
        connect(settingstrbt,SIGNAL(triggered()),this,SLOT(settings()));
        menu->addSeparator();
        //settingstrbt->setEnabled(false);
	
	QAction *exit = menu->addAction(tr("Выход"));
	connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(exit, SIGNAL(triggered()), tray, SLOT(hide()));
	
	tray->setContextMenu(menu);
	
	//таймер
	timer = new QTimer(this);
	timer->start(15000);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	
        mess = new HeroMessager();

        QSettings settings("godville.net", "godvilleQT");
        restoreGeometry(settings.value("statWinGeometry").toByteArray());
        this->setWindowOpacity(settings.value("statWinOp",100).toInt()/100);
}
//=====================================================================================
void statswinimpl::updateSettings()
{
    QSettings settings("godville.net", "godvilleQT");
    this->setWindowOpacity(settings.value("statWinOp",100).toInt()/100);
    mess->setWindowOpacity(settings.value("popUpOp",50).toInt()/100);
}
//=====================================================================================
void statswinimpl::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
//=====================================================================================
void statswinimpl::moveEvent(QMoveEvent * event)
{
     QSettings settings("godville.net", "godvilleQT");
     settings.setValue("statWinGeometry", saveGeometry());
}
//=====================================================================================
void statswinimpl::settings()
{
    //может тут стоит создавать диалог?
    //connect(settingsDialog,SIGNAL(rejected()),this,SLOT(deleteLater()));
    settingsDialog->exec();
}
//=====================================================================================
void statswinimpl::stayontopToggle(bool c)
{
	if (c)
		setWindowFlags(Qt::SubWindow | Qt::WindowStaysOnTopHint);
	else
		setWindowFlags(Qt::SubWindow);
	if (isHidden() || !isActiveWindow()){
		show();
		activateWindow();
                raise();
        }
        QSettings settings("godville.net", "godvilleQT");
        restoreGeometry(settings.value("statWinGeometry").toByteArray());
}
//=====================================================================================
void statswinimpl::resizeEvent(QResizeEvent *event)
{
        QSettings settings("godville.net", "godvilleQT");
        restoreGeometry(settings.value("statWinGeometry").toByteArray());
}
//=====================================================================================
void statswinimpl::trayActivated(QSystemTrayIcon::ActivationReason r)
{
	if (r == QSystemTrayIcon::Trigger){
                if (isHidden()){
			show();
			activateWindow();
                        raise();
		} else hide();
	}
}
//=====================================================================================
void statswinimpl::update()
{
	hero->updateStats();
	//qDebug() << "timer";
}
//=====================================================================================
//заполнение формы
void statswinimpl::updateInfo()
{
        //QString s;
        lbLevel->setText(QString::number(hero->level));
	pbLevel->setValue(hero->expa);
        lbItems->setText(QString::number(hero->items.count())+" / "+QString::number(hero->goods));
        lbHealth->setText(QString::number(hero->health)+" / "+QString::number(hero->healthAll));
	if (hero->healthAll > 0)
		pbHealth->setValue(int((float(hero->health) / float(hero->healthAll))*100.00));
        lbPrane->setText(QString::number(hero->prane)+"%");
	pbPrane->setValue(hero->prane);
        lbQuestNum->setText(tr("№ ")+QString::number(hero->quest));
	pbQuest->setValue(hero->questPercent);
        //lbQuestName->setText(tr(hero->questName.toAscii()));
        lbQuestName->setText(hero->questName);
        //lbMoney->setText(tr("Капитал: "+hero->money.toAscii()));
        lbMoney->setText(tr("Капитал: ")+hero->money);
	//qDebug() << "stats updated";
	if ((hero->diary.count() > 0)&& showmess->isChecked()){
		QString head = hero->diary.at(hero->diary.count()-1).time;
		QString text = hero->diary.at(hero->diary.count()-1).name;
		bool showmes = true;
		if (hero->diary.count() > 0){
			if (hero->diary.at(hero->diary.count()-1).details.count() > 1){
				if (hero->lastNote != ""){
                                        head = trUtf8("Вести с полей");
					text = hero->lastNote;
				} else showmes = false;
			}
		}
		if (showmes) mess->open(head, text);//tray->showMessage(tr(head.toAscii()), tr(text.toAscii()));
	}
	//qDebug() << "----------------------";
}
//=====================================================================================
void statswinimpl::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) hide();
}
//=====================================================================================
void statswinimpl::hideshow()
{
    qDebug() << "hideshow";
    if (isHidden())
        {
        show();
        activateWindow();
        raise();
        }
    else hide();
}
//=====================================================================================
void statswinimpl::loginDone(QString s)
{
	if (s == "stats"){
		updateInfo();
		hwin->update();
		diary->setDiary(hero->diary);
	}
	if (s == "hero"){
		//qDebug() << "hero updated";
                //lbHail->setText(tr(hero->hail.toAscii()));
                //lbName->setText(tr(hero->name.toAscii()));
                lbHail->setText(hero->hail);
                lbName->setText(hero->name);
		hwin->update();
	}
	if (s == "phrase") hwin->btSay->setEnabled(true);
}
//=====================================================================================
void statswinimpl::on_btDiary_pressed()
{
	diary->setDiary(hero->diary);
	diary->show();
	diary->activateWindow();
        diary->raise();
}
//=====================================================================================
void statswinimpl::on_btInfo_pressed()
{
	hwin->show();
	hwin->activateWindow();
        hwin->raise();
}
//=====================================================================================
