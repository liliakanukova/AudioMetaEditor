#include "audiofiledropreceiver.h"

AudiofileDropReceiver::AudiofileDropReceiver(QWidget* parent) : ScaledPixmapWidget(parent), activated(false) {
    this->setAcceptDrops(true);
}

AudiofileDropReceiver::AudiofileDropReceiver(const QString& baseIconPath, const QString& activatedIconPath, double targetScale, QWidget* parent) :
    ScaledPixmapWidget(parent, targetScale), activated(false) {
    this->setAcceptDrops(true);
    this->baseIconPath = baseIconPath;
    this->activatedIconPath = activatedIconPath;
    this->load(baseIconPath);
}

void AudiofileDropReceiver::setIcons(const QString& baseIconPath, const QString& activatedIconPath) {
    this->baseIconPath = baseIconPath;
    this->activatedIconPath = activatedIconPath;
}

void AudiofileDropReceiver::setActivated(bool activated) {
    if (activated && this->activatedIconPath.size() != 0) this->load(this->activatedIconPath);
    else if(!activated && this->baseIconPath.size() != 0) this->load(this->baseIconPath);
}

void AudiofileDropReceiver::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
        this->setActivated(true);
    }
}

void AudiofileDropReceiver::dragLeaveEvent(QDragLeaveEvent*) {
    this->setActivated(false);
}

void AudiofileDropReceiver::dropEvent(QDropEvent* event) {
    event->acceptProposedAction();
    QSet<QString> files;
    for (const auto& url : event->mimeData()->urls()) files.insert(url.toLocalFile());
    emit filesDropped(files);

    this->setActivated(false);
}





