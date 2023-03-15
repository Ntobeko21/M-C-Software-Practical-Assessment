#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BCanMsgsDb.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnProcess_clicked();

    void on_btnClose_clicked();

    void on_btnClear_clicked();

    void on_actionOpenDatabase_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    BCanMsgsDb *canDb;
    QString dbFilename;
};
#endif // MAINWINDOW_H
