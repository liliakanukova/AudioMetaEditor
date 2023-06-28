#ifndef AUDIOFILEDROPRECEIVER_H
#define AUDIOFILEDROPRECEIVER_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QByteArray>
#include <QSet>
#include "scaledsvgwidget.h"

/**
 * @brief Класс AudiofileDropReceiver реализует поле Drag and Drop, принимающее файлы.
 * Отображает базовую иконку, сменяя ее на "активную", на время, пока пользователь
 * держит файлы на этим виджетом
 */
class AudiofileDropReceiver : public ScaledPixmapWidget {
private:
    Q_OBJECT

protected:
    void dragEnterEvent(QDragEnterEvent*) override;
    void dragLeaveEvent(QDragLeaveEvent*) override;
    void dropEvent(QDropEvent*) override;

    /**
     * @brief activated указывает на то, держит ли сейчас пользователь файлы над этим виджетом
     */
    bool activated;

    /**
     * @brief baseIconPath путь до базовой иконки
     */
    QString baseIconPath;

    /**
     * @brief activatedIconPath путь до "активной" иконки
     */
    QString activatedIconPath;

public:
    AudiofileDropReceiver (QWidget* parent = nullptr);

    AudiofileDropReceiver (const QString& baseIconPath, const QString& activatedIconPath, double targetScale = 1.0, QWidget* parent = nullptr);

    /**
     * @brief setIcons позволяет устновить новые значения для @ref baseIconPath и @ref activatedIconPath.
     * @warning Не обновляет окно!
     * @param baseIconPath путь до новой базовой иконки
     * @param activatedIconPath путь до новой "активной" иконки
     */
    void setIcons(const QString& baseIconPath, const QString& activatedIconPath);

    /**
     * @brief setActivated позволяет переключать режимы базовый/активный
     * Вызывает обновление виджета
     * @param activated новый режим
     */
    void setActivated(bool activated);

signals:
    /**
     * @brief filesDropped сигнал, испускаемый, когда пользователь сбросил файлы на виджет
     */
    void filesDropped(QSet<QString>&);
};

#endif // AUDIOFILEDROPRECEIVER_H
