// Copyright (c) 2019-2020 The PIVX developers
// Copyright (c) 2021-2022 The Ibilechain Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "qt/ibilechain/mnrow.h"
#include "qt/ibilechain/forms/ui_mnrow.h"
#include "qt/ibilechain/qtutils.h"

MNRow::MNRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MNRow)
{
    ui->setupUi(this);
    setCssProperty(ui->labelAddress, "text-list-body2");
    setCssProperty(ui->labelName, "text-list-title1");
    setCssProperty(ui->labelDate, "text-list-caption-medium");
    ui->lblDivisory->setStyleSheet("background-color:#bababa;");
}

void MNRow::updateView(QString address, QString label, QString status, bool wasCollateralAccepted)
{
    ui->labelName->setText(label);
    ui->labelAddress->setText(address);
    if (!wasCollateralAccepted) status = tr("Collateral tx not found");
    ui->labelDate->setText(tr("Status: %1").arg(status));
}

MNRow::~MNRow()
{
    delete ui;
}
