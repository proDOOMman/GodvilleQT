#include <QtGui>
#include <QtGlobal>
#include "mainwindowimpl.h"
//=====================================================================================
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, Qt::WindowStaysOnTopHint)
{
        setupUi(this);
	setWindowFlags(Qt::Tool);
	
	QRect desk = qApp->desktop()->screenGeometry();
	move((desk.width()-width())/2, (desk.height()-height())/2);
	
	hero = new Hero();
	connect(hero, SIGNAL(done(QString)), this, SLOT(loginDone(QString)));
	connect(passLine, SIGNAL(returnPressed()), this, SLOT(on_pushButton_clicked()));
        connect(proxyButton,SIGNAL(released()),this,SLOT(proxySettings()));
	setTabOrder(logLine, passLine);
	setTabOrder(passLine, pushButton);
	setTabOrder(pushButton, logLine);

        s = new QSettings("godville.net","godvilleQT",this);
        savePassCheckBox->setChecked(s->value("savePass",false).toBool());
        logLine->setText(s->value("godName",QString()).toString());
        passLine->setText(s->value("password",QString()).toString());
}
//=====================================================================================
void MainWindowImpl::proxySettings()
{
    proxyWindow = new QMainWindow(this);
    proxyWindow->setWindowModality(Qt::WindowModal);
    QWidget *w = new QWidget(proxyWindow);
    proxyWindow->setCentralWidget(w);
    QVBoxLayout *l = new QVBoxLayout();
    w->setLayout(l);
    useProxy = new QCheckBox(trUtf8("Использовать proxy"),w);
    l->addWidget(useProxy);
    useProxy->setChecked(s->value("useProxy",false).toBool());
    l->addWidget(new QLabel(trUtf8("Адрес прокси сервера:"),w));
    proxyAdress = new QLineEdit(s->value("proxyAdress","127.0.0.1").toString(),w);
    l->addWidget(proxyAdress);
    l->addWidget(new QLabel(trUtf8("Номер порта:"),w));
    proxyPort = new QLineEdit(s->value("proxyPort","8080").toString(),w);
    l->addWidget(proxyPort);
    l->addWidget(new QLabel(trUtf8("Имя пользователя:"),w));
    proxyUserName = new QLineEdit(s->value("proxyUserName",QString()).toString());
    l->addWidget(proxyUserName);
    l->addWidget(new QLabel(trUtf8("Пароль:"),w));
    proxyPass = new QLineEdit(s->value("proxyPass",QString()).toString());
    proxyPass->setEchoMode(QLineEdit::Password);
    l->addWidget(proxyPass);
    proxySocks5 = new QCheckBox(trUtf8("SOCKS5 прокси"),w);
    proxySocks5->setChecked(s->value("SOCKS5",false).toBool());
    l->addWidget(proxySocks5);
    QPushButton *but = new QPushButton(trUtf8("Сохранить"),w);
    l->addWidget(but);

    connect(but,SIGNAL(released()),this,SLOT(saveProxy()));
    proxyWindow->show();
}
//=====================================================================================
void MainWindowImpl::saveProxy()
{
    s->setValue("useProxy",useProxy->isChecked());
    s->setValue("proxyAdress",proxyAdress->text());
    s->setValue("proxyPort",proxyPort->text());
    s->setValue("proxyUserName",proxyUserName->text());
    s->setValue("proxyPass",proxyPass->text());
    s->setValue("SOCKS5",proxySocks5->isChecked());
    proxyWindow->close();
}
//=====================================================================================
void MainWindowImpl::closeEvent(QCloseEvent *event)
{
	qApp->quit();
}
//=====================================================================================
void MainWindowImpl::on_pushButton_clicked()
{
        s->setValue("godName",logLine->text());
        if(savePassCheckBox->isChecked())
            s->setValue("password",passLine->text());
        else
            s->setValue("password",QString());
        s->setValue("savePass",savePassCheckBox->isChecked());
	pushButton->setText(tr("Логинимся..."));
	pushButton->setDisabled(true);
	hero->login(logLine->text(), passLine->text());
}
//=====================================================================================
void MainWindowImpl::loginDone(QString s)
{
	if (s == "login"){
		if (!hero->logedin){
			pushButton->setText(tr("OK"));
			pushButton->setDisabled(false);
			QMessageBox msgBox;
                        msgBox.setWindowTitle(tr("Ошибка!"));
                        msgBox.setText(tr("Неверный логин или пароль.\nА может на сервере чё поменялось или поломалось..."));
			msgBox.exec();
		} else {
			disconnect(hero, SIGNAL(done(QString)), this, SLOT(loginDone(QString)));
			stats = new statswinimpl(hero);
			stats->show();
			hide();
		}
	}
}
//=====================================================================================
