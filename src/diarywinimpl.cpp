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
	oldrecs = loadDiary();
	offset = 0;
	first = true;
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
void diarywinimpl::saveDiary(QString text)
{
#ifdef Q_WS_WIN
        QFile f("diary.htm");
#else
        QFile f(QDir::home().absoluteFilePath(".godville/diary.htm"));
#endif
        f.open(QIODevice::WriteOnly);
        f.write(text.toAscii());
        f.close();
}
//=====================================================================================
QString diarywinimpl::loadDiary()
{
        QString res = "";
#ifdef Q_WS_WIN
        QFile f("diary.htm");
#else
        QFile f(QDir::home().absoluteFilePath(".godville/diary.htm"));
#endif
        if(f.exists()){
                f.open(QIODevice::ReadOnly);
                res = f.readAll();
                f.close();
	}
	return res;
}
//=====================================================================================
void diarywinimpl::setDiary(QList<SDiaryNote> diary)
{
	text->setText("");
	QString str = "";
	if (first&&(oldrecs != "")&&(diary.count() > 0)){
		offset = diary.count()-1;
		first = false;
	}
	for (int i = diary.count()-1; i >= offset; i--){
		SDiaryNote dn = diary.at(i);
		str += "<div style=\"font-weight: bold; margin-left: 0px;\">"+dn.time+"</div>\n"+
			   "<div style=\"margin-left:20px;\">"+dn.name+"</div>\n";
		for (int j = 0; j < dn.details.count(); j++)
			str += "<div style=\"margin-left: 30px;\"><i>"+dn.details.at(j)+"</i></div>\n";
	}

        text->setText(tr(str.toAscii())+tr(oldrecs.toAscii()));
	saveDiary(str+oldrecs);
}
//=====================================================================================
