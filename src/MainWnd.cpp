#include "MainWnd.hpp"

#include "ControlWidget.hpp"
#include "EllipseWidget.hpp"
#include "RectangleWidget.hpp"
#include "TriangleWidget.hpp"
#include "ui_MainWnd.h"


MainWnd::MainWnd(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWnd) {
    ui->setupUi(this);

    cw = new ControlWidget{ui->frame};
    auto horizontalLayout = new QHBoxLayout(ui->frame);
    QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(cw->sizePolicy().hasHeightForWidth());
    cw->setSizePolicy(sizePolicy);
    horizontalLayout->addWidget(cw);

    cw->setMouseTracking(true);
    ui->frame->setMouseTracking(true);
    ui->frame->setFocusPolicy(Qt::ClickFocus);
    cw->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    cw->show();

    connect(ui->delete_action, &QAction::triggered, cw,
        [=] { cw->setRegime(ControlWidget::Regime::DELETE); });
    connect(ui->move_action, &QAction::triggered, cw,
       [=] { cw->setRegime(ControlWidget::Regime::MOVE); });
    connect(ui->relation_create_action, &QAction::triggered, cw,
    [=] { cw->setRegime(ControlWidget::Regime::RELATION); });

    connect(ui->ellipse_create_action, &QAction::triggered, cw,
    [=]
    {
        cw->setRegime(ControlWidget::Regime::CREATE);
        cw->setShapeCreator([]{ return new EllipseWidget;});
    });
    connect(ui->rectangle_create_action, &QAction::triggered, cw,
    [=]
    {
        cw->setRegime(ControlWidget::Regime::CREATE);
        cw->setShapeCreator([]{ return new RectangleWidget;});
    });
    connect(ui->triangle_create_atcion, &QAction::triggered, cw,
    [=]
    {
        cw->setRegime(ControlWidget::Regime::CREATE);
        cw->setShapeCreator([]{ return new TriangleWidget;});
    });
}

MainWnd::~MainWnd() {
    delete ui;
}

