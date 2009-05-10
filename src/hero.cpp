#include <QtGui>
#include "hero.h"
//=====================================================================================
Hero::Hero(QObject * parent) 
{
	//для аяксов:
	//req.setRawHeader("X-Requested-With","XMLHttpRequest");
	
        net = new QNetworkAccessManager(this);
        QSettings s("godville.net","godvilleQT");
        if(s.value("useProxy").toBool())
        {
            if(!s.value("SOCKS5").toBool())
                net->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy,s.value("proxyAdress").toString(),
                                                     s.value("proxyPort").toInt(),s.value("proxyUserName").toString(),
                                                     s.value("proxyPass").toString()));
            else
                net->setProxy(QNetworkProxy(QNetworkProxy::Socks5Proxy,s.value("proxyAdress").toString(),
                                                     s.value("proxyPort").toInt(),s.value("proxyUserName").toString(),
                                                     s.value("proxyPass").toString()));
        }
        connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(read(QNetworkReply*)));
	url = "http://www.godville.net/hero";
	
	loginReq = QNetworkRequest(QUrl("http://www.godville.net/login/login"));
	statsReq = QNetworkRequest(QUrl("http://www.godville.net/hero/update_details"));
	statsReq.setRawHeader("X-Requested-With","XMLHttpRequest");
	heroReq = QNetworkRequest(QUrl("http://www.godville.net/hero/update_hero_info"));
	heroReq.setRawHeader("X-Requested-With","XMLHttpRequest");
	
	encourageReq = QNetworkRequest(QUrl("http://www.godville.net/hero/encourage"));
	encourageReq.setRawHeader("X-Requested-With","XMLHttpRequest");
	punishReq = QNetworkRequest(QUrl("http://www.godville.net/hero/punish"));
	punishReq.setRawHeader("X-Requested-With","XMLHttpRequest");
	sayReq = QNetworkRequest(QUrl("http://www.godville.net/hero/god_phrase"));
	sayReq.setRawHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
	sayReq.setRawHeader("X-Requested-With","XMLHttpRequest");
	//update_hero_stats - статистика
	//update_timings - инвентарь
	//update_last_events - дневник
	//update_details - все кроме дневника и героя
	//update_hero_info - герой
	
	logedin = false;
}
//=====================================================================================
void Hero::login(QString log, QString pass)
{
	logedin = false;
	godName = log; 
	QString data = "username="+log.toAscii()+"&password="+pass.toAscii();
	net->post(loginReq, data.toAscii());
        //может лучше использовать toLocal8Bit() ?
}
//=====================================================================================
void Hero::updateStats()
{
	if (logedin) net->get(statsReq);
}
//=====================================================================================
void Hero::updateHero()
{
	if (logedin) net->get(heroReq);
}
//=====================================================================================
//PRIVATE
//=====================================================================================
void Hero::parseHero(QString data)
{
	/*QFile *f = new QFile("hero.txt");
	f->open(QIODevice::ReadWrite);
	f->write(data.toAscii());
	f->close();*/
	
	QString nm = "Имя</label> <div class=\\\"field_content\\\">";
	QString nm0 = "</div> </div>";
	QString cr = "Характер</span> <span class=\\\"field_content\\\">";
	QString cr0 = "</span> </div>";
	QString hl = "Девиз</label> <div class=\\\"field_content\\\"><i>";
	QString hl0 = "</i></div> </div>";
	QString ag = "Возраст</label> <div class=\\\"field_content\\\">";
	QString ag0 = "</div> </div>";
	
	int pos = data.indexOf(nm)+nm.length();
	name = data.mid(pos, data.indexOf(nm0, pos)-pos);
	
	pos = data.indexOf(cr)+cr.length();
	caracter = data.mid(pos, data.indexOf(cr0, pos)-pos);
	
	pos = data.indexOf(hl)+hl.length();
	hail = data.mid(pos, data.indexOf(hl0, pos)-pos);
	
	pos = data.indexOf(ag)+ag.length();
	age = data.mid(pos, data.indexOf(ag0, pos)-pos);
}
//=====================================================================================
void Hero::parseStats(QString data)
{
	/*QFile *f = new QFile("stats.txt");
	f->open(QIODevice::ReadWrite);
	f->write(data.toAscii());
	f->close();*/
	QString st, st0, tmp;
	int pos;

//статистика
        st = "Столбов от столицы</span> <span class=\\\"field_content\\\">";
	st0 = "</span> </div>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length())
		cityDistance = data.mid(pos, data.indexOf(st0, pos)-pos);
	//else cityDistance = "в городе";
        else
        {
            st = "Город</span> <span class=\\\"field_content\\\">";
            st0 = "</span> </div>";
            pos = data.indexOf(st)+st.length();
            if (pos > st.length())
                    cityDistance = data.mid(pos, data.indexOf(st0, pos)-pos);
        }

	
	st = "Кирпичей для храма</span><span class=\\\"field_content\\\">";
	st0 = "</span>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length())
		bricks = data.mid(pos, data.indexOf(st0, pos)-pos);
	
	st = "Побед / Поражений</span> <span class=\\\"field_content\\\">";
	st0 = "</span> </div>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length())
		falls = data.mid(pos, data.indexOf(st0, pos)-pos);
	
	st = "Смертей</span> <span class=\\\"field_content\\\">";
	st0 = "</span> </div>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length()){
		tmp = data.mid(pos, data.indexOf(st0, pos)-pos);
		deaths = tmp.toInt();
	}
	
	st = "Убито монстров</span> <span class=\\\"field_content\\\">";
	st0 = "</span> </div>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length())
		kills = data.mid(pos, data.indexOf(st0, pos)-pos);
	
	st = "Золотых</label> <div class=\\\"field_content\\\">";
	st0 = "</div> </div>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length())
		money = data.mid(pos, data.indexOf(st0, pos)-pos);

	st = "Задание</label> <div class=\\\"field_content\\\">";//<div class=\"new_line\"> <div class=\"pr_bg\" style=\"width:100 background-color:pink;\"> <div id=\"pr4\" class=\"pr_bar\" style=\"width:63%; margin-bottom: -12px;\"></div> </div>
	st0 = "</div> <div";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length()){
		tmp = data.mid(pos+6, data.indexOf(st0, pos)-pos-6);
		quest = tmp.toInt();
	}
	
	st = "<div class=\\\"field_content\\\"><i>";
	st0 = "</i></div> </div>";
	pos = data.indexOf(st, pos)+st.length();
	if (pos > st.length())
	questName = data.mid(pos, data.indexOf(st0, pos)-pos);
	
	st = "<div id=\\\"pr4\\\" class=\\\"pr_bar\\\" style=\\\"width:";
	st0 = "%;";
	pos = data.indexOf(st, pos)+st.length();
	if (pos > st.length()){
		tmp = data.mid(pos, data.indexOf(st0, pos)-pos);
		questPercent = 100 - tmp.toInt();
	}
	
	st = "Здоровье</label> <div class=\\\"field_content\\\">";
	st0 = "</div> </div>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length()){
		tmp = data.mid(pos, data.indexOf(st0, pos)-pos); //23 / 124
		health = tmp.left(tmp.indexOf(" / ")).toInt();
		pos = tmp.indexOf(" / ")+3;
		healthAll = tmp.mid(pos, tmp.length()-pos).toInt();
	}
	
	st = "Инвентарь</label> <div class=\\\"field_content\\\">";
	st0 = "</div> </div>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length()){
		tmp = data.mid(pos, data.indexOf(st0, pos)-pos); //5 / 10
		pos = tmp.indexOf(" / ")+3;
		goods =  tmp.mid(pos, tmp.length()-pos).toInt();
	}
	
	st = "Уровень</label> <div class=\\\"field_content\\\">";
	st0 = "</div> </div>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length()){
		tmp = data.mid(pos, data.indexOf(st0, pos)-pos);
		level = tmp.toInt();
	
		st = "<div id=\\\"pr3\\\" class=\\\"pr_bar\\\" style=\\\"width:";
		st0 = "%;";
		pos = data.indexOf(st, pos)+st.length();
		if (pos > st.length()){
			tmp = data.mid(pos, data.indexOf(st0, pos)-pos);
			expa = 100 - int(tmp.toFloat());
		}
	}
	
	
	
	
//вещи
	st = "В карманах у героя можно найти:</span> <UL> <li> ";
	st0 = " </li> <li> ";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length()){
		int end = data.indexOf(" </li> </UL>", pos);
		items.clear();
		while (pos < end){
			int newpos = data.indexOf(" <span id=", pos);
			int newpos1 = data.indexOf(st0, pos);
			int margin = data.indexOf("</span>", newpos)-newpos+QString("</span>").length();
			
			if ((newpos < 0)&&(newpos1 < 0)){
				margin = 0;
				newpos = end;
			}else
			if (newpos1 > 0){
				if (newpos > 0){
					if (newpos1 < newpos){
						newpos = newpos1;
						margin = 0;
					}
				} else {
					newpos = newpos1;
					margin = 0;
				}
			}
			if (newpos > end) newpos = end;
			
			items.append(data.mid(pos, newpos-pos));
			pos = newpos+st0.length()+margin;
		}
	}
	
//обмундирование
	st = "<div class=\\\"equip_content\\\">";
	st0 = "</div>";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length()){
		equipment.clear();
		while (pos > st.length()){
			equipment.append(data.mid(pos, data.indexOf(st0, pos)-pos));
			pos = data.indexOf(st, pos)+st.length();
		}
	}
	
//дневник
	pos = data.indexOf("Дневник героя");
	if (pos >= 0){
		st = "<div class=\\\"d_capt\\\">";
		st0= "</div>";
		QString st1 = "text_content\\\">";
		pos = data.indexOf(st, pos)+st.length();
		if (pos > st.length()){
			tmpdiary.clear();
			while (pos > st.length()){
				SDiaryNote dn;
				dn.time = data.mid(pos, data.indexOf(st0, pos)-pos);
				pos = data.indexOf(st1, pos)+st1.length();
				dn.name = data.mid(pos, data.indexOf(st0, pos)-pos);
				int pos1 = dn.name.indexOf("<span");
				if (pos1 >= 0)
					dn.name = dn.name.left(pos1);
				dn.details.clear();
				tmpdiary.append(dn);
				pos = data.indexOf(st, pos)+st.length();
			}
			//qDebug() << "new diary data parsed";
		}
	}
	
//вести с полей
	st = "Вести с полей</legend> <div class=\\\"new_line\\\">";
	st0 = "</div>";
	pos = data.indexOf(st)+st.length();
	lastNote = "";
	if (pos > st.length())
		lastNote = data.mid(pos, data.indexOf(st0, pos)-pos);
	
//прана
	st = "Прана</label> <div class=\\\"field_content\\\">";
	st0 = "%";
	pos = data.indexOf(st)+st.length();
	if (pos > st.length()){
		tmp = data.mid(pos, data.indexOf(st0, pos)-pos);
		prane = tmp.toInt();
	}
	
	//qDebug() << "updating diary";
	updateDiary();
}
//=====================================================================================
void Hero::updateDiary()
{
	if (tmpdiary.count() > 0){
		SDiaryNote dn = tmpdiary.at(tmpdiary.count()-1);
		dn.details.append(lastNote);
		tmpdiary.replace(tmpdiary.count()-1, dn);
	} else {
		if ((lastNote != "")&&(diary.count() > 0)){
			SDiaryNote dn = diary.at(diary.count()-1);
			dn.details.append(lastNote);
			diary.replace(diary.count()-1, dn);
		}
	}
	
	if (diary.count() <= 0)
		for (int i = 0; i < tmpdiary.count(); i++){
			SDiaryNote dn = tmpdiary.at(i);
			diary.append(dn);
		}
	else if (tmpdiary.count() > 0){
		SDiaryNote dn = tmpdiary.at(tmpdiary.count()-1);
		if (diary.at(diary.count()-1).name == dn.name){
			SDiaryNote dn = diary.at(diary.count()-1);
			bool append = true;
			if (dn.details.count() > 0)
				if ((dn.details.at(dn.details.count()-1) == lastNote)&&(dn.details.count() > 1)){
					lastNote = "";
					append = false;
				}
			if (append) dn.details.append(lastNote);
			diary.replace(diary.count()-1, dn);
		} else diary.append(dn);
	}
	//qDebug() << "Diary updated";
	/*
	QString str;
	for (int i = 0; i < diary.count(); i++){
		SDiaryNote dn = diary.at(i);
		str += dn.time + " " + dn.name + "\n";
		for (int j = 0; j < dn.details.count(); j++)
			str += "       " + dn.details.at(j) + "\n";
	}
	alert(str);*/
}
//=====================================================================================
void Hero::alert(QString str)
{
	QMessageBox msgBox;
	msgBox.setWindowTitle(tr("Алёёёёё!!! Мож поломалося чё?!1111"));
	msgBox.setText(tr(str.toAscii()));
	msgBox.exec();
}
//=====================================================================================
void Hero::read(QNetworkReply* r)
{
	//login
	if (r->request().url() == loginReq.url()){
		QString god_session = r->rawHeader("Set-Cookie");
		QByteArray bytes = r->readAll();
		QString str = QString(bytes);
		if (str.indexOf("redirected") < 0){
			logedin = false;
			emit done("login");
			return;
		}
		if (god_session != ""){
			int pos = god_session.indexOf("god_session_id=")+QString("god_session_id=").length();
			if (pos < 0){
				logedin = false;
				//qDebug() << "Login failed";
				emit done("login");
				return;
			}
			god_session = god_session.mid(pos,  god_session.indexOf(";", pos)-pos);
			
			QNetworkCookieJar * jar = net->cookieJar();
			QList<QNetworkCookie> coo;
			coo << QNetworkCookie("god_session_id", god_session.toAscii());
			jar->setCookiesFromUrl(coo, QUrl("http://www.godville.net/"));
			
			logedin = true;
			//qDebug() << "Login ok. Session: " << god_session;
			emit done("login");
			updateHero();
			updateStats();
		}
		else {
			logedin = false;
			//qDebug() << "Login failed";
			emit done("login");
		}
	}
	
	//stats
	if (r->request().url() == statsReq.url()){
		QByteArray bytes = r->readAll();
		QString str = convertString(bytes);
		parseStats(str);
		//qDebug() << "stats parsed";
		emit done("stats");
	}
	
	//hero
	if (r->request().url() == heroReq.url()){
		QByteArray bytes = r->readAll();
		QString str = convertString(bytes);
		parseHero(str);
		//qDebug() << "hero parsed";
		emit done("hero");
	}
	
	//encourage
	if (r->request().url() == encourageReq.url()){
		updateStats();
		emit done("encourage");
	}
	
	//punish
	if (r->request().url() == punishReq.url()){
		updateStats();
		emit done("punish");
	}
	
	//phrase
	if (r->request().url() == sayReq.url()){
		updateStats();
		emit done("phrase");
	}
}
//=====================================================================================
void Hero::doGood()
{
	if (logedin) net->get(encourageReq);
}
//=====================================================================================
void Hero::doBad()
{
	if (logedin) net->get(punishReq);
}
//=====================================================================================
void Hero::say(QString phrase)
{
        QString data = "god_phrase="+tr(phrase.toLocal8Bit());
        net->post(sayReq, data.toLocal8Bit());
        //может теперь будет говорить по русски?
}
//=====================================================================================
QString Hero::convertString(QByteArray bytes)
{
	QString str = QString(bytes);
	str.replace("\\u00ab", "«");
	str.replace("\\u00bb", "»");
	while (str.indexOf("\\u0") >= 0){
		int pos = str.indexOf("\\u0");
		QString tmp = str.mid(pos+2,4);
		bytes = QByteArray::fromHex(tmp.toAscii());
		
		for (int i=0;i<bytes.count()-1; i+=2){
			int b1 = bytes[i];
			int b2 = bytes[i+1];
			if (b1 != 0){
				bytes[i] = (((b1 & 0x0F) << 2)|((b2 & 0xC0) >> 6))|0xC0;
				bytes[i+1] = (b2 & 0x3F)|0x80;
			} else {
				bytes.remove(i,1);
				i--;
			}
		}
		
		str.replace("\\u"+tmp, QString(bytes));
	}
	
	str.replace("&quot;", "\"");
	str.replace("\\n", "");
	str.replace("\\t", "");
	str.replace("\\r", "");
	while (str.indexOf("  ") >= 0) str.replace("  ", " ");
	
	return str;
}
//=====================================================================================
//

