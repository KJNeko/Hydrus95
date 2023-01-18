//
// Created by kj16609 on 1/17/23.
//

#ifndef HYDRUS95_GAMEIMPORTDIALOG_HPP
#define HYDRUS95_GAMEIMPORTDIALOG_HPP

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui
{
	class GameImportDialog;
}
QT_END_NAMESPACE

class GameImportDialog : public QDialog
{
	Q_OBJECT

	Q_DISABLE_COPY_MOVE(GameImportDialog)

	public:
	explicit GameImportDialog( QWidget* parent = nullptr );
	~GameImportDialog() override;

	private:
	Ui::GameImportDialog* ui;
};


#endif	//HYDRUS95_GAMEIMPORTDIALOG_HPP