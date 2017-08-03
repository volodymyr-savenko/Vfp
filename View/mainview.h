#ifndef MAINVIEW_H
#define MAINVIEW_H
#include "setuptab.h"
#include "controltab.h"
#include <QMainWindow>


namespace Ui {
class MainView;
}

namespace Ps {
    class MainView : public QMainWindow
    {
        Q_OBJECT

    public:
        MainView(QWidget* parent, SetupTab* p_setupTab, ControlTab* p_controlTab);
        ~MainView();

    private slots:
        void on_action_Exit_triggered();

        void on_action_About_triggered();

    private:
        Ui::MainView *ui;
    };

    }

#endif // MAINVIEW_H
