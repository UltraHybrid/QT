//
// Created by Ultra on 03.12.2024.
//

#ifndef MAINWND_HPP
#define MAINWND_HPP

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


#endif //MAINWND_HPP
