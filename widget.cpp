#include "widget.h"
#include <QJsonObject>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QTextBrowser>
#include "question.h"
Widget::Widget(QJsonObject json)
{
    auto l = new QVBoxLayout;
    setLayout(l);

    auto text = new QTextBrowser;
    text->setText(json["theory"].toString());
    l->addWidget(text);
    auto questsJson = json["questions"].toArray();
    for(auto questJson:questsJson)
    {
        auto questWidget = new Question(questJson.toObject());
        l->addWidget(questWidget);
    }

}

