#ifndef DIALOG_H
#define DIALOG_H

#include <QSettings>
#include "ui_Dialog.h"

class Dialog : public QDialog, private Ui::Dialog {
    Q_OBJECT
    //Q_DISABLE_COPY(Dialog)
public:
    explicit Dialog(QWidget *parent = 0);
private slots:
    void saveAll();
    void loadSettings();
};

#endif // DIALOG_H
