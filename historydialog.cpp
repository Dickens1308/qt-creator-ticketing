#include "historydialog.h"
#include "ui_historydialog.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>

HistoryDialog::HistoryDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);

    loadHistory();

    connect(ui->refreshButton, &QPushButton::clicked,
            this, &HistoryDialog::loadHistory);
    connect(ui->printButton, &QPushButton::clicked,
            this, &HistoryDialog::onPrintClicked);
    connect(ui->closeButton, &QPushButton::clicked,
            this, &HistoryDialog::onCloseClicked);
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}


void HistoryDialog::setupTable()
{
    ui->historyTable->setColumnCount(4);
    ui->historyTable->setHorizontalHeaderLabels(
        {"Source", "Destination", "Date", "Seat"});
    ui->historyTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
}

void HistoryDialog::loadHistory()
{
    ui->historyTable->setRowCount(0);
    
    QSqlQuery query;
    query.prepare("SELECT source, destination, date, seat_no FROM bookings");
    
    if (query.exec()) {
        while (query.next()) {
            int row = ui->historyTable->rowCount();
            ui->historyTable->insertRow(row);
            
            for(int i = 0; i < 4; i++) {
                ui->historyTable->setItem(row, i,
                    new QTableWidgetItem(query.value(i).toString()));
            }
        }
    }
}

void HistoryDialog::onPrintClicked()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        ui->historyTable->render(&painter);
    }
}

void HistoryDialog::onCloseClicked()
{
    accept();
}