#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete conj;
    delete ui;
}

void MainWindow::on_pushButton_gerar_clicked()
{
    try {
        if (ui->lineEdit_inputGerar->text().isEmpty()){
            throw QString("Valor invalido, precisa ser numero");
        }
        QString texto = ui->lineEdit_inputGerar->text();
        for (int i = 0; i < texto.size(); i++){
            if (texto[i] > '9' || texto[i] < '0'){
                throw QString("Valor invalido, precisa ser numero positivo");
            }
        }
        if (ui->lineEdit_inputGerar->text().toInt() <= 0){
            throw QString("Tamanho invalido, precisa ser um numero maior que 0");
        }
        if (conj){
            delete conj;
        }
        conj = new Pedro::Conjunto(ui->lineEdit_inputGerar->text().toInt());
        ui->textEdit_vetorAleatorio->setText(conj->getConjunto());
        conj->selectionSort();
        ui->textEdit_vetorOrdenado->setText(conj->getConjuntoOrdenado());
    }catch(QString &erro){
        QMessageBox::critical(this,"Erro", erro);
    }
    catch (std::bad_alloc &e) {
        QMessageBox::critical(this,"Erro", "Nao foi possivel alocar memoria");
    }
}


void MainWindow::on_pushButton_buscar_clicked()
{
    try {
        if (!conj){
            throw QString("Conjunto nao criado");
        }
        if (ui->lineEdit_inputValor->text().isEmpty()){
            throw QString("Valor invalido, precisa ser numero");
        }
        QString texto = ui->lineEdit_inputValor->text();
        for (int i = 0; i < texto.size(); i++){
            if (texto[i] > '9' || texto[i] < '0'){
                throw QString("Valor invalido, precisa ser numero");
            }
        }
        int indice = conj->buscarValorOrdenado(ui->lineEdit_inputValor->text().toInt());
        if (indice == -1){
            ui->textEdit_resultadoBusca->setText("Valor nao existe");
        }else{
            ui->textEdit_resultadoBusca->setText("Valor existe e esta na posicao " + QString::number(indice));
        }
    } catch (QString &e) {
        QMessageBox::critical(this,"Erro", e);
    }
}


void MainWindow::on_pushButton_buscaBinaria_clicked()
{
    try {
        if (!conj){
            throw QString("Conjunto nao criado");
        }
        if (ui->lineEdit_inputValorBinario->text().isEmpty()){
            throw QString("Valor invalido, precisa ser numero");
        }
        QString texto = ui->lineEdit_inputValorBinario->text();
        for (int i = 0; i < texto.size(); i++){
            if (texto[i] > '9' || texto[i] < '0'){
                throw QString("Valor invalido, precisa ser numero");
            }
        }
        int indice = conj->buscaBinaria(ui->lineEdit_inputValorBinario->text().toInt());
        if (indice == -1){
            ui->textEdit_resultadoBuscaBinaria->setText("Valor nao existe");
        }else{
            ui->textEdit_resultadoBuscaBinaria->setText("Valor existe e esta na posicao " + QString::number(indice));
        }
    } catch (QString &e) {
        QMessageBox::critical(this,"Erro", e);
    }
}

