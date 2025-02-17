#include "ticketdialog.h"
#include "ui_ticketdialog.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>

TicketDialog::TicketDialog(
    const QString &source,
    const QString &destination,
    const QString &date,
    int seatNo,
    int distance,
    double fare,
    double discount,
    double totalFare,
    QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TicketDialog)
{
    ui->setupUi(this);
    
    // Set ticket details
    ui->sourceValue->setText(source);
    ui->destValue->setText(destination);
    ui->dateValue->setText(date);
    ui->seatValue->setText(QString::number(seatNo));
    ui->distanceValue->setText(QString::number(distance) + " km");
    ui->fareValue->setText("Tsh " + QString::number(fare, 'f', 2));
    ui->discountValue->setText(QString::number(discount, 'f', 2) + " %");
    ui->totalFareValue->setText("Tsh " + QString::number(totalFare, 'f', 2));
    
    // Connect buttons
    connect(ui->printButton, &QPushButton::clicked,
            this, &TicketDialog::onPrintClicked);
    connect(ui->saveButton, &QPushButton::clicked,
            this, &TicketDialog::onSaveClicked);
}

TicketDialog::~TicketDialog()
{
    delete ui;
}

void TicketDialog::onPrintClicked()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        ui->ticketGroup->render(&painter);
    }
}

void TicketDialog::onSaveClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        "Save Ticket", "", "PDF Files (*.pdf);;All Files (*)");
        
    if (fileName.isEmpty())
        return;
        
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    
    QPainter painter(&printer);
    ui->ticketGroup->render(&painter);
    
    QMessageBox::information(this, "Success", 
                           "Ticket saved successfully!");
}
