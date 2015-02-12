#pragma once

#include "utils/commondefines.hpp"

IGNORE_WARNINGS_BEGIN
#include "ui_mainwindow.h"
IGNORE_WARNINGS_END

class OpenGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    OpenGLWidget &getOpenGlWidget() const
    {
        return *ui.openGLWidget;
    }

signals:
    void closed();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_actionWireframe_mode_toggled(bool arg1);

    void on_actionClose_triggered();

private:
    Ui::MainWindow ui;
};
