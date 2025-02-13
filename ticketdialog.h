#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>

namespace Ui { class TicketDialog; }

class TicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TicketDialog(
        const QString &source,
        const QString &destination,
        const QString &date,
        int seatNo,
        int distance,
        double fare,
        double discount,
        double totalFare,
        QWidget *parent = nullptr);
    ~TicketDialog();

private slots:
    void onPrintClicked();
    void onSaveClicked();

private:
    Ui::TicketDialog *ui;
};

#endif