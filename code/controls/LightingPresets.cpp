/*
 Copyright (C) 2009-2011 wxLauncher Team
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "controls/LightingPresets.h"

#include "apis/CmdLineManager.h"
#include "apis/ProfileManager.h"

#include "global/ids.h"
#include "global/MemoryDebugging.h"

#include <wx/gbsizer.h>
#include <wx/hyperlink.h>

Preset::Preset(const wxString& name, const int buttonId, const wxString& preset):
	name(name), buttonId(buttonId), preset(preset) {
}

const int DEFAULT_PRESET_ID = ID_PRESETS_OFF;
PresetHashMap LightingPresets::presets;

LightingPresets::LightingPresets(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
	if (presets.size() == 0) {
		InitializePresets();
	}
	
	wxStaticBox* lightingPresetsBox = new wxStaticBox(this, wxID_ANY, _("Lighting presets"));
	
	wxHyperlinkCtrl* presetDescsUrl =
		new wxHyperlinkCtrl(this, wxID_ANY, _T("Preset descriptions"),
							_T("http://www.hard-light.net/wiki/index.php/Sample_Lighting_Settings"));
	wxButton* customFlagsCopyButton =
		new wxButton(this, ID_COPY_PRESET_BUTTON, _T("Copy selected preset's settings to custom flags"));
	wxRadioButton* radioButton1 = new wxRadioButton (this, ID_PRESETS_OFF, _T("Presets off"),
													 wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	wxRadioButton* radioButton2 = new wxRadioButton (this, ID_PRESET_BASELINE, _T("Baseline recommended"));
	wxRadioButton* radioButton3 = new wxRadioButton (this, ID_PRESET_DABRAIN, _T("DaBrain's"));
	wxRadioButton* radioButton4 = new wxRadioButton (this, ID_PRESET_HERRA_TOHTORI, _T("Herra Tohtori's"));
	wxRadioButton* radioButton5 = new wxRadioButton (this, ID_PRESET_CKID, _T("CKid's"));
	wxRadioButton* radioButton6 = new wxRadioButton (this, ID_PRESET_COLECAMPBELL666, _T("ColeCampbell666's"));
	wxRadioButton* radioButton7 = new wxRadioButton (this, ID_PRESET_CASTOR, _T("Castor's"));
	wxRadioButton* radioButton8 = new wxRadioButton (this, ID_PRESET_SPIDEY, _T("Spidey's"));

	this->Initialize();

	wxGridBagSizer* lightingInsideSizer = new wxGridBagSizer();
	lightingInsideSizer->Add(presetDescsUrl, wxGBPosition(0,0), wxGBSpan(1,1),
							 wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT, 5);
	lightingInsideSizer->Add(customFlagsCopyButton, wxGBPosition(0,1), wxGBSpan(1,3),
							 wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 10);
	lightingInsideSizer->Add(radioButton1, wxGBPosition(1,0), wxGBSpan(1,1),
							 wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5);
	lightingInsideSizer->Add(radioButton2, wxGBPosition(2,0), wxGBSpan(1,1),
							 wxEXPAND|wxALIGN_CENTER_VERTICAL|wxRIGHT, 5);
	lightingInsideSizer->Add(radioButton3, wxGBPosition(1,1), wxGBSpan(1,1),
							 wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5);
	lightingInsideSizer->Add(radioButton4, wxGBPosition(2,1), wxGBSpan(1,1),
							 wxEXPAND|wxALIGN_CENTER_VERTICAL|wxRIGHT, 5);
	lightingInsideSizer->Add(radioButton5, wxGBPosition(1,2), wxGBSpan(1,1),
							 wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5);
	lightingInsideSizer->Add(radioButton6, wxGBPosition(2,2), wxGBSpan(1,1), 
							 wxEXPAND|wxALIGN_CENTER_VERTICAL|wxRIGHT, 5);
	lightingInsideSizer->Add(radioButton7, wxGBPosition(1,3), wxGBSpan(1,1),
							 wxEXPAND|wxALIGN_CENTER_VERTICAL|wxBOTTOM, 5);
	lightingInsideSizer->Add(radioButton8, wxGBPosition(2,3), wxGBSpan(1,1),
							 wxEXPAND|wxALIGN_CENTER_VERTICAL);
	
	wxStaticBoxSizer* lightingPresetsSizer = new wxStaticBoxSizer(lightingPresetsBox, wxHORIZONTAL);
	lightingPresetsSizer->Add(lightingInsideSizer, wxSizerFlags().Expand().Border(wxALL, 5));
	
	this->SetSizer(lightingPresetsSizer);
}

void LightingPresets::InitializePresets() {
	presets[ID_PRESETS_OFF] = Preset(_T("Off"), ID_PRESETS_OFF, wxEmptyString);
	presets[ID_PRESET_BASELINE] =
		Preset(_T("BaselineRecommended"), ID_PRESET_BASELINE,
			   _T("-ambient_factor 75 -spec_exp 11 -spec_point 0.6 -spec_static 0.8 -spec_tube 0.4 -ogl_spec 60"));
	presets[ID_PRESET_DABRAIN] =
		Preset(_T("DaBrain"), ID_PRESET_DABRAIN,
			   _T("-ambient_factor 10 -no_emissive_light -spec_exp 7.0 -spec_point 8.6 -spec_static 12.8 -spec_tube 5.0"));
	presets[ID_PRESET_HERRA_TOHTORI] =
		Preset(_T("HerraTohtori"), ID_PRESET_HERRA_TOHTORI,
			   _T("-ambient_factor 35 -no_emissive_light -spec_exp 15 -spec_point 1.2 -spec_static 1.5 -spec_tube 1.5 -ogl_spec 20"));
	presets[ID_PRESET_CKID] =
		Preset(_T("CKid"), ID_PRESET_CKID,
			   _T("-ambient_factor 35 -no_emissive_light -spec_exp 16.7 -spec_point 0.6 -spec_static 0.9 -spec_tube 1"));
	presets[ID_PRESET_COLECAMPBELL666] =
		Preset(_T("ColeCampbell666"), ID_PRESET_COLECAMPBELL666,
			   _T("-ambient_factor 0 -no_emissive_light -spec_exp 11 -spec_point .6 -spec_static .8 -spec_tube .4 -ogl_spec 80"));
	presets[ID_PRESET_CASTOR] =
		Preset(_T("Castor"), ID_PRESET_CASTOR,
			   _T("-ambient_factor 75 -spec_exp 7.0 -spec_point 8.6 -spec_static 3.0 -spec_tube 5.0"));
	presets[ID_PRESET_SPIDEY] =
		Preset(_T("Spidey"), ID_PRESET_SPIDEY,
			   _T("-ambient_factor 5 -spec_exp 15 -spec_point 1.2 -spec_static 1.7 -spec_tube 1.5 -ogl_spec 50"));
}

BEGIN_EVENT_TABLE(LightingPresets, wxPanel)
EVT_BUTTON(ID_COPY_PRESET_BUTTON, LightingPresets::OnCopyLightingPreset)
EVT_RADIOBUTTON(ID_PRESETS_OFF, LightingPresets::OnSelectLightingPreset)
EVT_RADIOBUTTON(ID_PRESET_BASELINE, LightingPresets::OnSelectLightingPreset)
EVT_RADIOBUTTON(ID_PRESET_DABRAIN, LightingPresets::OnSelectLightingPreset)
EVT_RADIOBUTTON(ID_PRESET_HERRA_TOHTORI, LightingPresets::OnSelectLightingPreset)
EVT_RADIOBUTTON(ID_PRESET_CKID, LightingPresets::OnSelectLightingPreset)
EVT_RADIOBUTTON(ID_PRESET_COLECAMPBELL666, LightingPresets::OnSelectLightingPreset)
EVT_RADIOBUTTON(ID_PRESET_CASTOR, LightingPresets::OnSelectLightingPreset)
EVT_RADIOBUTTON(ID_PRESET_SPIDEY, LightingPresets::OnSelectLightingPreset)
END_EVENT_TABLE()

void LightingPresets::OnSelectLightingPreset(wxCommandEvent &event) {
	int id = event.GetId();
	const wxString& presetName = PresetButtonIdToPresetName(id);
	
	wxLogDebug(_T("lighting preset %s selected"), presetName.c_str());
	
	wxButton* copyPresetButton =
		dynamic_cast<wxButton*>(wxWindow::FindWindowById(ID_COPY_PRESET_BUTTON, this));
	wxCHECK_RET( copyPresetButton != NULL, _T("Unable to find copy lighting preset button"));
	
	if (id == ID_PRESETS_OFF) {
		copyPresetButton->Disable();
	} else {
		copyPresetButton->Enable();
	}
	
	ProMan::GetProfileManager()->Get()->Write(PRO_CFG_LIGHTING_PRESET, presetName);
	CmdLineManager::GenerateCmdLineChanged();
}

void LightingPresets::OnCopyLightingPreset(wxCommandEvent &WXUNUSED(event)) {
	wxString presetName;
	wxCHECK_RET(ProMan::GetProfileManager()->Get()->Read(PRO_CFG_LIGHTING_PRESET, &presetName),
				_T("copy lighting preset button pressed with no preset stored in profile"));

	wxCHECK_RET(presetName != presets[ID_PRESETS_OFF].GetName(),
				_T("copy lighting preset button pressed when 'presets off' is selected"));

	wxLogDebug(_T("attempting to copy preset named %s to custom flags"), presetName.c_str());
	
	wxString flagLine;

	ProMan::GetProfileManager()->Get()->Read(PRO_CFG_TC_CURRENT_FLAG_LINE, &flagLine);
	flagLine.Append(_T(" ")).Append(PresetNameToPresetString(presetName));
	ProMan::GetProfileManager()->Get()->Write(PRO_CFG_TC_CURRENT_FLAG_LINE, flagLine);
	CmdLineManager::GenerateCustomFlagsChanged();

	this->Reset();
}

const wxString& LightingPresets::PresetNameToPresetString(const wxString& presetName) {
	for (PresetHashMap::iterator it = presets.begin(), end = presets.end(); it != end; ++it) {
		if (it->second.GetName() == presetName) {
			return it->second.GetPreset();
		}
	}
	
	wxLogWarning(_T("PresetNameToPresetString: unknown preset name %s, returning default (off)"), presetName.c_str());
	return presets[DEFAULT_PRESET_ID].GetPreset();
}
	
void LightingPresets::Initialize() {
	wxString presetName;
	int presetButtonId;
	
	if (ProMan::GetProfileManager()->Get()->Read(PRO_CFG_LIGHTING_PRESET, &presetName)) {
		presetButtonId = PresetNameToPresetButtonId(presetName);
	} else {
		presetButtonId = DEFAULT_PRESET_ID;
	}

	wxRadioButton *selectedPresetButton =
		dynamic_cast<wxRadioButton*>(wxWindow::FindWindowById(presetButtonId, this));
	wxCHECK_RET( selectedPresetButton != NULL, _T("Cannot find selected preset button"));
	selectedPresetButton->SetValue(true);

	wxCommandEvent presetSelectionEvent(wxEVT_COMMAND_RADIOBUTTON_SELECTED, presetButtonId);
	this->OnSelectLightingPreset(presetSelectionEvent);
}

void LightingPresets::Reset() {
	wxRadioButton* presetsOffButton =
		dynamic_cast<wxRadioButton*>(wxWindow::FindWindowById(ID_PRESETS_OFF, this));
	wxCHECK_RET( presetsOffButton != NULL, _T("Unable to find lighting presets off radio button"));
	presetsOffButton->SetValue(true);
	
	wxCommandEvent resetEvent(wxEVT_COMMAND_RADIOBUTTON_SELECTED, ID_PRESETS_OFF);
	this->OnSelectLightingPreset(resetEvent);
}

int LightingPresets::PresetNameToPresetButtonId(const wxString& presetName) {
	for (PresetHashMap::iterator it = presets.begin(), end = presets.end(); it != end; ++it) {
		if (it->second.GetName() == presetName) {
			return it->second.GetButtonId();
		}
	}
	
	wxLogWarning(_T("PresetNameToPresetButtonId: unknown preset name %s, returning default (off)"), presetName.c_str());
	return DEFAULT_PRESET_ID;
}

const wxString& LightingPresets::PresetButtonIdToPresetName(int buttonId) {
	PresetHashMap::iterator it = presets.find(buttonId);
	
	wxCHECK_MSG(it != presets.end(), presets[DEFAULT_PRESET_ID].GetName(),
		wxString::Format(_T("PresetButtonIdToPresetName given invalid button ID %d"), buttonId));
	
	return it->second.GetName();
}