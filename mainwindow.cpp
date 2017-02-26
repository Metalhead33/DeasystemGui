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
void MainWindow::RefreshEditorType()
{
    if(!cur_elem)
    {
        ui->ContentEditLine->hide();
        ui->ContentEditFull->hide();
        ui->ElementContextButton->hide();
        ui->FileContent->hide();
    }
    else
    {
        if(cur_elem->IsDirectory())
        {
            ui->ContentEditLine->hide();
            ui->ContentEditFull->hide();
            ui->ElementContextButton->hide();
            ui->FileContent->hide();
        }
        else
        {
          Dea::File* temp_file = (Dea::File*)cur_elem;
          ui->ElementContextButton->show();
          ui->FileContent->show();
          switch(temp_file->GetFiletype())
          {
            case Dea::boolean :
          {
              ui->ContentEditLine->hide();
              ui->ContentEditFull->hide();
              break;
          }
          case Dea::int8 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::Int8File*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::int16 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::Int16File*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::int32 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::Int32File*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::int64 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::Int64File*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::uint8 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::Uint8File*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::uint16 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::Uint16File*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::uint32 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::Uint32File*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::uint64 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::Uint64File*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::float32 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::FloatFile*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::float64 :
        {
            ui->ContentEditLine->show();
            ui->ContentEditFull->hide();
            std::stringstream convert;
            convert << ((Dea::DoubleFile*)temp_file)->GetContent();
            ui->ContentEditLine->setText(QString::fromStdString(convert.str() ) );
            break;
        }
          case Dea::string8 :
        {
            ui->ContentEditLine->hide();
            ui->ContentEditFull->show();
            ui->ContentEditFull->setPlainText(QString::fromStdString(*((Dea::String8File*)temp_file)->GetContent()  ) );
            break;
        }
          case Dea::string16 :
        {
            ui->ContentEditLine->hide();
            ui->ContentEditFull->show();
            ui->ContentEditFull->setPlainText(QString::fromStdU16String(*((Dea::String16File*)temp_file)->GetContent()  ) );
            break;
        }
          case Dea::string32 :
        {
            ui->ContentEditLine->hide();
            ui->ContentEditFull->show();
            ui->ContentEditFull->setPlainText(QString::fromStdU32String(*((Dea::String32File*)temp_file)->GetContent()  ) );
            break;
        }
          }
        }
    }
}

