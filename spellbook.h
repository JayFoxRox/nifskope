/***** BEGIN LICENSE BLOCK *****

BSD License

Copyright (c) 2005, NIF File Format Library and Tools
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the NIF File Format Library and Tools projectmay not be
   used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***** END LICENCE BLOCK *****/

#ifndef SPELLBOOK_H
#define SPELLBOOK_H

#include "nifmodel.h"

#include <QMenu>

#define REGISTER_SPELL( SPELL ) static Librarian __##SPELL##__ ( new SPELL );

class Spell
{
public:
	Spell() {}
	virtual ~Spell() {}
	
	virtual QString name() const = 0;
	virtual QString page() const { return QString(); }
	virtual QString hint() const { return QString(); }

	virtual bool isApplicable( NifModel * nif, const QModelIndex & index ) = 0;
	
	virtual QModelIndex cast( NifModel * nif, const QModelIndex & index ) = 0;	
};

class SpellBook : public QMenu
{
	Q_OBJECT
public:
	SpellBook( NifModel * nif, const QModelIndex & index = QModelIndex(), QObject * receiver = 0, const char * member = 0 );
	~SpellBook();
	
	static void registerSpell( Spell * spell );
	
public slots:
	void sltNif( NifModel * nif );
	
	void sltIndex( const QModelIndex & index );
	
signals:
	void sigIndex( const QModelIndex & index );

protected slots:
	void sltSpellTriggered( QAction * action );

protected:
	NifModel * Nif;
	QPersistentModelIndex Index;
	QMap<QAction*,Spell*> Map;
	
	void newSpellRegistered( Spell * spell );
	void checkActions( const QModelIndex & index, QMenu * menu, const QString & page );
	
private:
	static QList<Spell*> spells;
	static QList<SpellBook*> books;
};

class Librarian
{
public:
	Librarian( Spell * spell )
	{
		SpellBook::registerSpell( spell );
	}
};

#endif
