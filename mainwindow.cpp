#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <Deasystem/StdStream.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FilesystemContainer* container = new FilesystemContainer();
    Dea::StdStream* strm = new Dea::StdStream("/home/metalhead33/NetBeansProjects/Filesystem2/dist/Debug/CLang-Linux/test.raw");
    container->Unserialize(strm);
    ui->treeView->setModel(container);
    ui->stackedWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    cur_elem = (Dea::Element*)index.internalPointer();
    ui->NameEditor->setText(QString::fromStdString(cur_elem->GetName()));
    RefreshEditorType();
}

void MainWindow::on_NameEditor_editingFinished()
{
    if(cur_elem) cur_elem->SetName(ui->NameEditor->text().toStdString());
}

void MainWindow::on_ElementNameButton_accepted()
{
    on_NameEditor_editingFinished();
}

void MainWindow::on_ElementNameButton_rejected()
{
    if(cur_elem) ui->NameEditor->setText(QString::fromStdString(cur_elem->GetName()));
}
void MainWindow::RefreshEditorType()
{
    if(!cur_elem) ui->stackedWidget->hide();
    else
    {
        if(cur_elem->IsDirectory()) ui->stackedWidget->hide();
        else
        {
          ui->stackedWidget->show();
          Dea::File* temp_file = (Dea::File*)cur_elem;
          switch(temp_file->GetFiletype())
          {
            case Dea::boolean :
          {
              ui->stackedWidget->setCurrentIndex(2);
              ui->comboBox->setCurrentIndex((int)((Dea::BoolFile*)cur_elem)->GetContent() );
              break;
          }
          case Dea::int8 :
        {
            ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::Int8File*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::int16 :
        {
            ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::Int16File*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::int32 :
        {
              ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::Int32File*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::int64 :
        {
              ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::Int64File*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::uint8 :
        {
              ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::Uint8File*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::uint16 :
        {
              ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::Uint16File*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::uint32 :
        {
              ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::Uint32File*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::uint64 :
        {
              ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::Uint64File*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::float32 :
        {
              ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::FloatFile*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::float64 :
        {
              ui->stackedWidget->setCurrentIndex(0);
            std::stringstream convert;
            convert << ((Dea::DoubleFile*)temp_file)->GetContent();
            ui->lineEdit->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::string8 :
        {
              ui->stackedWidget->setCurrentIndex(1);
            ui->plainTextEdit->setPlainText(QString::fromStdString(*((Dea::String8File*)temp_file)->GetContent()  ) );
            break;
        }
          case Dea::string16 :
        {
              ui->stackedWidget->setCurrentIndex(1);
            ui->plainTextEdit->setPlainText(QString::fromStdU16String(*((Dea::String16File*)temp_file)->GetContent()  ) );
            break;
        }
          case Dea::string32 :
        {
              ui->stackedWidget->setCurrentIndex(1);
            ui->plainTextEdit->setPlainText(QString::fromStdU32String(*((Dea::String32File*)temp_file)->GetContent()  ) );
            break;
        }
          default:
              break;
          }
    }
    }
}
void MainWindow::AcceptChange()
{
    if(!cur_elem) return;
    else
    {
        if(cur_elem->IsDirectory()) return;
        else
        {
          Dea::File* temp_file = (Dea::File*)cur_elem;
          switch(temp_file->GetFiletype())
          {
            case Dea::boolean :
          {
              ((Dea::BoolFile*)temp_file)->SetContent(ui->comboBox->currentIndex() > 0);
              break;
          }
          case Dea::int8 :
        {
              try {
                  ((Dea::Int8File*)temp_file)->SetContent( (int8_t)std::stoi(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::int16 :
        {
              try {
                  ((Dea::Int16File*)temp_file)->SetContent( (int16_t)std::stoi(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::int32 :
        {
              try {
                  ((Dea::Int32File*)temp_file)->SetContent( (int32_t)std::stoi(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::int64 :
        {
              try {
                  ((Dea::Int64File*)temp_file)->SetContent( (int64_t)std::stoi(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::uint8 :
        {
              try {
                  ((Dea::Uint8File*)temp_file)->SetContent( (uint8_t)std::stoi(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::uint16 :
        {
              try {
                  ((Dea::Uint16File*)temp_file)->SetContent( (uint16_t)std::stoi(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::uint32 :
        {
              try {
                  ((Dea::Uint32File*)temp_file)->SetContent( (uint32_t)std::stoi(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::uint64 :
        {
              try {
                  ((Dea::Uint64File*)temp_file)->SetContent( (uint64_t)std::stoi(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::float32 :
        {
              try {
                  ((Dea::FloatFile*)temp_file)->SetContent( (float)std::stof(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::float64 :
        {
              try {
                  ((Dea::DoubleFile*)temp_file)->SetContent( (double)std::stod(ui->lineEdit->text().toStdString() ) );
              } catch (std::exception e) {
                  ;
              }
            break;
        }
          case Dea::string8 :
        {
            ((Dea::String8File*)temp_file)->SetContent(ui->plainTextEdit->toPlainText().toStdString());
            break;
        }
          case Dea::string16 :
        {
            ((Dea::String16File*)temp_file)->SetContent(ui->plainTextEdit->toPlainText().toStdU16String());
            break;
        }
          case Dea::string32 :
        {
              ((Dea::String32File*)temp_file)->SetContent(ui->plainTextEdit->toPlainText().toStdU32String());
            break;
        }
          default:
              break;
          }
    }
    }
    RefreshEditorType();
}

void MainWindow::on_LineEditorBox_accepted()
{
    AcceptChange();
}

void MainWindow::on_LineEditorBox_rejected()
{
    RefreshEditorType();
}

void MainWindow::on_TexteditBox_accepted()
{
    AcceptChange();
}

void MainWindow::on_TexteditBox_rejected()
{
    RefreshEditorType();
}

void MainWindow::on_comboButton_accepted()
{
    AcceptChange();
}

void MainWindow::on_comboButton_rejected()
{
    RefreshEditorType();
}
