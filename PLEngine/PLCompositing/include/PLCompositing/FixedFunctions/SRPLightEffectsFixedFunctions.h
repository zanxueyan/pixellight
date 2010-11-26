/*********************************************************\
 *  File: SRPLightEffectsFixedFunctions.h                *
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


#ifndef __PLCOMPOSITING_FIXEDFUNCTIONS_LIGHTEFFECTS_H__
#define __PLCOMPOSITING_FIXEDFUNCTIONS_LIGHTEFFECTS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Pool.h>
#include "PLCompositing/SRPLightEffects.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class VertexBuffer;
	class OcclusionQuery;
}
namespace PLScene {
	class VisNode;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Fixed functions based scene renderer pass drawing light effects like lens flares
*/
class SRPLightEffectsFixedFunctions : public SRPLightEffects {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPLightEffectsFixedFunctions, "PLCompositing", PLCompositing::SRPLightEffects, "Fixed functions based scene renderer pass drawing light effects like lens flares")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPLightEffectsFixedFunctions();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPLightEffectsFixedFunctions();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Prepares light effects recursive
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*  @param[in] cCullQuery
		*    Cull query to use
		*/
		void PrepareRec(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);

		/**
		*  @brief
		*    Frees all light effects
		*/
		void FreeLightEffects();

		/**
		*  @brief
		*    Draws a light effect flare
		*
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] fP
		*    Position. 1.0f is where the light is, -1.0f is the opposite side
		*  @param[in] fS
		*    Size. 1.0f will fill the screen when looking right at the light
		*  @param[in] fR
		*    Red color component of the flare
		*  @param[in] fG
		*    Green color component of the flare
		*  @param[in] fB
		*    Blue color component of the flare
		*  @param[in] fA
		*    Alpha color component of the flare
		*  @param[in] v2DPos
		*    2D screen position of the light
		*/
		void DrawFlare(PLRenderer::Renderer &cRenderer, float fP, float fS, float fR, float fG,
					   float fB, float fA, const PLMath::Vector3 &v2DPos) const;

		/**
		*  @brief
		*    Draws a simple billboard
		*
		*  param[in] vPos
		*    Billboard position
		*  param[in] fSize
		*    Billboard size
		*
		*  @remarks
		*    A billboard will always 'look into the camera'. The position is normally in world space.
		*    The world matrix of the renderer should be an identity matrix.
		*/
		void DrawBillboard(const PLMath::Vector3 &vPos, float fSize);

		/**
		*  @brief
		*    Draws a simple billboard
		*
		*  param[in] vPos
		*    Billboard position
		*  param[in] fSize
		*    Billboard size
		*  param[in] cColor
		*    Billboard color
		*
		*  @see
		*    - DrawBillboard() above
		*/
		void DrawBillboard(const PLMath::Vector3 &vPos, float fSize, const PLGraphics::Color4 &cColor);


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal prepared light effect
		*/
		struct LightEffect {
			const PLScene::VisNode	   *pVisNode;			/**< ALWAYS valid! */
			PLRenderer::OcclusionQuery *pOcclusionQueryAll;	/**< Can be NULL */
			PLRenderer::OcclusionQuery *pOcclusionQuery;	/**< Can be NULL */
			float						fFactor;			/**< Factor */
			float						fFlareBlendFactor;	/**< Factor for flares & blend */
			PLMath::Vector3				v2DPos;				/**< 2D screen position (-1 to 1) */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::VertexBuffer	  *m_pBillboardVB;			/**< Billbord vertex buffer, can be NULL */
		PLRenderer::VertexBuffer	  *m_pBillboardColorVB;		/**< Billbord vertex buffer with color support, can be NULL */
		PLGeneral::Pool<LightEffect*>  m_lstLightEffects;		/**< List of used light effects */
		PLGeneral::Pool<LightEffect*>  m_lstFreeLightEffects;	/**< List of free light effects */


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);


	//[-------------------------------------------------------]
	//[ public virtual SRPLightEffects functions              ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API void Prepare(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_FIXEDFUNCTIONS_LIGHTEFFECTS_H__
