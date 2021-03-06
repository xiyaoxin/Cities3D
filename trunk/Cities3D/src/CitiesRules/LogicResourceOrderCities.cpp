/*
 *  Cities3D - Copyright (C) 2001-2009 Jason Fugate (saladyears@gmail.com)
 * 
 *  This program is free software; you can redistribute it and/or modify it 
 *  under the terms of the GNU General Public License as published by the Free 
 *  Software Foundation; either version 2 of the License, or (at your option) 
 *  any later version.
 * 
 *  This program is distributed in the hope that it will be useful, but 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 *  for more details.
 */
#include "stdwx.h"
#include "style.h"	//READ THIS BEFORE MAKING ANY CHANGES TO THIS FILE!!!

//---------------------------- SYSTEM INCLUDES  -----------------------------//

//---------------------------- USER INCLUDES    -----------------------------//
#include "Logic.h"
#include "RuleSetDatabase.h"

//---------------------------- TYPEDEFS         -----------------------------//
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//---------------------------- STATICS          -----------------------------//

//---------------------------- LOGIC            -----------------------------//

//---------------------------------------------------------------------------//
// Class: LogicResourceOrderCities
// 
// Provides resource ordering for C&K resources.
//
// Derived From:
//     <Logic>
//
// Project:
//     <CitiesRules>
//
// RuleSet:
//     <Cities>
//
// Mixin To:
//     <LogicResourceOrder>
//

// Cloth.

class LogicResourceOrderCloth : public Logic
{
public:
	virtual void Decide(const DataObject &, DataObject &output)
	{
		output = DataObject(10);
	}
};

IMPLEMENT_LOGIC_KEYED_MIXIN(LogicResourceOrderCloth, Cloth, 
							LogicResourceOrder, CITIES);


// Coin.

class LogicResourceOrderCoin : public Logic
{
public:
	virtual void Decide(const DataObject &, DataObject &output)
	{
		output = DataObject(11);
	}
};

IMPLEMENT_LOGIC_KEYED_MIXIN(LogicResourceOrderCoin, Coin, 
							LogicResourceOrder, CITIES);

// Paper.

class LogicResourceOrderPaper : public Logic
{
public:
	virtual void Decide(const DataObject &, DataObject &output)
	{
		output = DataObject(12);
	}
};

IMPLEMENT_LOGIC_KEYED_MIXIN(LogicResourceOrderPaper, Paper, 
							LogicResourceOrder, CITIES);
