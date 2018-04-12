#ifndef UIENGINE_H
#define UIENGINE_H

#include <QDialog>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <QGraphicsDropShadowEffect>
#include <QLabel>

namespace Ui {
class UIEngine;
}

class UIEngine : public QDialog
{
    Q_OBJECT

public:
    explicit UIEngine(QWidget *parent = 0);
    ~UIEngine();
    QString returnPass();
    void numberButtonPressed();
    void numberButtonAction();

public slots:
    void timer_timeout();

private slots:
    void on_buttonOk_clicked();
    void on_buttonDel_clicked();
    void on_button0_clicked();
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void on_button4_clicked();
    void on_button5_clicked();
    void on_button6_clicked();
    void on_button7_clicked();
    void on_button8_clicked();
    void on_button9_clicked();
    void on_buttonPoistu_clicked();

private:
    Ui::UIEngine *ui;
    QTimer *timer;
    QString pass;
    int counter;
    int idleTimer;
    QList<QPushButton*> button_list_;
    QList<QGraphicsDropShadowEffect*> shadow_list_;
    QList<QLabel*> label_list_;
    QString pincode;
    bool okPressed;
};

#endif // UIENGINE_H
