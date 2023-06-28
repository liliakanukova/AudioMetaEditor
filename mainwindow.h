#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QDebug>
#include "scaledsvgwidget.h"
#include "audiofiledropreceiver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Класс MainWindow 0 главное окно приложения
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief MainWindow создает окно и произвоит настройку
     * графического интефейса
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
