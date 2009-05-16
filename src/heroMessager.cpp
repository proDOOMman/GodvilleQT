#include "heroMessager.h"
//=====================================================================================
HeroMessager::HeroMessager()
: QWidget()
{
        setupUi(this);
        QSettings settings("godville.net", "godvilleQT");
        setWindowOpacity(settings.value("popUpOp",100).toInt()/100);
#ifdef Q_OS_MAC
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
#else
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
#endif
	showTimer = new QTimer(this);
	showTimer->setInterval(10);
	connect(showTimer, SIGNAL(timeout()), this, SLOT(showT()));

	stayTimer = new QTimer(this);
	stayTimer->setInterval(3500);
	connect(stayTimer, SIGNAL(timeout()), this, SLOT(stay()));

	hideTimer = new QTimer(this);
	hideTimer->setInterval(10);
	connect(hideTimer, SIGNAL(timeout()), this, SLOT(hideT()));
	showTime = 700;
	hideTime = 500;
	showTimer->stop();
	hideTimer->stop();
	stayTimer->stop();
}
//=====================================================================================
void HeroMessager::showT()
{
	if (x() > desk.width()-width()){
		move(x()-int((float(width())/float(showTime))*float(showTimer->interval())), y());
	} else {
		showTimer->stop();
		stayTimer->start();
	}
}
//=====================================================================================
void HeroMessager::hideT()
{
	if (x() < desk.width()){
		move(x()+int((float(width())/float(hideTime))*float(hideTimer->interval())), y());
	} else {
		hideTimer->stop();
		hide();
	}
}
//=====================================================================================
void HeroMessager::stay()
{
	stayTimer->stop();
	hideTimer->start();
}
//=====================================================================================
void HeroMessager::open(QString headS, QString textS)
{
	showTimer->stop();
	hideTimer->stop();
	stayTimer->stop();
	head->setText(tr(headS.toAscii()));
        text->setText(tr(textS.toAscii()));
	desk = qApp->desktop()->availableGeometry();
	move(desk.width(), desk.height()-height()-25);
	show();
	showTimer->start();
}
//=====================================================================================
