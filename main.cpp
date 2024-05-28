#include "widget.h"
#include <QFile>
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QScrollArea>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file;
    file.setFileName("data.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "не найден файл", "требуется файл data.json в папке с билдом проекта");
        return a.exec();
    }
    QString val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

    QScrollArea area;
    auto w = new Widget(doc.object());
    area.setWidget(w);
    area.show();

    return a.exec();
}
