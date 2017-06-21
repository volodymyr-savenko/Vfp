#ifndef MAINVIEW_H
#define MAINVIEW_H
#include "setuptab.h"
#include <QMainWindow>


namespace Ui {
class MainView;
}

namespace Ps {
    class MainView : public QMainWindow
    {
        Q_OBJECT

    public:
        MainView(QWidget* parent, SetupTab* p_setupTab);
        ~MainView();

    private:
        Ui::MainView *ui;
    };

    }

#endif // MAINVIEW_H
