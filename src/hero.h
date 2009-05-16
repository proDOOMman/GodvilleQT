#ifndef HERO_H
#define HERO_H
#include <QtNetwork>
//=====================================================================================
struct SDiaryNote{
	QString name;
	QString time;
	QStringList details;
};
//=====================================================================================
class Hero : public QObject
{
Q_OBJECT
public:
	Hero(QObject * parent = 0);
	void login(QString log, QString pass);
	void doGood();
	void doBad();
	void say(QString);
	void updateStats();
	void updateHero();
	
	bool logedin;
	int level, expa, goods, health, healthAll, quest, questPercent, deaths, prane;
	QString name, age, caracter, hail, godName,
        questName, kills, money, falls, lastEvent, cityDistance, bricks, lastNote;
	QStringList items, equipment;
	QList<SDiaryNote> diary, tmpdiary;
	
signals:
	void done(QString);
	
public slots:
	void read(QNetworkReply*);

private:
	QString convertString(QByteArray bytes);
	void parseHero(QString);
	void parseStats(QString);
	void alert(QString);
	void updateDiary();
	
	QNetworkAccessManager *net;
	QString url;
	QNetworkRequest loginReq, statsReq, heroReq, encourageReq, punishReq, sayReq;
};
//=====================================================================================
#endif
