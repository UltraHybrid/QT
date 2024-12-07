#pragma once

#include <qgraphicsscene.h>
#include <QMainWindow>


class ControlWidget;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWnd; }
QT_END_NAMESPACE

class MainWnd : public QMainWindow {
Q_OBJECT

public:
    explicit MainWnd(QWidget *parent = nullptr);
    ~MainWnd() override;
private:
    ControlWidget* cw;
    Ui::MainWnd *ui;
};
