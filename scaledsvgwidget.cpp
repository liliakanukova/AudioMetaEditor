#include "scaledsvgwidget.h"

void ScaledPixmapWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPixmap sImg = this->image.scaled(this->width(), this->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QRect drawableRegion = sImg.rect();
    drawableRegion.setSize(drawableRegion.size() * this->scale);
    drawableRegion.moveCenter(this->rect().center());

    painter.drawPixmap(drawableRegion, sImg);
}
