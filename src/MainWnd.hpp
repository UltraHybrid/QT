#pragma once

#include <qgraphicsscene.h>
#include <QMainWindow>


class PaintPanel;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWnd; }
QT_END_NAMESPACE

class MainWnd : public QMainWindow {
Q_OBJECT

public:
    explicit MainWnd(QWidget *parent = nullptr);
    ~MainWnd() override;
private:
    PaintPanel* cw;
    Ui::MainWnd *ui;

    void save();
    void load();

    void unsetActions() const;
};
