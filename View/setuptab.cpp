#include <QStringListModel>
#include <QDebug>

#include "setuptab.h"
#include "ui_setuptab.h"
#include "utils.h"


namespace Ps {
    SetupTab::SetupTab(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SetupTab)
    {
        ui->setupUi(this);
    }

    SetupTab::~SetupTab()
    {
        Utils::DestructorMsg(this);
        delete ui;
    }

    void SetupTab::SetHostName(const QString& value)
    {
        ui->editIpAddress->setText(value);
        emit NotifyHostNameChanged(value);
    }

    void SetupTab::SetPort(quint16 value)
    {
        ui->editPort->setText(QString::number(value));
        emit NotifyPortChanged(value);
    }

    void SetupTab::SetCommands(QStringListModel& commands)
    {
        ui->cmbCommands->setModel(&commands);
    }

    void SetupTab::onStatusUpdated(const QString &statusMsg)
    {
        ui->editInstMsgs->append(statusMsg);
    }

    void SetupTab::onConnected()
    {
        auto connect_msg = QString(tr("Connected."));
        ui->editInstMsgs->append(connect_msg);
    }

    void SetupTab::onDisconnected()
    {
        auto connect_msg = QString(tr("Disconnected."));
        ui->editInstMsgs->append(connect_msg);
    }

    void SetupTab::onDataSent(const QString &dataSent)
    {
        ui->editInstMsgs->append("Data sent: " + dataSent);
    }

    void SetupTab::onDataReceived(const QString &dataRead)
    {
        ui->editInstMsgs->append(dataRead);
    }

    void SetupTab::onConnectEnabled(bool isEnabled)
    {
        ui->btnConnect->setEnabled(isEnabled);
    }

    void SetupTab::onDisconnectEnabled(bool isEnabled)
    {
        ui->btnDisconnect->setEnabled(isEnabled);
    }

    void SetupTab::onDirectCommandsEnabled(bool isEnabled)
    {
        ui->gbDirectCommands->setEnabled(isEnabled);
    }

    void SetupTab::onControlTabEnabled(bool isEnabled)
    {
        //TODO
    }

    void SetupTab::on_editIpAddress_editingFinished()
    {
        emit NotifyHostNameChanged(ui->editIpAddress->text());
    }

    void SetupTab::on_editPort_editingFinished()
    {
        bool ok;
        int result = ui->editPort->text().toInt(&ok);
        if (!ok || (result > USHRT_MAX))
        {
            ui->editInstMsgs->append(tr("Invalid Port Number" + result));
        }
        else
        {
            emit NotifyPortChanged(result);
        }
    }

    void SetupTab::on_btnConnect_clicked()
    {
        emit NotifyConnectClicked();
    }

    void SetupTab::on_btnDisconnect_clicked()
    {
        emit NotifyDisconnectClicked();
    }

    void SetupTab::on_btnSend_clicked()
    {
        emit NotifySendClicked(ui->cmbCommands->currentText());
    }

    void SetupTab::on_btnReceive_clicked()
    {
        emit NotifyReceiveClicked();
    }

    void SetupTab::on_btnClear_clicked()
    {
        ui->editInstMsgs->clear();
    }
}


