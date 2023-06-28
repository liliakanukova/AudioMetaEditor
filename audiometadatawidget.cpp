#include "audiometadatawidget.h"

AudioMetadataWidget::LoadResult AudioMetadataWidget::getFileRef(TagLib::FileRef& out, const QString& name, bool errorCheck) {
    TagLib::FileRef fileRef(name.toUtf8().data());
    if (errorCheck) {
        if (fileRef.isNull()) {
            this->showErrorMessage(AudioMetadataWidget::LoadResult::FILE_ERROR, name);
            return AudioMetadataWidget::LoadResult::FILE_ERROR;
        }

        if (!fileRef.tag()) {
            this->showErrorMessage(AudioMetadataWidget::LoadResult::NO_TAG, name);
            return AudioMetadataWidget::LoadResult::NO_TAG;
        }
    }

    out = fileRef;
    return AudioMetadataWidget::LoadResult::NO_ERR;
}

void AudioMetadataWidget::buildDefault() {
    this->clearContents();
    this->setColumnCount(2);
    this->setRowCount(3);
    this->setItem(0, 0, new QTableWidgetItem("TITLE"));
    this->setItem(1, 0, new QTableWidgetItem("ALBUM"));
    this->setItem(2, 0, new QTableWidgetItem("ARTIST"));
}

QString AudioMetadataWidget::messageFromType(AudioMetadataWidget::LoadResult type) {
    switch (type) {
        case NO_ERR: return "Операция успешна";
        case FILE_ERROR: return "Не удается открыть файл";
        case NO_TAG: return "Не удается прочитать метаданные из файла";
        case NO_FILES: return "Не обранужено ни одного файла";
        default: return "Неизвестная ошибка";
    }
}

AudioMetadataWidget::LoadResult AudioMetadataWidget::load(const QSet<QString>& files) {
    if (files.empty()) {
        this->showErrorMessage(AudioMetadataWidget::LoadResult::NO_FILES);
        return AudioMetadataWidget::LoadResult::NO_FILES;
    }

    this->setColumnCount(2);
    this->setRowCount(3);
    this->isSingleFile = (files.size() == 1);
    TagLib::FileRef firstFileRef; const auto result = this->getFileRef(firstFileRef, *files.begin());
    if (result != AudioMetadataWidget::LoadResult::NO_ERR) return result;

    emit fileLoaded(*files.begin());
    TagLib::Tag* firstFileMeta = firstFileRef.tag();

    if (this->isSingleFile) {
        int curRow = 0;
        if (firstFileMeta->isEmpty()) this->buildDefault();
        else for (const auto& it : firstFileMeta->properties()) {
            this->insertRow(curRow);
            QString key = it.first.toCString();
            QString value = join(it.second.begin(), it.second.end(), ';');
            this->setItem(curRow, 0, new QTableWidgetItem(key));
            this->setItem(curRow, 1, new QTableWidgetItem(value));
            ++curRow;
        }
    } else {
        QList<TagLib::FileRef> fileRefs; fileRefs.reserve(files.size() - 1);
        QList<QMap<QString, QString>> fileProps; fileProps.reserve(files.size() - 1);

        int i = 0;
        for (auto f = std::next(files.begin()); f != files.end(); ++f, ++i) {
            TagLib::FileRef fileRef;
            if (this->getFileRef(fileRef, *f) != AudioMetadataWidget::LoadResult::NO_ERR) continue;
            emit fileLoaded(*f);
            fileRefs.append(fileRef);
            QMap<QString, QString> prop;
            for (const auto& it : fileRefs[i].tag()->properties()) {
                prop[it.first.toCString()] = join(it.second.begin(), it.second.end(), ';');
            }
            fileProps.append(prop);
        }

        int curRow = 0;
        for (const auto& it : firstFileMeta->properties()) {
            bool isCommon = true;
            QString key = it.first.toCString();
            QString prop = join(it.second.begin(), it.second.end(), ';');
            for (auto f = fileProps.begin(); f != fileProps.end(); ++f) {
                if (!f->contains(key) || (*f)[key] != prop) {
                    isCommon = false;
                    break;
                }
            }

            if (isCommon) {
                this->setItem(curRow, 0, new QTableWidgetItem(key));
                this->setItem(curRow, 1, new QTableWidgetItem(prop));
                ++curRow;
            }
        }

#ifndef TEST_RUN
        if (curRow == 0) {
            QMessageBox* warnBox = new QMessageBox(
                    QMessageBox::Icon::Warning,
                    "Внимание",
                    "Не найдено ни однонго общего тега",
                    QMessageBox::StandardButton::Ok,
                    this
            ); warnBox->open();
        }
#endif
    }

    return AudioMetadataWidget::LoadResult::NO_ERR;
}

void AudioMetadataWidget::showErrorMessage(AudioMetadataWidget::LoadResult type, QString fileName) {
#ifndef TEST_RUN
    QMessageBox* errBox = new QMessageBox(
                QMessageBox::Icon::Critical,
                "Ошибка",
                this->messageFromType(type) + (fileName.isEmpty() ? "" : (" : " + fileName)),
                QMessageBox::StandardButton::Ok,
                this
    ); errBox->open();
#endif
}

void AudioMetadataWidget::updateMeta(const QSet<QString>& files) {
    this->clearContents();
    this->setRowCount(0);
    this->load(files);
}

void AudioMetadataWidget::saveMeta(const QSet<QString>& files) {
    bool ok = true;
    for (const auto& f : files) {
        TagLib::FileRef fileRef;
        if (this->getFileRef(fileRef, f) != AudioMetadataWidget::LoadResult::NO_ERR) continue;
        TagLib::PropertyMap props = fileRef.tag()->properties();
        for (int i = 0; i < this->rowCount(); ++i) {
            const auto* key = this->item(i, 0);
            const auto* value = this->item(i, 1);
            if (key && value) {
                props[TagLib::String(key->text().toUtf8().data())]
                        = TagLib::String(value->text().toUtf8().data()).split(";");
            }
        }

        TagLib::Tag* tag = fileRef.tag(); tag->setProperties(props);
        ok &= fileRef.save();
    }

#ifndef TEST_RUN
    QMessageBox* box = new QMessageBox(
                ok ? QMessageBox::Icon::Information : QMessageBox::Icon::Critical,
                "Сохранение",
                ok ? "Сохранено успешно" : "Ошибка сохранения",
                QMessageBox::StandardButton::Ok,
                this
    ); box->open();
#endif
}
