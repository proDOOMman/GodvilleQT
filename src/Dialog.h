#ifndef DIALOG_H
#define DIALOG_H

#include <QSettings>
#include <QCloseEvent>
#include "ui_Dialog.h"

class Dialog : public QDialog, private Ui::Dialog
{
    Q_OBJECT
    Q_DISABLE_COPY(Dialog)
public:
    Dialog(QWidget *parent = 0);
private slots:
    void saveAll();
    void loadSettings();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // DIALOG_H
