#include "filelistwidget.h"


void FileListWidget::filesProvided(QSet<QString>& fileNames) {
    this->fileNames.clear();
    QMimeDatabase db;

    for (const auto& name : fileNames) {
        QMimeType mimeType = db.mimeTypeForFile(name);
        if (!(mimeType.isValid() && mimeType.name().startsWith("audio"))) {
            QMessageBox* box = new QMessageBox(
                        QMessageBox::Icon::Critical,
                        "Ошибка",
                        "Поддерживаются только аудиофайлы",
                        QMessageBox::StandardButton::Ok,
                        this
            ); box->open();
            fileNames.remove(name);
        }
    }

    if (!fileNames.empty()) emit updateContent(fileNames);
}

void FileListWidget::newFileLoaded(const QString name) {
    this->fileNames.insert(name);
    this->addItem(name);
}

void FileListWidget::selectedFilesRemoved() {
    if (this->item(0)->isSelected()) {
        this->selectAll();
        this->item(0)->setSelected(false);
    }

    if (this->selectedItems().empty()) return;
    for (const auto& it : this->selectedItems()) {
        this->fileNames.remove(it->text());
    }

    this->selectAll();
    this->item(0)->setSelected(false);
    qDeleteAll(this->selectedItems());

    if(!this->fileNames.empty()) emit updateContent(this->fileNames);
    else emit contentEmpty();
}

void FileListWidget::selectedFilesSaved() {
    if (this->item(0)->isSelected()) {
        this->selectAll();
        this->item(0)->setSelected(false);
    }
    if (this->selectedItems().empty()) return;

    QSet<QString> toSave;
    for (const auto* it : this->selectedItems()) {
        toSave.insert(it->text());
    }

    emit saveContent(toSave);
}
