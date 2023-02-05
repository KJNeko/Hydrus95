//
// Created by kj16609 on 1/15/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RecordView.h" resolved

#include "RecordView.hpp"
#include "ui_RecordView.h"


RecordView::RecordView( QWidget* parent ) : QWidget( parent ), ui( new Ui::RecordView )
{
	ui->setupUi( this );

	ui->splitter->setStretchFactor( 1, 0 );
	ui->selectedView->hide();

	// Connect backend to view
	connect(
		&backend,
		SIGNAL( recordsUpdated( const std::vector< Record >& ) ),
		ui->recordView,
		SLOT( recordsUpdated( const std::vector< Record >& ) ) );

	/*
	//Connect backend to tag display
	connect(
		&backend,
		SIGNAL( tagsChanged( const std::vector< Tag >& ) ),
		ui->tagView,
		SLOT( tagsChanged( const std::vector< Tag >& ) ) );
	connect( ui->tagView, SIGNAL( selected( const Tag& ) ), &backend, SLOT( removeTag( const Tag& ) ) );

	//Connect to search
	connect(
		&backend,
		SIGNAL( similarTagFinished( const std::vector< Tag >& ) ),
		ui->tagSearch,
		SLOT( similarTagFinished( const std::vector< Tag >& ) ) );
	connect(
		ui->tagSearch,
		SIGNAL( searchSimilar( const QString& ) ),
		&backend,
		SLOT( searchSimilar( const QString& ) ) );
	connect( ui->tagSearch->view(), SIGNAL( selected( const Tag& ) ), &backend, SLOT( addTag( const Tag& ) ) );
	 */

	//Connect intermediate pieces
	connect(
		ui->recordView,
		SIGNAL( changeSelection( const QPersistentModelIndex& ) ),
		ui->selectedView,
		SLOT( recordSelected( const QPersistentModelIndex& ) ) );

	connect(
		ui->recordView,
		SIGNAL( changeSelection( const QPersistentModelIndex& ) ),
		this,
		SLOT( recordSelected( const QPersistentModelIndex& ) ) );

	backend.refresh();
}

void RecordView::recordSelected( const QPersistentModelIndex& index )
{
	if ( index.isValid() )
		ui->selectedView->show();
	else
		ui->selectedView->hide();
}

RecordView::~RecordView()
{
	delete ui;
}

void RecordView::refresh()
{
	backend.refresh();
}