#include "historydialog.h"
#include "ui_historydialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QSqlError>

HistoryDialog::HistoryDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);
    setupTable();
    loadHistory();

    connect(ui->refreshButton, &QPushButton::clicked,
            this, &HistoryDialog::onRefreshClicked);
    connect(ui->printButton, &QPushButton::clicked,
            this, &HistoryDialog::onPrintClicked);
    connect(ui->closeButton, &QPushButton::clicked,
            this, &HistoryDialog::onCloseClicked);
    connect(ui->deleteAllButton, &QPushButton::clicked,
            this, &HistoryDialog::onDeleteAllClicked);
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

void HistoryDialog::setupTable()
{
    ui->historyTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
}

void HistoryDialog::loadHistory()
{
    ui->historyTable->setRowCount(0);
    
    QSqlQuery query;
    query.prepare("SELECT passenger_name, source, destination, date, seat_no, "
                 "distance, fare, discount, total_fare FROM bookings "
                 "ORDER BY date DESC");
    
    if (query.exec()) {
        while (query.next()) {
            int row = ui->historyTable->rowCount();
            ui->historyTable->insertRow(row);
            
            // Add data to row
            ui->historyTable->setItem(row, 0, 
                new QTableWidgetItem(query.value("passenger_name").toString()));
            ui->historyTable->setItem(row, 1, 
                new QTableWidgetItem(query.value("source").toString()));
            ui->historyTable->setItem(row, 2, 
                new QTableWidgetItem(query.value("destination").toString()));
            ui->historyTable->setItem(row, 3, 
                new QTableWidgetItem(query.value("date").toString()));
            ui->historyTable->setItem(row, 4, 
                new QTableWidgetItem(query.value("seat_no").toString()));
            ui->historyTable->setItem(row, 5, 
                new QTableWidgetItem(query.value("distance").toString() + " km"));
            ui->historyTable->setItem(row, 6,
                new QTableWidgetItem("Tsh " + query.value("fare").toString()));
            ui->historyTable->setItem(row, 7,
                new QTableWidgetItem(query.value("discount").toString()));
            ui->historyTable->setItem(row, 8,
                new QTableWidgetItem("Tsh " + query.value("total_fare").toString()));
        }
    } else {
        QMessageBox::critical(this, "Error", 
            "Failed to load booking history: " + query.lastError().text());
    }
}

void HistoryDialog::onRefreshClicked()
{
    loadHistory();
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

void HistoryDialog::onDeleteAllClicked()
{
    auto reply = QMessageBox::question(this, "Confirm Delete",
        "Are you sure you want to delete all booking history?",
        QMessageBox::Yes | QMessageBox::No);
        
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        if (query.exec("DELETE FROM bookings")) {
            QMessageBox::information(this, "Success", 
                "All booking history has been deleted");
            loadHistory();
        } else {
            QMessageBox::critical(this, "Error",
                "Failed to delete history: " + query.lastError().text()
            );
        }
    }
}
