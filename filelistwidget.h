#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include <QListWidget>
#include <QSet>
#include <QMimeType>
#include <QMimeDatabase>
#include <QMessageBox>

/**
 * @brief Класс FileListWidget реализует виджет, управляющий
 * открытыми файлами. Отображает список полных путей до открытых файлов.
 */
class FileListWidget : public QListWidget {
private:
    Q_OBJECT

protected:
    /**
     * @brief fileNames множество путей до файлов, открытых в данный момент
     */
    QSet<QString> fileNames;

public:
    FileListWidget(QWidget* parent = nullptr) : QListWidget(parent) {
        this->setSelectionMode(QAbstractItemView::MultiSelection);
    }

signals:
    /**
     * @brief updateContent сигнал, испускаемый, когда были открыты/закрыты
     * некоторые (возможно, все) файлы и @ref AudioMetadataWidget требуется обновить
     * данные, связанные с этими файлами.
     * @param множество путей до файлов, которые открыты в текущий момент
     */
    void updateContent(const QSet<QString>&);

    /**
     * @brief saveContent сигнал, испускаемый, когда требуется записать данные,
     * хранимые в @ref AudioMetadataWidget, в файлы
     * @param множество путей до файлов, в которых требуется сохранить изменения
     */
    void saveContent(const QSet<QString>&);

    /**
     * @brief contentEmpty сигнал, испускаемый, когда не осталось
     * больше ни одного открытого файла
     */
    void contentEmpty();

public slots:
    /**
     * @brief filesProvided слот, принимающий новые файлы на вход.
     * Подключен к @ref OpenFileButton::filesChosen и @ref AudiofileDropReceiver::filesDropped
     * @param множество имен файлов, которые требуется добавить.
     * Испускает @ref updateContent()
     */
    void filesProvided(QSet<QString>&);

    /**
     * @brief newFileLoaded используется для подтверждения того, что
     * файл действительно успешно обработан. Добавляет путь до файла в список.
     * @param путь до загруженного файла
     */
    void newFileLoaded(const QString);

    /**
     * @brief selectedFilesRemoved используется для закрытия выделенных пользователем файлов
     * и удаления их из списка. Испускает @ref updateContent.
     * @warning не вызывает сохранения файлов.
     */
    void selectedFilesRemoved();

    /**
     * @brief selectedFilesSaved используется для сохранения выделенных пользователем файлов.
     * Испускает @ref saveContent.
     */
    void selectedFilesSaved();
};

#endif // FILELISTWIDGET_H
