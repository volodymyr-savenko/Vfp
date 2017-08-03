#include "mainview.h"
#include "ui_mainview.h"
#include "View/setuptab.h"
#include "View/controltab.h"
#include "View/aboutbox.h"
#include "utils.h"

namespace Ps{

MainView::MainView(QWidget *parent, SetupTab* p_setupTab, ControlTab *p_controlTab) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    p_setupTab->setParent(this);
    p_controlTab->setParent(this);
    ui->loSetupTab->addWidget(p_setupTab);
    ui->loControlTab->addWidget(p_controlTab);
}

MainView::~MainView()
{
    Utils::DestructorMsg(this);
    delete ui;
}
}

void Ps::MainView::on_action_Exit_triggered()
{
    QApplication::quit();
}

void Ps::MainView::on_action_About_triggered()
{
     AboutBox about_box;
     about_box.show();
     about_box.exec();
}
