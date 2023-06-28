#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    {
        QFile style(":/ui/qss/style.qss");
        if (style.open(QFile::ReadOnly)) this->setStyleSheet(style.readAll());
        else qDebug() << "Failed to load styles";
    }

    ui->dropReceiver->setIcons(":/ui/svg/drag-drop-icon.svg", ":/ui/svg/drag-drop-icon-activated.svg");
    ui->dropReceiver->setActivated(false);
    ui->dropReceiver->setScale(0.5);
    ui->splitter->setSizes(QList<int>{static_cast<int>(ui->splitter->width() * 0.3), static_cast<int>(ui->splitter->width() * 0.7)});

    QObject::connect(ui->openFileButton, &OpenFileButton::clicked, ui->openFileButton, &OpenFileButton::chooseFiles, Qt::DirectConnection);
    QObject::connect(ui->openFileButton, &OpenFileButton::filesChosen, ui->fileList, &FileListWidget::filesProvided, Qt::DirectConnection);
    QObject::connect(ui->dropReceiver, &AudiofileDropReceiver::filesDropped, ui->fileList, &FileListWidget::filesProvided, Qt::DirectConnection);
    QObject::connect(ui->closeButton, &QPushButton::clicked, ui->fileList, &FileListWidget::selectedFilesRemoved, Qt::DirectConnection);
    QObject::connect(ui->saveButton, &QPushButton::clicked, ui->fileList, &FileListWidget::selectedFilesSaved, Qt::DirectConnection);
    QObject::connect(ui->fileList, &FileListWidget::updateContent, ui->metaDataWidget, &AudioMetadataWidget::updateMeta, Qt::DirectConnection);
    QObject::connect(ui->fileList, &FileListWidget::saveContent, ui->metaDataWidget, &AudioMetadataWidget::saveMeta, Qt::DirectConnection);
    QObject::connect(ui->fileList, &FileListWidget::updateContent, ui->mainAreaWidget, [this](){ this->ui->mainAreaWidget->setCurrentIndex(1); }, Qt::DirectConnection);
    QObject::connect(ui->fileList, &FileListWidget::contentEmpty, ui->mainAreaWidget, [this](){ this->ui->mainAreaWidget->setCurrentIndex(0); }, Qt::DirectConnection);
    QObject::connect(ui->metaDataWidget, &AudioMetadataWidget::fileLoaded, ui->fileList, &FileListWidget::newFileLoaded, Qt::DirectConnection);
}

MainWindow::~MainWindow() {
    delete ui;
}

