#include "question.h"
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QPushButton>
#include <QMessageBox>
#include <QRadioButton>
#include <QLineEdit>
Question::Question(QJsonObject json)
{
    auto l= new QVBoxLayout;
    setLayout(l);
    auto text =new QLabel(json["questionText"].toString());
    l->addWidget(text);
    if(json["questionType"].toString()=="multipleAnswers")
    {
        auto options = json["options"].toArray();
        for(auto option:options)
        {
            auto b = new QCheckBox(option.toString());
            l->addWidget(b);
            buttons.push_back(b);
        }
    }
    else if(json["questionType"].toString()=="oneAnswer")
    {
        auto options = json["options"].toArray();
        for(auto option:options)
        {
            auto b = new QRadioButton(option.toString());
            l->addWidget(b);
            buttons.push_back(b);
        }
    }
    else if(json["questionType"].toString()=="freeAnswer")
    {
        freeAnswer = new QLineEdit;
        l->addWidget(freeAnswer);
    }


    auto push=new QPushButton("Принять");
    l->addWidget(push);
    connect(push, &QPushButton::clicked, [json, this](){
        QStringList selected; //ответы выбранные пользователем
        for(auto button:buttons)
        {
            if(button->isChecked()) selected<<button->text();
        }
        if(freeAnswer) selected<<freeAnswer->text();
        QStringList correct; //список с правильными ответами
        if(json["correctAnswer"].isArray())
        {
            auto correctAnswers = json["correctAnswer"].toArray();
            for(auto correctAnswer : correctAnswers)
            {
                correct<<correctAnswer.toString();
            }
        }
        else
            correct<<json["correctAnswer"].toString();

        if(selected==correct)
        {
            QMessageBox::information(this, "Правильный ответ!", "ПРАВИЛЬНЫЙ ОТВЕТ!");
        }
        else
        {
            QMessageBox::critical(this, "Не правильный ответ!", "НЕ ПРАВИЛЬНЫЙ ОТВЕТ!");
        }
    });
}
