#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

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
    void onRefreshClicked();
    void onCloseClicked();
    void onDeleteAllClicked();

private:
    Ui::HistoryDialog *ui;
    void setupTable();
};

#endif