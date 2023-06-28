#ifndef SCALEDSVGWIDGET_H
#define SCALEDSVGWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QByteArray>
#include <QPainter>
#include <QPaintEvent>

/**
 * @brief Класс ScaledPixmapWidget реализует виджетом для
 * масштабированного отображения изображений. Отношение
 * сторон изображений при изменении размера виджета сохраняется.
 */
class ScaledPixmapWidget : public QWidget {
private:
    Q_OBJECT

protected:
    /**
     * @brief scale коэффициент масштабирования изображения
     */
    double scale;
    /**
     * @brief image текущее отображаемое изображение
     */
    QPixmap image;
    void paintEvent(QPaintEvent*) override;

public:
    ScaledPixmapWidget (QWidget* parent = nullptr, double targetScale = 1.0) : QWidget(parent), scale(targetScale) {}

    /**
     * @brief load - загружает новое изображение и обновляет виджет
     * @param image путь до файла с изображением
     */
    void load(const QString& image) {
        this->image = QPixmap(image);
        this->update();
    }

    /**
     * @brief getScale получить текущий коэффициент масштабирования изображения
     * @return коэффициент масштабирования изображения
     */
    double getScale() {
        return this->scale;
    }

    /**
     * @brief setScale устанавливает новый коэффициент масштабирования изображения
     * и обновляет виджет
     * @param newScale новый коэффициент масштабирования изображения
     */
    void setScale(double newScale) {
        this->scale = newScale;
        this->update();
    }
};

#endif // SCALEDSVGWIDGET_H
