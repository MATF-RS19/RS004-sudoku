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
    /* Closes the current window
     */
    void exit();
protected:

    /* Handles keyboard inputs
     * Only the escape key is defined and causes the window to close
     */
    void keyPressEvent(QKeyEvent *e);
};

#endif // ERRORMESSAGE_H
