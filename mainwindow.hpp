#pragma once

#include "ui_mainwindow.h"

class OpenGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    OpenGLWidget &getOpenGlWidget() const
    {
        return *ui.openGLWidget;
    }

signals:
    void closed();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow ui;
};
