#ifndef QUESTION_H
#define QUESTION_H

#include <QWidget>
#include <QJsonObject>
#include <QAbstractButton>

class Question : public QWidget
{
    Q_OBJECT
public:
    explicit Question(QJsonObject json);
private:
    QVector<QAbstractButton*> buttons;
    class QLineEdit* freeAnswer = nullptr;
};

#endif // QUESTION_H
