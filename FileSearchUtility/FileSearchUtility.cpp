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

	if (selectPathButton)
		connect(selectPathButton, &QPushButton::clicked, this, &FileSearchUtility::selectFolderButtonClicked);
	if (searchButton)
		connect(searchButton, &QPushButton::clicked, this, &FileSearchUtility::searchButtonClicked);
}

void FileSearchUtility::updateTranslations()
{
	if (folderGroupBox)
		folderGroupBox->setTitle(trUtf8("Folder"));
	if (conditionGroupBox)
		conditionGroupBox->setTitle(trUtf8("Condition"));
	if (searchButton)
		searchButton->setText(trUtf8("Search"));
	if (resultsGroupBox)
		resultsGroupBox->setTitle(trUtf8("Results"));
}

void FileSearchUtility::selectFolderButtonClicked()
{
	statusBar->setToolTip(trUtf8("Select folder"));
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
}