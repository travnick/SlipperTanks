#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent_) :
    QMainWindow(parent_)
{
    ui.setupUi(this);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui.retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event_)
{
    QMainWindow::closeEvent(event_);
    emit closed();
}

void MainWindow::on_actionWireframe_mode_toggled(bool wireframe)
{
    ui.openGLWidget->toggleWireFrameMode(wireframe);
}

void MainWindow::on_actionClose_triggered()
{
    close();
}
