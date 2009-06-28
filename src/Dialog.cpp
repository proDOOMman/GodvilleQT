#include "Dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent){
    setupUi(this);
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(saveAll()));
    loadSettings();
#ifdef Q_OS_WIN32
    notify_knotify3->setEnabled(false);
    notify_knotify4->setEnabled(false);
    notify_libnotify->setEnabled(false);
#endif
    media = new Phonon::MediaObject(this);
//    connect(media, SIGNAL(finished()), SLOT(slotFinished()));
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::Path path = Phonon::createPath(media, audioOutput);
}

/*void Dialog::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}*/

void Dialog::loadSettings()
{
    QSettings settings("godville.net", "godvilleQT");
    soundCheckBox->setCheckState((settings.value("Sound",0).toInt()==0)?(Qt::Unchecked):(Qt::Checked));
    critHealth->setValue(settings.value("CritHealthValue",20).toInt());
    critHealthFileName->setText(settings.value("CritHealth",QString()).toString());
    popUpOp->setValue(settings.value("popUpOp",100).toInt());
    statWinOp->setValue(settings.value("statWinOp",100).toInt());
    QString notifyType = settings.value("notifyType").toString();
    if(notifyType=="standart")
        notify_standart->setChecked(true);
    else
        if(notifyType=="libnotify")
            notify_libnotify->setChecked(true);
    else
        if(notifyType=="knotify3")
            notify_knotify3->setChecked(true);
    else
        if(notifyType=="knotify4")
            notify_knotify4->setChecked(true);
}

void Dialog::saveAll()
{
    QSettings settings("godville.net", "godvilleQT");
    settings.setValue("Sound",(soundCheckBox->checkState()==Qt::Unchecked)?(0):(2));
    settings.setValue("CritHealthValue",critHealth->value());
    settings.setValue("CritHealth",critHealthFileName->text());
    settings.setValue("statWinOp",statWinOp->value());
    settings.setValue("popUpOp",popUpOp->value());
    if(notify_standart->isChecked())
        settings.setValue("notifyType","standart");
    else
        if(notify_libnotify->isChecked())
            settings.setValue("notifyType","libnotify");
    else
        if(notify_knotify3->isChecked())
            settings.setValue("notifyType","knotify3");
    else
        if(notify_knotify4->isChecked())
            settings.setValue("notifyType","knotify4");
    //this->close();
}

void Dialog::on_critHealthPlay_released()
{
    media->setCurrentSource(Phonon::MediaSource(critHealthFileName->text()));
    media->play();
}

void Dialog::on_critHealthFileChoose_released()
{
    critHealthFileName->setText(QFileDialog::getOpenFileName(this,
     tr("Выберите сигнал"), QDir::homePath(), tr("Sound Files (*.wav *.ogg *.mp3 *.flac);;All Files(*.*)")));
}
