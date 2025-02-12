#include "welcomescreendialog.h"
#include "ui_welcomescreendialog.h"
#include "bookingdialog.h"
#include "historydialog.h"

WelcomeScreenDialog::WelcomeScreenDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::WelcomeScreenDialog)
{
    ui->setupUi(this);

    connect(ui->purchaseButton, &QPushButton::clicked,
            this, &WelcomeScreenDialog::onPurchaseClicked);
    connect(ui->historyButton, &QPushButton::clicked,
            this, &WelcomeScreenDialog::onHistoryClicked);
}

WelcomeScreenDialog::~WelcomeScreenDialog()
{
    delete ui;
}

void WelcomeScreenDialog::onPurchaseClicked()
{
    BookingDialog bookingDialog(this);
    bookingDialog.exec();
}

void WelcomeScreenDialog::onHistoryClicked()
{
    HistoryDialog historyDialog(this);
    historyDialog.exec();
}