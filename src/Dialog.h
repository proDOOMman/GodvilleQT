#ifndef DIALOG_H
#define DIALOG_H

#include <QSettings>
#include <QCloseEvent>
#include <QDir>
#include <QFileDialog>
#include "ui_Dialog.h"
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <phonon/path.h>
#include <phonon/audiooutput.h>

class Dialog : public QDialog, private Ui::Dialog
{
    Q_OBJECT
    Q_DISABLE_COPY(Dialog)
public:
    Dialog(QWidget *parent = 0);
private slots:
    void on_critHealthFileChoose_released();
    void on_critHealthPlay_released();
    void saveAll();
    void loadSettings();
private:
    Phonon::MediaObject *media;
    Phonon::AudioOutput *audioOutput;
};

#endif // DIALOG_H
