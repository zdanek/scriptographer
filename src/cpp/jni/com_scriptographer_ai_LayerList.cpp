/*
 * Scriptographer
 *
 * This file is part of Scriptographer, a Plugin for Adobe Illustrator.
 *
 * Copyright (c) 2002-2005 Juerg Lehni, http://www.scratchdisk.com.
 * All rights reserved.
 *
 * Please visit http://scriptographer.com/ for updates and contact.
 *
 * -- GPL LICENSE NOTICE --
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * -- GPL LICENSE NOTICE --
 *
 * $RCSfile: com_scriptographer_ai_LayerList.cpp,v $
 * $Author: lehni $
 * $Revision: 1.1 $
 * $Date: 2005/02/23 22:00:59 $
 */
 
#include "stdHeaders.h"
#include "ScriptographerEngine.h"
#include "Plugin.h"
#include "com_scriptographer_ai_LayerList.h"

/*
 * com.scriptographer.ai.LayerList
 */

/*
 * int getLength()
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_ai_LayerList_getLength(JNIEnv *env, jobject obj) {
	try {
		long count;
		sAILayer->CountLayers(&count);
		return count;
	} EXCEPTION_CONVERT(env)
	return 0;
}

/*
 * com.scriptographer.ai.Art get(int index)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_LayerList_get__I(JNIEnv *env, jobject obj, jint index) {
	try {
		AILayerHandle layer = NULL;
		sAILayer->GetNthLayer(index, &layer);
		if (layer != NULL)
			return gEngine->wrapLayerHandle(env, layer);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * com.scriptographer.ai.Art get(java.lang.String name)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_LayerList_get__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring name) {
	try {
		AILayerHandle layer = NULL;
		char *str = gEngine->createCString(env, name);
		sAILayer->GetLayerByTitle(&layer, gPlugin->toPascal(str, (unsigned char *) str));
		delete str;
		if (layer != NULL)
			return gEngine->wrapLayerHandle(env, layer);
	} EXCEPTION_CONVERT(env)
	return NULL;
}