#include "FilesystemContainer.hpp"

FilesystemContainer::FilesystemContainer()
    : QAbstractItemModel(), Dea::FsSystem()
{
    ;
}

FilesystemContainer::~FilesystemContainer()
{
    ;
}
QModelIndex FilesystemContainer::index(int row, int column, const QModelIndex &parent) const
{
    if(!parent.isValid())
        return createIndex(row, column, GetRoot()->PGetByRowSafe(row));
    else
    {
        return createIndex(row,column,((Dea::Directory*)parent.internalPointer())->PGetByRowSafe(row));
    }
}
QModelIndex FilesystemContainer::parent(const QModelIndex &child) const
{
    if(!child.isValid()) return QModelIndex();
    Dea::Element* element = (Dea::Element*)child.internalPointer();
    Q_ASSERT(element);
    Dea::Directory* parent = element->GetParent();
    if(!parent) return QModelIndex();
    if(parent == GetRoot()) return QModelIndex();

    int row = 0;
    Dea::Directory* higher_parent = parent->GetParent();

    if(higher_parent)
    {
        Dea::ElementContainer* children = higher_parent->GetContainer();
        Dea::ElementIterator it;
      if(!children->empty()) for(it = children->begin(), row = 0;it != children->end() && (*it) != parent;++row,++it);
    }

return createIndex(row, 0, parent);
}

int FilesystemContainer::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        Dea::Element* elem = (Dea::Element*)parent.internalPointer();
        if(elem->IsDirectory()) return ((Dea::Directory*)elem)->GetContainer()->size();
        else return 0;
        //return ((Structure::Directory*)parent.internalPointer())->GetNumChildren();
    }
    else return GetRoot()->GetContainer()->size();
}

int FilesystemContainer::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant FilesystemContainer::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= rowCount(index.parent())) return QVariant();
    //if(role != Qt::DisplayRole) return QVariant();
    //return QString::fromStdString(((Structure::Element*)index.internalPointer())->GetName());
    switch(role)
    {
    case Qt::DisplayRole :
        return QString::fromStdString(((Dea::Element*)index.internalPointer())->GetName());
    default:
        return QVariant();
    }
}

bool FilesystemContainer::removeRows(int row, int count, const QModelIndex &parent)
{
    if(parent.isValid()) {
        Dea::Element* parent_elem = (Dea::Element*)parent.internalPointer();
        if(!parent_elem) return false;
        if(!parent_elem->IsDirectory()) return false;
        Dea::Directory* parent_dir = (Dea::Directory*)parent_elem;
        if(rowCount(parent) < row+count) return false;
        beginRemoveRows(parent,row,row+count);
        for(int i = 0;i < count;++i) delete parent_dir->PGetByRowSafe(row);
        endRemoveRows();
        return true;
    }
    else return false;
}

bool FilesystemContainer::AddElement(const QModelIndex &parent,QString name,int8_t type)
{
    if(name.isEmpty()) return false;
    if(parent.isValid())
    {
        if( ((Dea::Directory*)parent.internalPointer())->PGetByName(name.toStdString() ) ) return false; //We don't overwrite.
        switch(type)
        {
        case 0:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::Directory((Dea::Directory*)parent.internalPointer(),name.toStdString());
            endInsertRows();
            return true;
            break;
        }
        case 1:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::BoolFile((Dea::Directory*)parent.internalPointer(),name.toStdString(),false);
            endInsertRows();
            return true;
            break;
        }
        case 2:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::Int8File((Dea::Directory*)parent.internalPointer(),name.toStdString(),0);
            endInsertRows();
            return true;
            break;
        }
        case 3:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::Int16File((Dea::Directory*)parent.internalPointer(),name.toStdString(),0);
            endInsertRows();
            return true;
            break;
        }
        case 4:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::Int32File((Dea::Directory*)parent.internalPointer(),name.toStdString(),0);
            endInsertRows();
            return true;
            break;
        }
        case 5:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::Int64File((Dea::Directory*)parent.internalPointer(),name.toStdString(),0);
            endInsertRows();
            return true;
            break;
        }
        case 6:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::Uint8File((Dea::Directory*)parent.internalPointer(),name.toStdString(),0);
            endInsertRows();
            return true;
            break;
        }
        case 7:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::Uint16File((Dea::Directory*)parent.internalPointer(),name.toStdString(),0);
            endInsertRows();
            return true;
            break;
        }
        case 8:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::Uint32File((Dea::Directory*)parent.internalPointer(),name.toStdString(),0);
            endInsertRows();
            return true;
            break;
        }
        case 9:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::Uint64File((Dea::Directory*)parent.internalPointer(),name.toStdString(),0);
            endInsertRows();
            return true;
            break;
        }
        case 10:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::FloatFile((Dea::Directory*)parent.internalPointer(),name.toStdString(),0.00);
            endInsertRows();
            return true;
            break;
        }
        case 11:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::DoubleFile((Dea::Directory*)parent.internalPointer(),name.toStdString(),0.00);
            endInsertRows();
            return true;
            break;
        }
        case 12:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::String8File((Dea::Directory*)parent.internalPointer(),name.toStdString(),"");
            endInsertRows();
            return true;
            break;
        }
        case 13:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::String16File((Dea::Directory*)parent.internalPointer(),name.toStdString(),u"");
            endInsertRows();
            return true;
            break;
        }
        case 14:
        {
            beginInsertRows(parent,parent.row()+1,parent.row()+1);
            new Dea::String32File((Dea::Directory*)parent.internalPointer(),name.toStdString(),U"");
            endInsertRows();
            return true;
            break;
        }
        default:
        {
            return false;
            break;
        }
        }
        return true;
    }
    else return false;
}
