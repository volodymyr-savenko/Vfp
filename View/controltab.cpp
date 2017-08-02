#include "controltab.h"
#include "ui_controltab.h"
#include "utils.h"

namespace Ps {
    ControlTab::ControlTab(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ControlTab)
    {
        ui->setupUi(this);
    }

    ControlTab::~ControlTab()
    {
        Utils::DestructorMsg(this);
        delete ui;
    }

    void ControlTab::EnablePanel(bool isEnabled)
    {
        ui->grbxEnable->setEnabled(isEnabled);
        ui->grbxModulation->setEnabled(isEnabled);
        ui->grbxPulseSettings->setEnabled(isEnabled);
    }
    void ControlTab::on_spinPulseWidht_valueChanged(int value)
    {
        emit NotifyPulseWidthChanged(value);
    }

}


