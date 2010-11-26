/*********************************************************\
 *  File: SNMPostProcessSepia.cpp                        *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Material/Parameter.h>
#include <PLCompositing/Shaders/PostProcessing/PostProcessManager.h>
#include "PLPostProcessEffects/SNMPostProcessSepia.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessSepia)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessSepia::SNMPostProcessSepia(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	Desat(this),
	Toned(this),
	LightColor(this),
	DarkColor(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/Sepia.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessSepia::~SNMPostProcessSepia()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessSepia::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // Desat
		Parameter *pParameter = GetParameter("Desat");
		if (pParameter)
			pParameter->SetValue1f(Desat.Get());
	}

	{ // Toned
		Parameter *pParameter = GetParameter("Toned");
		if (pParameter)
			pParameter->SetValue1f(Toned.Get());
	}

	{ // LightColor
		Parameter *pParameter = GetParameter("LightColor");
		if (pParameter)
			pParameter->SetValue3fv(LightColor.Get());
	}
	
	{ // DarkColor
		Parameter *pParameter = GetParameter("DarkColor");
		if (pParameter)
			pParameter->SetValue3fv(DarkColor.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
