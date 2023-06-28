#include <QTest>
#include <QObject>
#include <QFile>
#include <QSet>
#include <QApplication>
#include <QSignalSpy>

#include "../audiometadatawidget.h"

class TestMetaParsing : public QObject {
private:
    Q_OBJECT

private slots:
    void cleanup();
    void testSingleParsing();
    void testMultipleParsing();
    void testWrite();

};

void TestMetaParsing::cleanup() {
    QVERIFY(QGuiApplication::allWindows().isEmpty());
}

void TestMetaParsing::testSingleParsing() {
    int argc = 1;
    char *argv[] = { const_cast<char*>("test_meta_parsing") };
    QApplication app(argc, argv);
    AudioMetadataWidget w;
    QSignalSpy spy(&w, &AudioMetadataWidget::fileLoaded);

    QSet<QString> files {"beep.mp3"};
    w.load(files);
    QCOMPARE(spy.size(), 1);

    const auto* key = w.item(0, 0);
    const auto* value = w.item(0, 1);
    QVERIFY2(key && value, "ALBUM not found");
    QVERIFY2(key->text() == "ALBUM" && value->text() == "super album", "ALBUM tag doesnt match");

    key = w.item(1, 0);
    value = w.item(1, 1);
    QVERIFY2(key && value, "ARTIST not found");
    QVERIFY2(key->text() == "ARTIST" && value->text() == "human", "ARTIST tag doesnt match");

    key = w.item(2, 0);
    value = w.item(2, 1);
    QVERIFY2(key && value, "COMMENT not found");
    QVERIFY2(key->text() == "COMMENT" && value->text() == "good beep", "COMMENT tag doesnt match");

    key = w.item(3, 0);
    value = w.item(3, 1);
    QVERIFY2(key && value, "TITLE not found");
    QVERIFY2(key->text() == "TITLE" && value->text() == "213213", "TITLE tag doesnt match");
}

void TestMetaParsing::testMultipleParsing() {
    int argc = 1;
    char *argv[] = { const_cast<char*>("test_meta_parsing") };
    QApplication app(argc, argv);
    AudioMetadataWidget w;
    QSignalSpy spy(&w, &AudioMetadataWidget::fileLoaded);

    QSet<QString> files {"beep.mp3", "beep-intersect.mp3"};
    w.load(files);
    QCOMPARE(spy.size(), 2);

    const auto* key = w.item(0, 0);
    const auto* value = w.item(0, 1);
    QVERIFY2(key && value, "ARTIST not found");
    QVERIFY2(key->text() == "ARTIST" && value->text() == "human", "ARTIST tag doesnt match");


    key = w.item(1, 0);
    value = w.item(1, 1);
    QVERIFY2(key && value, "COMMENT not found");
    QVERIFY2(key->text() == "COMMENT" && value->text() == "good beep", "COMMENT tag doesnt match");

    key = w.item(2, 0);
    value = w.item(2, 1);
    QVERIFY2(key && value, "TITLE not found");
    QVERIFY2(key->text() == "TITLE" && value->text() == "213213", "TITLE tag doesnt match");
}

void TestMetaParsing::testWrite() {
    int argc = 1;
    char *argv[] = { const_cast<char*>("test_meta_parsing") };
    QApplication app(argc, argv);



    {
        AudioMetadataWidget w;
        QTableWidgetItem* newValue = new QTableWidgetItem("new title");
        QSignalSpy spy(&w, &AudioMetadataWidget::fileLoaded);

        QSet<QString> files {"beep-empty.wav"};
        w.load(files);
        QCOMPARE(spy.size(), 1);

        const auto* key = w.item(0, 0);
        QVERIFY2(key, "TITLE not found");
        w.setItem(0, 1, newValue);
        w.saveMeta(files);
    }

    AudioMetadataWidget w;
    QSignalSpy spy(&w, &AudioMetadataWidget::fileLoaded);

    QSet<QString> files {"beep-empty.wav"};
    w.load(files);
    QCOMPARE(spy.size(), 1);
    const auto* key = w.item(0, 0);
    auto* value = w.item(0, 1);
    QVERIFY2(key && value, "TITLE not found");
    QVERIFY2(value->text() == "new title", "title doesent match");
}

QTEST_APPLESS_MAIN(TestMetaParsing)
#include "test_meta_parsing.moc"
