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
#include "OptionDatabase.h"
#include "IOptionUI.h"

#include "Rule.h"
#include "RuleSetDatabase.h"

#include "IRuleEngine.h"
#include "DataObject.h"
#include "BaseStaticText.h"
#include "BaseComboBox.h"

//---------------------------- TYPEDEFS         -----------------------------//
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//---------------------------- STATICS          -----------------------------//
namespace
{
	long sRounds = 1;

	enum
	{
		ID_ROUNDS_COMBO			= 0,
	};

	const wxString sOptions_No7[] = {sw1, sw2};

	wxBaseStaticText* spText_No7 = NULL;
	wxBaseComboBox *spRoundsCombo = NULL;
}

//---------------------------- PUBLIC           -----------------------------//
class No7Option 
	: public wxEvtHandler
	, public IOptionUI
{
public:
	virtual void dependencies(StringPairArray&) const
	{
	}

	virtual void silent_dependencies(StringPairArray&) const
	{
	}

	virtual void exclusions(StringPairArray& ) const
	{
	}

	virtual const wxString& description() const
	{
		return stPrevent7s;
	}

	virtual wxInt32 priority() const
	{
		return 10;
	}

	virtual wxString short_description() const
	{
		wxString str;

		if(1 == sRounds)
		{
			str = stNo7sForOneRound;
		}
		else
		{
			str = wxString::Format(stNo7sForXRounds.c_str(), sRounds);
		}

		return str;
	}

	virtual bool HasUI() const
	{
		return true;
	}

	virtual void CreateUI(wxWindow* parent, wxSizer* sizer)
	{
		wxString init = wxString::Format(swIntFormat.c_str(), sRounds);

		wxBoxSizer *vert = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer *innerVert = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* innerHorz = new wxBoxSizer(wxHORIZONTAL);
		spText_No7 = new wxBaseStaticText(parent, -1, 
			stRoundsBeforeA7IsRolled + swColon);
		spRoundsCombo = new wxBaseComboBox(parent, ID_ROUNDS_COMBO, init, 
			wxDefaultPosition, wxDefaultSize, 2, sOptions_No7, wxCB_READONLY);
		
		innerVert->AddStretchSpacer();
		innerVert->Add(spText_No7);
		innerVert->AddStretchSpacer();
		innerHorz->Add(innerVert, 1, wxEXPAND | wxLEFT, 7);
		innerHorz->Add(spRoundsCombo, 0, wxEXPAND | wxLEFT | wxRIGHT, 7);
		vert->Add(innerHorz, 1, wxEXPAND);
		
		sizer->Add(vert, 0);

		parent->Connect(ID_ROUNDS_COMBO, ID_ROUNDS_COMBO, 
			wxEVT_COMMAND_COMBOBOX_SELECTED, 
			wxCommandEventHandler(No7Option::OnRoundsCombo));
	}

	virtual void DestroyUI(wxWindow* parent, wxSizer* sizer)
	{
		parent->Disconnect(ID_ROUNDS_COMBO, ID_ROUNDS_COMBO, 
			wxEVT_COMMAND_COMBOBOX_SELECTED, 
			wxCommandEventHandler(No7Option::OnRoundsCombo));

		sizer->Remove(0);

		spText_No7->Destroy();
		spText_No7 = NULL;

		spRoundsCombo->Destroy();
		spRoundsCombo = NULL;
	}

	virtual void UpdateUI(const wxString& key, const wxString& value)
	{
		wxASSERT(swRounds == key);

		value.ToLong(&sRounds);
	}

	void OnRoundsCombo(wxCommandEvent &)
	{
		wxInt32 sel = spRoundsCombo->GetSelection();
		wxASSERT(-1 != sel);

		wxString str = spRoundsCombo->GetString(sel);
		
		Controller::get().Transmit(shEventUpdateOption, 
			DataObject(swRounds, str));
	}

	virtual void SaveToXML(wxXmlNode* node)
	{
		wxXmlNode* child = new wxXmlNode(node, wxXML_ELEMENT_NODE,
			swRounds);
		child->AddProperty(swValue, wxString::Format(swIntFormat.c_str(), 
            sRounds));
	}

	virtual void LoadFromXML(const wxString& option, wxXmlNode* node)
	{
		wxXmlNode* child = node->GetChildren();
		wxString value;

		if( (swRounds == child->GetName()) &&
			(true == child->GetPropVal(swValue, &value)))
		{
			RULE.Execute(shRuleSilentUpdateOption, DataObject(option,
				swRounds, value));
		}
	}
};

IMPLEMENT_OPTION_UI(NO7S, No7Option);

//---------------------------------------------------------------------------//
// Class: RuleInitializeNo7s
// 
// Initializes no sevens data.
//
// Derived From:
//     <Rule>
//
// Project:
//     <StandardRules>
//
// RuleSet:
//     <No7s>
//
// Mixin To:
//     <RuleInitializeOptions>
//
class RuleInitializeNo7s : public Rule
{
public:
	virtual void Execute(const DataObject &)
	{
		gameData<wxInt32>(shNo7Rounds) = sRounds;
	}
};

IMPLEMENT_RULE_MIXIN(RuleInitializeNo7s, RuleInitializeOptions, NO7S)

//---------------------------- PROTECTED        -----------------------------//

//---------------------------- PRIVATE          -----------------------------//
