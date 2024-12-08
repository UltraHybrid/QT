#include "MainWnd.hpp"

#include "ControlWidget.hpp"
#include "QFileDialog"
#include "EllipseWidget.hpp"
#include "RectangleWidget.hpp"
#include "TriangleWidget.hpp"
#include "ui_MainWnd.h"


MainWnd::MainWnd(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWnd)
{
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

    connect(ui->ellipse_create_action, &QAction::triggered, cw, [=]
    {
        cw->setRegime(ControlWidget::Regime::CREATE);
        cw->setShapeType(ShapeType::ELLIPSE);
    });
    connect(ui->rectangle_create_action, &QAction::triggered, cw, [=]
    {
        cw->setRegime(ControlWidget::Regime::CREATE);
        cw->setShapeType(ShapeType::RECTANGLE);
    });
    connect(ui->triangle_create_atcion, &QAction::triggered, cw, [=]
    {
        cw->setRegime(ControlWidget::Regime::CREATE);
        cw->setShapeType(ShapeType::TRIANGLE);
    });
    connect(ui->save_action, &QAction::triggered, cw, [=]
    {
       save();
    });

    connect(ui->load_action, &QAction::triggered, cw,
    [=]
    {
        load();
    });
}

MainWnd::~MainWnd() {
    delete ui;
}

void MainWnd::save()
{
    QString filters("Custom files (*.cum);;All files (*.*)");
    QString defaultFilter("Custom files (*.cum)");
    auto path = QFileDialog::getSaveFileName(0, "Save file", QDir::currentPath(), filters, &defaultFilter);
    if (path.isEmpty()) return;
    auto file = QFile{path};
    file.open(QIODeviceBase::WriteOnly);
    QDataStream out(&file);
    cw->saveTo(out);
}

void MainWnd::load()
{
    QString filters("Custom files (*.cum);;All files (*.*)");
    QString defaultFilter("Custom files (*.cum)");
    auto path = QFileDialog::getOpenFileName(0, "Open file", QDir::currentPath(), filters, &defaultFilter);
    if (path.isEmpty()) return;
    auto file = QFile{path};
    file.open(QIODeviceBase::ReadOnly);
    QDataStream out(&file);
    cw->loadFrom(out);
}

