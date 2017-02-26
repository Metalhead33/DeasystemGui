#ifndef FILESYSTEMCONTAINER_HPP
#define FILESYSTEMCONTAINER_HPP
#include <QAbstractItemModel>
#include <Deasystem/FsSystem.hpp>

class FilesystemContainer : public QAbstractItemModel, public Dea::FsSystem
{
public:
    FilesystemContainer();
    virtual ~FilesystemContainer();
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    //bool AddElement(const QModelIndex &parent,Structure::Element* elem);
    //bool AddDirectory(const QModelIndex &parent,QString name);
    //bool AddFile(const QModelIndex &parent,Structure::File::FileType type, QString name);
};

#endif // FILESYSTEMCONTAINER_HPP
