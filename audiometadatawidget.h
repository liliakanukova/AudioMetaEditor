#ifndef AUDIOMETADATAWIDGET_H
#define AUDIOMETADATAWIDGET_H

#include <QTableWidget>
#include <QMessageBox>
#include <QTextStream>
#include <QList>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tstring.h>
#include <taglib/tstringlist.h>
#include <taglib/tpropertymap.h>

/**
 * @brief Класс AudioMetadataWidget реализует виджет-таблицу для хранения
 * и редактирования метаданных. Управляет чтением и записью метаданных.
 */
class AudioMetadataWidget : public QTableWidget {
public:
    /**
     * @brief Перечислление LoadResult используется для возвращения кода ошибки из методов этого класса.
     * @ref NO_ERR операция успешна
     * @ref FILE_ERROR ошибка открытия файла
     * @ref NO_TAG ошибка чтения метаданных
     * @ref NO_FILES попытка вызвать @ref load() с пустым множеством путей до файлов
     */
    enum LoadResult {NO_ERR, FILE_ERROR, NO_TAG, NO_FILES};

private:
    Q_OBJECT

    /**
     * Внутренний метод, используемый для объедниения последовательности элементов
     * от @param begin до @param end в строку, с разделителм @param sep
     * @return результирующая строка
     */
    template<typename Iter>
    static QString join(Iter begin, Iter end, char sep = ' ') {
        QString out;
        QTextStream outStream(&out);
        if (begin != end) {
            outStream << begin->toCString(); ++begin;
            for (; begin != end; ++begin) {
                outStream << sep << *begin->toCString();
            }
        }

        return out;
    }

    /**
     * @brief getFileRef получает ссылку на файл по пути и проводит проверку на ошибки по необходимости
     * @param out переменная, в которую будет записана полученная ссылка
     * @param name путь до файла, к которому требуется получить ссылку
     * @param errorCheck требуется ли проверка на ошибки
     * @return код состояния операции
     * @see LoadResult
     */
    LoadResult getFileRef(TagLib::FileRef& out, const QString& name, bool errorCheck = true);

    /**
     * @brief buildDefault устанавливает стандартные ключи без значений в таблицу
     */
    void buildDefault();

protected:
    /**
     * @brief isSingleFile является ли открытый сейчас файл единственным
     */
    bool isSingleFile;

    /**
     * @brief messageFromType получает сообщение, соответствующее переданному коду состояния
     * @param type код, для которого требуется получить сообщение
     * @return полученное сообщение
     */
    virtual QString messageFromType(LoadResult type);

public:
    AudioMetadataWidget(QWidget* parent = nullptr) : QTableWidget(parent) {}

    /**
     * @brief load загружает метаданные из файлов и отображает их в таблице.
     * В случае, если было передано более одного файла, отобрадает лишь пары ключ-значение,
     * общие для всех переданных файлов
     * @param files множество путей ло файлов для загрузки
     * @return код состояния операции
     */
    LoadResult load(const QSet<QString>& files);

    /**
     * @brief showErrorMessage отображает @see QMessageBox в соответствии с кодом ошибки.
     * Если предоставлено имя файла, вызвавшего ошибку, добавляет его к сообщению
     * @param type код, для которого требуется отобразить сообщение
     * @param fileName имя файла, вызвавшего ошибку
     */
    void showErrorMessage(LoadResult type, QString fileName=QString());

signals:
    /**
     * @brief fileLoaded используется для подтверждения того, что файл успешно загружен.
     * Подключен к @ref FileListWidget::newFileLoaded
     * @param name путь до загруженного файла
     */
    void fileLoaded(const QString& name);

public slots:
    /**
     * @brief updateMeta принимает сигнал с требованием обновить данные, очищает таблицу
     * и вызывает метод @ref load()
     * @param пути до файлов, который должны быть загружены
     */
    void updateMeta(const QSet<QString>&);

    /**
     * @brief saveMeta ринимает сигнал с требованием сохранить данные и
     * выполняет операцию сохранения
     * @param пути до файлов, который должны быть сохранены
     */
    void saveMeta(const QSet<QString>&);
};

#endif // AUDIOMETADATAWIDGET_H
