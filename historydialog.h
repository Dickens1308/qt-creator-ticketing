#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>

namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(QWidget *parent = nullptr);
    ~HistoryDialog();

private slots:
    void loadHistory();
    void onPrintClicked();
    void onCloseClicked();

private:
    Ui::HistoryDialog *ui;
    void setupTable();
};

#endif // HISTORYDIALOG_H
