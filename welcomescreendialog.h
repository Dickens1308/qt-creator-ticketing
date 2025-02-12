#ifndef WELCOMESCREENDIALOG_H
#define WELCOMESCREENDIALOG_H

#include <QDialog>

namespace Ui {
class WelcomeScreenDialog;
}

class WelcomeScreenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeScreenDialog(QWidget *parent = nullptr);
    ~WelcomeScreenDialog();

private slots:
    void onPurchaseClicked();
    void onHistoryClicked();    

private:
    Ui::WelcomeScreenDialog *ui;
    void showBookingHistory();

};

#endif // WELCOMESCREENDIALOG_H
