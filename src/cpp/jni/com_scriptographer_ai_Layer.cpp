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
 * $RCSfile: com_scriptographer_ai_Layer.cpp,v $
 * $Author: lehni $
 * $Revision: 1.1 $
 * $Date: 2005/02/23 22:00:58 $
 */
 
#include "stdHeaders.h"
#include "ScriptographerEngine.h"
#include "Plugin.h"
#include "com_scriptographer_ai_Layer.h"

/*
 * com.scriptographer.ai.Layer
 */

// the creation of layers is handled in nativeCreateArt!

/*
 * void setVisible(boolean visible)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Layer_setVisible(JNIEnv *env, jobject obj, jboolean visible) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		sAILayer->SetLayerVisible(layer, visible);
	} EXCEPTION_CONVERT(env)
}

/*
 * boolean isVisible()
 */
JNIEXPORT jboolean JNICALL Java_com_scriptographer_ai_Layer_isVisible(JNIEnv *env, jobject obj) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		AIBoolean visible;
		if (!sAILayer->GetLayerVisible(layer, &visible)) {
			return visible;	
		}
	} EXCEPTION_CONVERT(env)
	return JNI_FALSE;
}

/*
 * void setPreview(boolean preview)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Layer_setPreview(JNIEnv *env, jobject obj, jboolean preview) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		sAILayer->SetLayerPreview(layer, preview);
	} EXCEPTION_CONVERT(env)
}

/*
 * boolean getPreview()
 */
JNIEXPORT jboolean JNICALL Java_com_scriptographer_ai_Layer_getPreview(JNIEnv *env, jobject obj) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		AIBoolean preview;
		if (!sAILayer->GetLayerPreview(layer, &preview)) {
			return preview;	
		}
	} EXCEPTION_CONVERT(env)
	return JNI_FALSE;
}

/*
 * void setEditable(boolean editable)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Layer_setEditable(JNIEnv *env, jobject obj, jboolean editable) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		sAILayer->SetLayerEditable(layer, editable);
	} EXCEPTION_CONVERT(env)
}

/*
 * boolean isEditable()
 */
JNIEXPORT jboolean JNICALL Java_com_scriptographer_ai_Layer_isEditable(JNIEnv *env, jobject obj) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		AIBoolean editable;
		if (!sAILayer->GetLayerEditable(layer, &editable)) {
			return editable;	
		}
	} EXCEPTION_CONVERT(env)
	return JNI_FALSE;
}

/*
 * void setPrinted(boolean printed)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Layer_setPrinted(JNIEnv *env, jobject obj, jboolean printed) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		sAILayer->SetLayerPrinted(layer, printed);
	} EXCEPTION_CONVERT(env)
}

/*
 * boolean isPrinted()
 */
JNIEXPORT jboolean JNICALL Java_com_scriptographer_ai_Layer_isPrinted(JNIEnv *env, jobject obj) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		AIBoolean printed;
		if (!sAILayer->GetLayerPrinted(layer, &printed)) {
			return printed;	
		}
	} EXCEPTION_CONVERT(env)
	return JNI_FALSE;
}

/*
 * void setSelected(boolean selected)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Layer_setSelected(JNIEnv *env, jobject obj, jboolean selected) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		sAILayer->SetLayerSelected(layer, selected);
	} EXCEPTION_CONVERT(env)
}

/*
 * boolean isSelected()
 */
JNIEXPORT jboolean JNICALL Java_com_scriptographer_ai_Layer_isSelected(JNIEnv *env, jobject obj) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		AIBoolean selected;
		if (!sAILayer->GetLayerSelected(layer, &selected)) {
			return selected;	
		}
	} EXCEPTION_CONVERT(env)
	return JNI_FALSE;
}

/*
 * void setColor(com.scriptographer.Color color)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Layer_setColor(JNIEnv *env, jobject obj, jobject color) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		AIColor aiColor;
		gEngine->convertColor(env, color, &aiColor);
		AIRGBColor rgbColor;
		gEngine->convertColor(&aiColor, &rgbColor);
		sAILayer->SetLayerColor(layer, rgbColor);
	} EXCEPTION_CONVERT(env)
}

/*
 * com.scriptographer.ai.RGBColor getColor()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_Layer_getColor(JNIEnv *env, jobject obj) {
	try {
		AILayerHandle layer = gEngine->getLayerHandle(env, obj);
		AIRGBColor rgbColor;
		if (!sAILayer->GetLayerColor(layer, &rgbColor)) {
			AIColor aiColor;
			gEngine->convertColor(&rgbColor, &aiColor);
			return gEngine->convertColor(env, &aiColor);
		}
	} EXCEPTION_CONVERT(env)
	return NULL;
}