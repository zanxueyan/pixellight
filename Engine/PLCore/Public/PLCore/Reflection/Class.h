/*********************************************************\
 *  File: Rtti.h                                         *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLCORE_REFL_CLASS_H__
#define __PLCORE_REFL_CLASS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "TypeId.h"
#include "ClassMethod.h"
#include "ClassField.h"
#include "ClassProperty.h"
#include <PLCore/String/String.h>
#include <PLCore/Container/HashMap.h>
#include <PLCore/Container/Array.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRefl {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <typename T>
class ClassBuilder;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    The reflection system's representation of a class type
*
*  @remarks
*    TODO: describe this in more detail
*/
class Class {

	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	template <typename T>
	friend class ClassBuilder;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Start the construction of a new class definition
		*
		*  @param[in] sName
		*    The name of the new class in the reflection system. This can be different from the real
		*    C++ class name
		*/
		template <typename T>
		static ClassBuilder<T> Declare(const PLCore::String &sName);

		/**
		*  @brief
		*    Find a method by name on this class
		*
		*  @param[in] sName
		*    The name of the method to look for
		*
		*  @return
		*    Pointer to ClassMethod instance representing the method or nullptr if it was not found
		*/
		PLCORE_API const ClassMethod *GetMethod(const PLCore::String &sName) const;

		/**
		*  @brief
		*    Find a field by name on this class
		*
		*  @param[in] sName
		*    The name of the field to look for
		*
		*  @return
		*    Pointer to ClassField instance representing the field or nullptr if it was not found
		*/
		PLCORE_API const ClassField *GetField(const PLCore::String &sName) const;

		/**
		*  @brief
		*    Find a property by name on this class
		*
		*  @param[in] sName
		*    The name of the property to look for
		*
		*  @return
		*    Pointer to ClassProperty instance representing the property or nullptr if it was not found
		*/
		PLCORE_API const ClassProperty *GetProperty(const PLCore::String &sName) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		typedef PLCore::HashMap<PLCore::String, ClassMethod> _MethodMap;
		_MethodMap m_mapMethods;		/**< Methods for this class */

		typedef PLCore::HashMap<PLCore::String, ClassField> _FieldMap;
		_FieldMap m_mapFields;			/**< Fields for this class */

		typedef PLCore::HashMap<PLCore::String, ClassProperty> _PropertyMap;
		_PropertyMap m_mapProperties;	/**< Properties for this class */

		typedef PLCore::Array<const Class*> _BaseClasses;
		_BaseClasses m_lstBases;		/**< Base classes */
};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRefl


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "ClassBuilder.h"
#include "Class.inl"


#endif // __PLCORE_REFL_CLASS_H__
