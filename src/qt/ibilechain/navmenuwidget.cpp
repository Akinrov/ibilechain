// Copyright (c) 2019-2020 The PIVX developers
// Copyright (c) 2021-2022 The Ibilechain Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "qt/ibilechain/navmenuwidget.h"
#include "qt/ibilechain/forms/ui_navmenuwidget.h"
#include "qt/ibilechain/ibilechaingui.h"
#include "qt/ibilechain/qtutils.h"
#include "clientversion.h"
#include "optionsmodel.h"
#include <QScrollBar>

NavMenuWidget::NavMenuWidget(PIVXGUI *mainWindow, QWidget *parent) :
    PWidget(mainWindow, parent),
    ui(new Ui::NavMenuWidget)
{
    ui->setupUi(this);
    this->setFixedWidth(100);
    setCssProperty(ui->navContainer_2, "container-nav");
    setCssProperty(ui->imgLogo, "img-nav-logo");

    // App version
    ui->labelVersion->setText(QString(tr("v%1")).arg(QString::fromStdString(FormatVersionFriendly())));
    ui->labelVersion->setProperty("cssClass", "text-title-white");

    // Buttons
    ui->btnDashboard->setProperty("name", "dash");
    ui->btnDashboard->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->btnSend->setProperty("name", "send");
    ui->btnSend->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->btnReceive->setProperty("name", "receive");
    ui->btnReceive->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->btnAddress->setProperty("name", "address");
    ui->btnAddress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->btnMaster->setProperty("name", "master");
    ui->btnMaster->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->btnSettings->setProperty("name", "settings");
    ui->btnSettings->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btns = {ui->btnDashboard, ui->btnSend, ui->btnReceive, ui->btnAddress, ui->btnMaster, ui->btnSettings};
    onNavSelected(ui->btnDashboard, true);

    ui->scrollAreaNav->setWidgetResizable(true);

    QSizePolicy scrollAreaPolicy = ui->scrollAreaNav->sizePolicy();
    scrollAreaPolicy.setVerticalStretch(1);
    ui->scrollAreaNav->setSizePolicy(scrollAreaPolicy);

    QSizePolicy scrollVertPolicy = ui->scrollAreaNavVert->sizePolicy();
    scrollVertPolicy.setVerticalStretch(1);
    ui->scrollAreaNavVert->setSizePolicy(scrollVertPolicy);

    connectActions();
}

void NavMenuWidget::loadWalletModel() {

}

/**
 * Actions
 */
void NavMenuWidget::connectActions() {
    connect(ui->btnDashboard, &QPushButton::clicked, this, &NavMenuWidget::onDashboardClicked);
    connect(ui->btnSend, &QPushButton::clicked, this, &NavMenuWidget::onSendClicked);
    connect(ui->btnAddress, &QPushButton::clicked, this, &NavMenuWidget::onAddressClicked);
    connect(ui->btnMaster, &QPushButton::clicked, this, &NavMenuWidget::onMasterNodesClicked);
    connect(ui->btnSettings, &QPushButton::clicked, this, &NavMenuWidget::onSettingsClicked);
    connect(ui->btnReceive, &QPushButton::clicked, this, &NavMenuWidget::onReceiveClicked);

    ui->btnDashboard->setShortcut(QKeySequence(SHORT_KEY + Qt::Key_1));
    ui->btnSend->setShortcut(QKeySequence(SHORT_KEY + Qt::Key_2));
    ui->btnReceive->setShortcut(QKeySequence(SHORT_KEY + Qt::Key_3));
    ui->btnAddress->setShortcut(QKeySequence(SHORT_KEY + Qt::Key_4));
    ui->btnMaster->setShortcut(QKeySequence(SHORT_KEY + Qt::Key_5));
    ui->btnSettings->setShortcut(QKeySequence(SHORT_KEY + Qt::Key_7));
}

void NavMenuWidget::onSendClicked(){
    window->goToSend();
    onNavSelected(ui->btnSend);
}

void NavMenuWidget::onDashboardClicked(){
    window->goToDashboard();
    onNavSelected(ui->btnDashboard);
}

void NavMenuWidget::onAddressClicked(){
    window->goToAddresses();
    onNavSelected(ui->btnAddress);
}

void NavMenuWidget::onMasterNodesClicked(){
    window->goToMasterNodes();
    onNavSelected(ui->btnMaster);
}

void NavMenuWidget::onSettingsClicked(){
    window->goToSettings();
    onNavSelected(ui->btnSettings);
}

void NavMenuWidget::onReceiveClicked(){
    window->goToReceive();
    onNavSelected(ui->btnReceive);
}

void NavMenuWidget::onNavSelected(QWidget* active, bool startup) {
    QString start = "btn-nav-";
    Q_FOREACH (QWidget* w, btns) {
        QString clazz = start + w->property("name").toString();
        if (w == active) {
            clazz += "-active";
        }
        setCssProperty(w, clazz);
    }
    if (!startup) updateButtonStyles();
}

void NavMenuWidget::selectSettings() {
    onSettingsClicked();
}

void NavMenuWidget::showEvent(QShowEvent *event) {
    if (!init) {
        init = true;
        ui->scrollAreaNav->verticalScrollBar()->setValue(ui->btnDashboard->y());
    }
}

void NavMenuWidget::updateButtonStyles(){
    forceUpdateStyle({
         ui->btnDashboard,
         ui->btnSend,
         ui->btnAddress,
         ui->btnMaster,
         ui->btnSettings,
         ui->btnReceive
    });
}

NavMenuWidget::~NavMenuWidget(){
    delete ui;
}
