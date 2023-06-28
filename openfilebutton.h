#ifndef OPENFILEBUTTON_H
#define OPENFILEBUTTON_H

#include <QPushButton>
#include <QSet>
#include <QFileDialog>

/**
 * @brief Класс OpenFileButton реализует кнопку, вызывающуюю
 * окно для выбора файлов пользователем.
 */
class OpenFileButton : public QPushButton {
private:
    Q_OBJECT

public:
    OpenFileButton(QWidget* parent = nullptr) : QPushButton(parent) {}

public slots:
    /**
     * @brief chooseFiles слот, который сделует подключить к
     * сингналу @see QPushButton::clicked. Этот слот отвечает
     * за вызов окна для выбора файлов и дальнейшую обработку
     * выбора пользователя. Испускает @ref filesChosen в
     * случае успешного выбора файлов.
     */
    void chooseFiles();

signals:
    /**
     * @brief filesChosen сигнал, испускаемый кнопкой,
     * когда пользователь выюрал файлы
     * @param множество имен файлов, выбранных пользователем
     */
    void filesChosen(QSet<QString>&);
};

#endif // OPENFILEBUTTON_H
