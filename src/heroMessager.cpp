#include "heroMessager.h"
//=====================================================================================
HeroMessager::HeroMessager()
: QWidget()
{
        QSettings settings("godville.net", "godvilleQT");
        notifyType = settings.value("notifyType",QString("standart")).toString();
        setupUi(this);
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
    QSettings settings("godville.net", "godvilleQT");
    notifyType = settings.value("notifyType",QString("standart")).toString();
    if(notifyType=="standart")
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
#ifndef Q_OS_WIN32
    else
    {
        headS.replace('"',"\\\"");
        textS.replace('"',"\\\"");
            if(notifyType=="libnotify")
                QProcess::startDetached(QString("notify-send \"%1\" \"%2\" -t 4000").arg(tr(headS.toAscii())).arg(tr(textS.toAscii())));
        else
            if(notifyType=="knotify3")
            {
                QProcess::startDetached(QString("kdialog --passivepopup \"%1\" 4").arg(tr(textS.toAscii())));
            }
        else
            if(notifyType=="knotify4")
            {
                emit knotifySend(tr(headS.toAscii()),tr(textS.toAscii()));
            }
    }
#endif
}
//=====================================================================================
#ifndef Q_OS_WIN32
void HeroMessager::knotifySend(QString head, QString text)
{
    QDBusConnection connection = QDBusConnection(QDBusConnection(QDBusConnection::connectToBus(QDBusConnection::SessionBus,"org.godvilleqt.notify")));
    if(connection.isConnected())
        qDebug() << "Connected to DBus";
    else
    {
        qDebug() << "Can't connect to DBus";
        qDebug() << connection.lastError();
        return;
    }
    QDBusMessage msg = QDBusMessage::createMethodCall("org.kde.VisualNotifications",
                                                      "/VisualNotifications","org.kde.VisualNotifications","Notify");
    QList<QVariant> args;
    //method uint org.kde.VisualNotifications.Notify(QString app_name, uint replaces_id, QString event_id,
    //QString app_icon, QString summary, QString body, QStringList actions, QVariantMap hints, int timeout)
    args.append(QVariant("GodvilleQT"));//app name
    args.append(QVariant(quint32(0)));//replace id
    args.append(QVariant("GodvillePopup"));//event id
    args.append(QVariant("dialog-information"));//app icon
    args.append(QVariant(head));//summury
    args.append(QVariant(text));//body
    args.append(QVariant(QStringList()));//actions
    args.append(QVariant(QVariantMap()));//actions
    args.append(QVariant(qint32(4000)));//timeout
    msg.setArguments(args);
    if(!connection.send(msg))
    {
        qDebug() << "message send error";
        qDebug() << connection.lastError();
    }
    QCoreApplication::processEvents();
}
#endif
