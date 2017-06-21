#include "mainview.h"
#include "ui_mainview.h"
#include "utils.h"

namespace Ps{

MainView::MainView(QWidget *parent, SetupTab* p_setupTab) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    //auto setup_tab = new SetupTab(this);
    ui->loSetupTab->addWidget(p_setupTab);
}

MainView::~MainView()
{
    Utils::DestructorMsg(this);
    delete ui;
}
}
