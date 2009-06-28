#ifndef HERO_H
#define HERO_H
#include <QtNetwork>

#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <phonon/path.h>
#include <phonon/audiooutput.h>
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
        void pranaRestore();
	void say(QString);
	void updateStats();
	void updateHero();
	
	bool logedin;
	int level, expa, goods, health, healthAll, quest, questPercent, deaths, prane;
	QString name, age, caracter, hail, godName,
        questName, kills, money, falls, lastEvent, cityDistance, bricks, lastNote, previousNote;
	QStringList items, equipment;
	QList<SDiaryNote> diary, tmpdiary;

        bool diaryUp;

signals:
	void done(QString);

public slots:
	void read(QNetworkReply*);

private slots:
        void warning();

private:
	QString convertString(QByteArray bytes);
	void parseHero(QString);
	void parseStats(QString);
	void alert(QString);
	void updateDiary();
	
	QNetworkAccessManager *net;
	QString url;
        QNetworkRequest loginReq, statsReq, heroReq, encourageReq, punishReq, sayReq, pranaRestoreReq, toArena, updateArena;

        Phonon::MediaObject *media;
        Phonon::AudioOutput *audioOutput;
        QTimer *sound_delay;
};
//=====================================================================================
#endif
