#include "FileSearchUtility.h"

FileSearchUtility::FileSearchUtility(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	folderGroupBox = ui.folderGroupBox;
	searchPathEdit = ui.searchPathEdit;
	selectPathButton = ui.selectPathButton;
	conditionGroupBox = ui.conditionGroupBox;
	conditionEdit = ui.conditionEdit;
	searchButton = ui.searchButton;
	resultsGroupBox = ui.resultsGroupBox;
	resultsTable = ui.resultsTable;
	statusBar = ui.statusBar;

	updateTranslations();
	if (searchPathEdit)
		searchPathEdit->setText(QDir::currentPath());

	// Runtime regexp check
	regexpParseTimer = new QTimer();
	connect(regexpParseTimer, &QTimer::timeout, this, &FileSearchUtility::testRegex);
	if (conditionEdit)
		connect(conditionEdit, &QPlainTextEdit::textChanged, this, &FileSearchUtility::conditionTextChanged);
	//

	if (selectPathButton)
		connect(selectPathButton, &QPushButton::clicked, this, &FileSearchUtility::selectFolderButtonClicked);
	if (searchButton)
	{
		searchButton->setEnabled(false);
		connect(searchButton, &QPushButton::clicked, this, &FileSearchUtility::searchButtonClicked);
		conditionTextChanged(); // start first check with delay
	}
}

FileSearchUtility::~FileSearchUtility()
{
	if (regexpParseTimer)
		regexpParseTimer->deleteLater();
}

void FileSearchUtility::conditionTextChanged()
{
	setConditionFieldColor(Qt::GlobalColor::white);
	regexpParseTimer->stop();
	regexpParseTimer->setSingleShot(true);
	regexpParseTimer->start(REGEXP_PARSING_DELAY);
}

void FileSearchUtility::setConditionFieldColor(const QColor& v)
{
	if (conditionEdit)
	{
		QPalette p = conditionEdit->palette();
		p.setColor(QPalette::Active, QPalette::Base, v);
		p.setColor(QPalette::Inactive, QPalette::Base, v);
		conditionEdit->setPalette(p);
	}
}

void FileSearchUtility::updateSearchButtonText()
{
	if (searchButton)
	{
		if (searchState)
			searchButton->setText(trUtf8("Stop"));
		else
			searchButton->setText(trUtf8("Start"));
	}
}

void FileSearchUtility::updateTranslations()
{
	if (folderGroupBox)
		folderGroupBox->setTitle(trUtf8("Folder"));
	if (conditionGroupBox)
		conditionGroupBox->setTitle(trUtf8("Condition"));
	updateSearchButtonText();
	if (resultsGroupBox)
		resultsGroupBox->setTitle(trUtf8("Results"));
}

void FileSearchUtility::selectFolderButtonClicked()
{
	setStatus(trUtf8("Select folder"));
	QString dir = QFileDialog::getExistingDirectory(this, trUtf8("Select Directory"),
		QDir::currentPath(),
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	if (searchPathEdit)
		searchPathEdit->setText(dir);
}

void FileSearchUtility::searchButtonClicked()
{
	searchState = !searchState;
	updateSearchButtonText();
	if (searchState)
	{
		if (searchPathEdit)
		{
			if (currentRegexp.isValid) // recheck, i think condition will be true always
				emit searchForFiles(searchPathEdit->text(), currentRegexp);
			else
				setConditionFieldColor(REGEXP_IS_INVALID_COLOR);
		}
	}
	else
	{
		emit stopSearch();
	}
}

void FileSearchUtility::testRegex()
{
	if (conditionEdit)
	{
		const QString val = conditionEdit->toPlainText();
#ifndef ALLOW_EMPTY_CONDIION
		if (!val.isEmpty())
#endif
		{
			pendigRegexps.clear();
			RegexpValidateData data;
			data.id = ++lastId;
			data.val = val;
			pendigRegexps.append(data.id);
			emit validateRegexp(data);
		}
	}
}

void FileSearchUtility::regexpValidated(RegexpValidateData data)
{
	if (!pendigRegexps.contains(data.id))
	{
		//setStatus(trUtf8("Regexp is too old"));
	}
	else
	{
		pendigRegexps.removeAll(data.id);
		if (data.isValid)
		{
			currentRegexp = data;
			setConditionFieldColor(REGEXP_IS_VALID_COLOR);
			searchButton->setEnabled(true);
		}
		else
			setConditionFieldColor(REGEXP_IS_INVALID_COLOR);
	}
}

void FileSearchUtility::haveSomeFile(const QString& path, const quint64& size)
{

}

void FileSearchUtility::searchFinished()
{
	searchState = !searchState;
	updateSearchButtonText();
}

void FileSearchUtility::setStatus(const QString& text)
{
	if (statusBar)
		statusBar->setToolTip(text);
}