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
 * $RCSfile: com_scriptographer_ai_Document.cpp,v $
 * $Author: lehni $
 * $Revision: 1.1 $
 * $Date: 2005/02/23 22:00:59 $
 */
 
#include "stdHeaders.h"
#include "ScriptographerEngine.h"
#include "Plugin.h"
#include "aiGlobals.h"
#include "com_scriptographer_ai_Document.h"

/*
 * com.scriptographer.ai.Document
 */

// documentStart and documentStop are necessary because only the active document
// can be accessed and modified throught sAIDocument. it seems like adobe forgot
// tu use the AIDocumentHandle parameter there...

#define DOCUMENT_BEGIN \
	AIDocumentHandle activeDoc = NULL; \
	AIDocumentHandle prevDoc = NULL; \
	try { \
		AIDocumentHandle doc = gEngine->getDocumentHandle(env, obj); \
		sAIDocument->GetDocument(&activeDoc); \
		if (activeDoc != doc) { \
			prevDoc = activeDoc; \
			sAIDocumentList->Activate(doc, false); \
		} \

#define DOCUMENT_END \
	} EXCEPTION_CONVERT(env) \
	if (prevDoc != NULL) \
		sAIDocumentList->Activate(prevDoc, false);
	
/*
 * int nativeCreate(java.io.File file, int colorModel, int dialogStatus)
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_ai_Document_nativeCreate__Ljava_io_File_2II(JNIEnv *env, jobject obj, jobject file, jint colorModel, jint dialogStatus) {
	char *str = NULL;
	AIDocumentHandle doc = NULL;
	try {
		jstring path = (jstring) gEngine->callObjectMethod(env, file, gEngine->mid_File_getPath);
		str = gEngine->createCString(env, path);
		SPPlatformFileSpecification fileSpec;
		if (gPlugin->pathToFileSpec(str, &fileSpec)) {
			sAIDocumentList->Open(&fileSpec, (AIColorModel) colorModel, (ActionDialogStatus) dialogStatus, &doc);
		}		
	} EXCEPTION_CONVERT(env)
	if (str != NULL)
		delete str;
	return (jint) doc;
}

/*
 * int nativeCreate(java.lang.String title, float width, float height, int colorModel, int dialogStatus)
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_ai_Document_nativeCreate__Ljava_lang_String_2FFII(JNIEnv *env, jobject obj, jstring title, jfloat width, jfloat height, jint colorModel, jint dialogStatus) {
	char *str = NULL;
	AIDocumentHandle doc = NULL;
	try {
		str = gEngine->createCString(env, title);
		AIColorModel model = (AIColorModel) colorModel;
		sAIDocumentList->New(str, &model, &width, &height, (ActionDialogStatus) dialogStatus, &doc);
	} EXCEPTION_CONVERT(env)
	if (str != NULL)
		delete str;
	return (jint) doc;
}

/*
 * com.scriptographer.ai.Point getPageOrigin()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_Document_getPageOrigin(JNIEnv *env, jobject obj) {
	jobject origin = NULL;
	DOCUMENT_BEGIN

	AIRealPoint pt;
	sAIDocument->GetDocumentPageOrigin(&pt);
	origin = gEngine->convertPoint(env, &pt);

	DOCUMENT_END
	return origin;
}

/*
 * void setPageOrigin(com.scriptographer.ai.Point origin)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_setPageOrigin(JNIEnv *env, jobject obj, jobject origin) {
	DOCUMENT_BEGIN
		
	AIRealPoint pt;
	gEngine->convertPoint(env, origin, &pt);
	sAIDocument->SetDocumentPageOrigin(&pt);

	DOCUMENT_END
}

/*
 * com.scriptographer.ai.Point getRulerOrigin()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_Document_getRulerOrigin(JNIEnv *env, jobject obj) {
	jobject origin = NULL;

	DOCUMENT_BEGIN

	AIRealPoint pt;
	sAIDocument->GetDocumentRulerOrigin(&pt);
	origin = gEngine->convertPoint(env, &pt);

	DOCUMENT_END

	return origin;
}

/*
 * void setRulerOrigin(com.scriptographer.ai.Point origin)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_setRulerOrigin(JNIEnv *env, jobject obj, jobject origin) {
	DOCUMENT_BEGIN

	AIRealPoint pt;
	gEngine->convertPoint(env, origin, &pt);
	sAIDocument->SetDocumentRulerOrigin(&pt);

	DOCUMENT_END
}

/*
 * com.scriptographer.ai.Point getSize()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_Document_getSize(JNIEnv *env, jobject obj) {
	jobject size = NULL;

	DOCUMENT_BEGIN

	AIDocumentSetup setup;
	sAIDocument->GetDocumentSetup(&setup);
	DEFINE_POINT(pt, setup.width, setup.height);
	size = gEngine->convertPoint(env, &pt);

	DOCUMENT_END

	return size;
}

/*
 * void setSize(float width, float height)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_setSize(JNIEnv *env, jobject obj, jfloat width, jfloat height) {
	DOCUMENT_BEGIN

	AIDocumentSetup setup;
	sAIDocument->GetDocumentSetup(&setup);
	setup.width = width;
	setup.height = height;
	sAIDocument->SetDocumentSetup(&setup);

	DOCUMENT_END
}

/*
 * com.scriptographer.ai.Rectangle getCropBox()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_Document_getCropBox(JNIEnv *env, jobject obj) {
	jobject cropBox = NULL;

	DOCUMENT_BEGIN

	AIRealRect rt;
	sAIDocument->GetDocumentCropBox(&rt);
	cropBox = gEngine->convertRectangle(env, &rt);

	DOCUMENT_END
	
	return cropBox;
}

/*
 * void setCropBox(com.scriptographer.ai.Rectangle cropBox)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_setCropBox(JNIEnv *env, jobject obj, jobject cropBox) {
	DOCUMENT_BEGIN

	AIRealRect rt;
	gEngine->convertRectangle(env, cropBox, &rt);
	sAIDocument->SetDocumentCropBox(&rt);

	DOCUMENT_END
}

/*
 * boolean isModified()
 */
JNIEXPORT jboolean JNICALL Java_com_scriptographer_ai_Document_isModified(JNIEnv *env, jobject obj) {
	jboolean modified = false;
	
	DOCUMENT_BEGIN
	
	sAIDocument->GetDocumentModified(&modified);
	
	DOCUMENT_END
	
	return modified;
}

/*
 * void setModified(boolean modified)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_setModified(JNIEnv *env, jobject obj, jboolean modified) {
	DOCUMENT_BEGIN
	
	sAIDocument->SetDocumentModified(modified);

	DOCUMENT_END
}

/*
 * java.io.File getFile()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_Document_getFile(JNIEnv *env, jobject obj) {
	jobject file = NULL;
	
	DOCUMENT_BEGIN
	
	SPPlatformFileSpecification fileSpec;
	sAIDocument->GetDocumentFileSpecification(&fileSpec);
	char path[kMaxPathLength];
	if (gPlugin->fileSpecToPath(&fileSpec, path)) {
		file = env->NewObject(gEngine->cls_File, gEngine->cid_File, gEngine->createJString(env, path));
	}
	
	DOCUMENT_END
	
	return file;
}

/*
 * java.lang.String[] nativeGetFormats()
 */
JNIEXPORT jobjectArray JNICALL Java_com_scriptographer_ai_Document_nativeGetFormats(JNIEnv *env, jclass cls) {
	try {
		long count;
		sAIFileFormat->CountFileFormats(&count);
		jobjectArray array = env->NewObjectArray(count, gEngine->cls_String, NULL); 
		for (int i = 0; i < count; i++) {
			AIFileFormatHandle fileFormat = NULL;
			sAIFileFormat->GetNthFileFormat(i, &fileFormat);
			if (fileFormat != NULL) {
				char *name = NULL;
				sAIFileFormat->GetFileFormatName(fileFormat, &name);
				if (name != NULL) {
					env->SetObjectArrayElement(array, i, gEngine->createJString(env, name));
				}
			}
		}
		return array;
	} EXCEPTION_CONVERT(env)
	return NULL;
}


/*
 * void activate()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_activate(JNIEnv *env, jobject obj) {
	try {
		AIDocumentHandle doc = gEngine->getDocumentHandle(env, obj);
		sAIDocumentList->Activate(doc, true);
	} EXCEPTION_CONVERT(env)
}

/*
 * void print(int dialogStatus)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_print(JNIEnv *env, jobject obj, jint dialogStatus) {
	try {
		AIDocumentHandle doc = gEngine->getDocumentHandle(env, obj);
		sAIDocumentList->Print(doc, (ActionDialogStatus) dialogStatus);
	} EXCEPTION_CONVERT(env)
}

/*
 * void save()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_save(JNIEnv *env, jobject obj) {
	try {
		AIDocumentHandle doc = gEngine->getDocumentHandle(env, obj);
		sAIDocumentList->Save(doc);
	} EXCEPTION_CONVERT(env)
}

/*
 * boolean write(java.io.File file, Ljava.lang.String format, boolean ask)
 */
JNIEXPORT jboolean JNICALL Java_com_scriptographer_ai_Document_write(JNIEnv *env, jobject obj, jobject fileObj, jstring formatObj, jboolean ask) {
	jboolean ret = false;
	char *path = NULL;
	char *format = NULL;
	
	DOCUMENT_BEGIN
	
	jstring pathObj = (jstring) gEngine->callObjectMethod(env, fileObj, gEngine->mid_File_getPath);
	path = gEngine->createCString(env, pathObj);
	if (formatObj == NULL) format = "Adobe Illustrator Any Format Writer";
	else format = gEngine->createCString(env, formatObj);
	SPPlatformFileSpecification fileSpec;
	if (gPlugin->pathToFileSpec(path, &fileSpec)) {
		ret = !sAIDocument->WriteDocument(&fileSpec, format, ask);
	}
	
	DOCUMENT_END

	if (path != NULL)
		delete path;
	if (format != NULL && formatObj != NULL)
		delete format;

	return ret;
}

/*
 * void close()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_close(JNIEnv *env, jobject obj) {
	try {
		AIDocumentHandle doc = gEngine->getDocumentHandle(env, obj);
		sAIDocumentList->Close(doc);
	} EXCEPTION_CONVERT(env)
}

/*
 * void redraw()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_redraw(JNIEnv *env, jobject obj) {
	DOCUMENT_BEGIN
	
	sAIDocument->RedrawDocument();
	
	DOCUMENT_END
}

/*
 * void copy()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_copy(JNIEnv *env, jobject obj) {
	DOCUMENT_BEGIN
	
	sAIDocument->Copy();
	
	DOCUMENT_END
}

/*
 * void cut()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_cut(JNIEnv *env, jobject obj) {
	DOCUMENT_BEGIN
	
	sAIDocument->Cut();
	
	DOCUMENT_END
}

/*
 * void paste()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Document_paste(JNIEnv *env, jobject obj) {
	DOCUMENT_BEGIN
	
	sAIDocument->Paste();
	
	DOCUMENT_END
}