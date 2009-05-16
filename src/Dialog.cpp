#include "Dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent){
    setupUi(this);
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(saveAll()));
    loadSettings();
}

void Dialog::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

void Dialog::loadSettings()
{
    QSettings settings("godville.net", "godvilleQT");
    soundCheckBox->setCheckState((settings.value("Sound",0).toInt()==0)?(Qt::Unchecked):(Qt::Checked));
    critHealth->setValue(settings.value("CritHealthValue",20).toInt());
    critHealthFileName->setText(settings.value("CritHealth",QString()).toString());
    popUpOp->setValue(settings.value("popUpOp",100).toInt());
    statWinOp->setValue(settings.value("statWinOp",100).toInt());
}

void Dialog::saveAll()
{
    QSettings settings("godville.net", "godvilleQT");
    settings.setValue("Sound",(soundCheckBox->checkState()==Qt::Unchecked)?(0):(2));
    settings.setValue("CritHealthValue",critHealth->value());
    settings.setValue("CritHealth",critHealthFileName->text());
    settings.setValue("statWinOp",statWinOp->value());
    settings.setValue("popUpOp",popUpOp->value());
    this->close();
}
