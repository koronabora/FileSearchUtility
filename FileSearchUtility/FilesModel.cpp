#include "FilesModel.h"

FilesModel::FilesModel(QObject* parent) : QAbstractTableModel(parent)
{}

Qt::ItemFlags FilesModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	return flags;
}

QVariant FilesModel::data(const QModelIndex& index, int role) const
{
	if (index.isValid() && m_data.size() > index.row() && role == Qt::DisplayRole)
	{
		const QVariant v = m_data[index.row()][Columns(index.column())];
		if (index.column() == FILE_SIZE)
			return convertSize(v);
		return v;
	}

	return QVariant();
}

QVariant FilesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Vertical)
		return section;

	if (section < LAST_POS)
		return columnNames.at(section);

	return QVariant();
}

int FilesModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent)
		return m_data.count();
}

int FilesModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent)
		return LAST_POS;
}

bool FilesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && m_data.size() <= index.row() && role == Qt::EditRole)
	{
		m_data[index.row()][Columns(index.column())] = value;
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

void FilesModel::addFile(const QString& fileName, const quint64& fileSize)
{
	FileData data;
	data[FILE_NAME] = fileName;
	data[FILE_SIZE] = fileSize;

	int row = m_data.count();
	beginInsertRows(QModelIndex(), row, row);
	m_data.append(data);
	endInsertRows();
}

void FilesModel::clearData()
{
	int row = m_data.count() - 1;
	if (row >= 0)
	{
		beginRemoveRows(QModelIndex(), 0, row);
		m_data.clear();
		endRemoveRows();
	}
}

void FilesModel::sortCall(int logicalIndex)
{
	if (logicalIndex < LAST_POS)
	{
		columnSortDirections[logicalIndex] != columnSortDirections.at(logicalIndex);
		sort(Columns(logicalIndex));
	}
}

QVariant FilesModel::convertSize(const QVariant& s) const
{
	// narcomania
	QString res;
	quint64 v = s.toULongLong();
	size_t step = 0;
	quint64 foo = 0;
	quint64 buf = v;
	while (buf >= BYTES_IN_MB)
	{
		foo = buf % BYTES_IN_MB;
		buf = buf / BYTES_IN_MB;
		step++;
	}
	res = QString::number(buf) + "." + QString::number(foo);
	const double size = res.toDouble();
	res = QString("%1").arg(size, 0, 'f', 2);
	if (foo == 0)
		res = res.replace(".00", "");
	else
		if (res.at(res.size() - 1) == '0')
			res.remove(res.size() - 1, 1);
	if (step < sizeNames.size())
		res += " " + sizeNames.at(step);
	return res;
}

void FilesModel::sort(const Columns& column)
{ // may use proxy model
	auto compare = [&](const size_t& index0, const size_t& index1) -> bool
	{
		if (columnSortDirections.size() > column && index0<m_data.size() && index1 < m_data.size())
			if (columnSortDirections.at(column))
			{
				return m_data[index0][column] > m_data[index1][column];
			}
			else
			{
				return m_data[index0][column] < m_data[index1][column];
			}
		return false;
	};

	// bubble sort
	const size_t size = m_data.size();
	bool found = true;
	while (found)
	{
		found = false;
		for (size_t i = 0; i < size - 1; i++)
			if (compare(i, i+1))
			{
				FileData f = m_data.at(i+1);
				QModelIndex index;
				beginMoveRows(index, i, i, index, i + 1);
				m_data[i+1] = m_data[i];
				m_data[i] = f;
				endMoveRows();
			}
	}
}