/*********************************************************\
 *  File: SNMPostProcessChalk.cpp                        *
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
#include "PLPostProcessEffects/SNMPostProcessChalk.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPostProcessChalk)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessChalk::SNMPostProcessChalk(PLScene::SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	ColorScale(this),
	PixelKernel0(this),
	PixelKernel1(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/Chalk.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessChalk::~SNMPostProcessChalk()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessChalk::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // ColorScale
		Parameter *pParameter = GetParameter("ColorScale");
		if (pParameter)
			pParameter->SetValue2fv(ColorScale.Get());
	}

	{ // PixelKernel[0]
		Parameter *pParameter = GetParameter("PixelKernel[0]");
		if (pParameter)
			pParameter->SetValue2fv(PixelKernel0.Get());
	}

	{ // PixelKernel[1]
		Parameter *pParameter = GetParameter("PixelKernel[1]");
		if (pParameter)
			pParameter->SetValue2fv(PixelKernel1.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
