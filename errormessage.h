#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include<QKeyEvent>
#include <QWidget>

class ErrorMessage : public QWidget
{
    Q_OBJECT
public:
    explicit ErrorMessage(QString s, QWidget *parent = nullptr);

signals:

public slots:
    void exit();
protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // ERRORMESSAGE_H
