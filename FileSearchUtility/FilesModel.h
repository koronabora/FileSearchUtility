#pragma once

#include <QAbstractTableModel>
#include <QString>
#include <QStringList>
#include <QSortFilterProxyModel>
#include <QPointer>

#define BYTES_IN_MB 1024

class FileSortProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	FileSortProxyModel(QObject *parent = 0);

protected:
	bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

};

class FilesModel : public QAbstractTableModel {
	Q_OBJECT
public:
	FilesModel(QObject* parent = 0);

	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	int rowCount(const QModelIndex& parent) const override;
	int columnCount(const QModelIndex& parent) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role) override;

	void addFile(const QString& fileName, const quint64& fileSize);
	void clearData();

	QVariant rawData(const QModelIndex& index);

public slots:

private:
	enum Columns
	{
		FILE_NAME = 0,
		FILE_SIZE,
		LAST_POS
	};
	const QStringList columnNames =
	{
		trUtf8("Name"),
		trUtf8("Size")
	};

	const QStringList sizeNames =
	{
		trUtf8("bytes"),
		trUtf8("KB"),
		trUtf8("MB"),
		trUtf8("GB"),
		trUtf8("TB")
	};
	
	typedef QMap<Columns, QVariant> FileData;
	QVector<FileData> m_data;

	QVariant convertSize(const QVariant& s) const;
};