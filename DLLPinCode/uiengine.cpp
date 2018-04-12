#include "uiengine.h"
#include "ui_uiengine.h"

UIEngine::UIEngine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIEngine)
{
    ui->setupUi(this);

    pincode = "";
    pass = "";
    counter = 0;
    idleTimer = 10;
    okPressed = false;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(timer_timeout()));


    timer->start(1000);
    ui->labelAnnatunnusluku->setStyleSheet("QLabel{background: transparent; color:white;}");
    ui->linePin->setStyleSheet("QLabel{background-color:white; border-width: 1px; border-style: solid; border-radius: 10px; border-color:white;}");


    button_list_ = this->findChildren<QPushButton*>();
    foreach(QPushButton *btn, button_list_) {
        shadow_list_.append(new QGraphicsDropShadowEffect);
        shadow_list_.back()->setBlurRadius(20);
        shadow_list_.back()->setOffset(5,5);
        btn->setGraphicsEffect(shadow_list_.back());
    }

    label_list_ =this->findChildren<QLabel*>();
    foreach(QLabel *lbl, label_list_){
        shadow_list_.append(new QGraphicsDropShadowEffect);
        shadow_list_.back()->setBlurRadius(20);
        shadow_list_.back()->setOffset(7,7);
        lbl->setGraphicsEffect(shadow_list_.back());
    }

}

UIEngine::~UIEngine()
{
    delete ui;
}

void UIEngine::on_buttonOk_clicked()
{
    if (counter == 4){
        qDebug()<<pass;
        okPressed = true;
        this->close();
    }
}

void UIEngine::on_buttonPoistu_clicked()
{
    this->close();
}

void UIEngine::on_buttonDel_clicked()
{
    if (counter <=4 && counter >= 1){
        pass.replace(counter - 1,1,"");
        pincode.replace(counter - 1,1,"");
        if (counter > 0){
            counter--;}

        ui->linePin->setText(pincode);
    }
    ui->buttonOk->setStyleSheet("QPushButton{background-color:rgb(163,163,163)}");
}

void UIEngine::on_button0_clicked()
{
    if (counter <= 3){
        pass.append("0");
       this->numberButtonAction();
    }
    this->numberButtonPressed();
}

void UIEngine::on_button1_clicked()
{
    if (counter <= 3){
        pass.append("1");
       this->numberButtonAction();
    }
    this->numberButtonPressed();
}

void UIEngine::on_button2_clicked()
{
    if (counter <= 3){
        pass.append("2");
        this->numberButtonAction();
    }
    this->numberButtonPressed();
}

void UIEngine::on_button3_clicked()
{
    if (counter <= 3){
        pass.append("3");
        this->numberButtonAction();
    }
    this->numberButtonPressed();
}

void UIEngine::on_button4_clicked()
{
    if (counter <= 3){
        pass.append("4");
        this->numberButtonAction();
    }
    this->numberButtonPressed();
}

void UIEngine::on_button5_clicked()
{
    if (counter <= 3){
        pass.append("5");
        this->numberButtonAction();
    }
    this->numberButtonPressed();
}

void UIEngine::on_button6_clicked()
{
    if (counter <= 3){
        pass.append("6");
        this->numberButtonAction();
    }
    this->numberButtonPressed();
}

void UIEngine::on_button7_clicked()
{
    if (counter <= 3){
        pass.append("7");
        this->numberButtonAction();
    }
    this->numberButtonPressed();
}

void UIEngine::on_button8_clicked()
{
    if (counter <= 3){
        pass.append("8");
        this->numberButtonAction();
    }
    this->numberButtonPressed();
}

void UIEngine::on_button9_clicked()
{
    if (counter <= 3){
        pass.append("9");
        this->numberButtonAction();
    }
    this->numberButtonPressed();
}

QString UIEngine::returnPass()
{
    if(okPressed == true)
    {
        return pass;
    }
    else
    {
        return 0;
    }
}

void UIEngine::timer_timeout()
{
    idleTimer--;
    if (idleTimer < 0)
    {
        this->close();
    }
}

void UIEngine::numberButtonAction()
{
    pincode.append("*");
    ui->linePin->setText(pincode);
    counter++;
    if(counter == 4){
    ui->buttonOk->setStyleSheet("QPushButton{background-color:rgb(255,255,255)}");
    }
    else{
        ui->buttonOk->setStyleSheet("QPushButton{background-color:rgb(163,163,163)}");
    }
}

void UIEngine::numberButtonPressed()
{
    timer->start(1000);
    idleTimer = 10;
}
