#ifndef CONTROLTAB_H
#define CONTROLTAB_H

#include <QWidget>



namespace Ui {
    class ControlTab;
}
namespace Ps{
    class ControlTab : public QWidget
    {
        Q_OBJECT

    public:
        explicit ControlTab(QWidget *parent = 0);
        ~ControlTab();
        void EnablePanel(bool isEnabled);

    signals:
        void NotifyPulseWidthChanged(double value);

    private slots:
        void on_spinPulseWidht_valueChanged(int value);

    private:
        Ui::ControlTab *ui;
    };
}
#endif // CONTROLTAB_H
