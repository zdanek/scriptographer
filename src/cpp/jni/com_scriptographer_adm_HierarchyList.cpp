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
 * $RCSfile: com_scriptographer_adm_HierarchyList.cpp,v $
 * $Author: lehni $
 * $Revision: 1.1 $
 * $Date: 2005/02/23 22:00:59 $
 */
 
#include "stdHeaders.h"
#include "ScriptographerEngine.h"
#include "admGlobals.h"
#include "com_scriptographer_adm_HierarchyList.h"

/*
 * com.scriptographer.adm.HierarchyList
 */
 
// lists don't have init callbacks that automatically get called, but just for simetry let's use the same scheme:
ASErr ASAPI callbackHierarchyListInit(ADMHierarchyListRef list) {
	JNIEnv *env = gEngine->getEnv();
	try {
		jobject listObj = env->NewGlobalRef( env->NewObject(gEngine->cls_HierarchyList, gEngine->cid_HierarchyList, (jint)list));
		sADMHierarchyList->SetUserData(list, listObj);
		sADMHierarchyList->SetInitProc(list, callbackHierarchyListEntryInit);
		sADMHierarchyList->SetDestroyProc(list, callbackHierarchyListEntryDestroy);
		sADMHierarchyList->SetNotifyProc(list, callbackHierarchyListEntryNotify);
		/* these are activated in enable****Callback
		sADMHierarchyList->SetTrackProc(list, callbackHierarchyListEntryTrack);
		sADMHierarchyList->SetDrawProc(list, callbackHierarchyListEntryDraw);
		*/
	} EXCEPTION_CATCH_REPORT(env)
	return kNoErr;
}

void ASAPI callbackHierarchyListDestroy(ADMHierarchyListRef list) {
	jobject listObj = gEngine->getListObject(list);
	JNIEnv *env = gEngine->getEnv();
	env->DeleteGlobalRef(listObj);
	sADMHierarchyList->SetUserData(list, NULL);
}

/*
 * void setEntrySize(int width, int height, boolean recursive)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_setEntrySize(JNIEnv *env, jobject obj, jint width, jint height, jboolean recursive) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		if (recursive) {
			sADMHierarchyList->SetEntryWidthRecursive(list, width);
			sADMHierarchyList->SetEntryHeightRecursive(list, height);
		} else {
			sADMHierarchyList->SetEntryWidth(list, width);
			sADMHierarchyList->SetEntryHeight(list, height);
		}
	} EXCEPTION_CONVERT(env)
}

/*
 * void setEntryTextRect(int x, int y, int width, int height, boolean recursive)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_setEntryTextRect(JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height, jboolean recursive) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMRect rt;
		rt.left = x;
		rt.top = y;
		rt.right = x + width;
		rt.bottom = y + height;

		if (recursive)
			sADMHierarchyList->SetEntryTextRectRecursive(list, &rt);
		else
			sADMHierarchyList->SetEntryTextRect(list, &rt);
	} EXCEPTION_CONVERT(env)
}

/*
 * int getNonLeafEntryWidth()
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_HierarchyList_getNonLeafEntryWidth(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		return sADMHierarchyList->GetNonLeafEntryWidth(list);
	} EXCEPTION_CONVERT(env)
	return 0;
}

/*
 * void setNonLeafEntryTextRect(int x, int y, int width, int height, boolean recursive)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_setNonLeafEntryTextRect(JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height, jboolean recursive) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMRect rt;
		rt.left = x;
		rt.top = y;
		rt.right = x + width;
		rt.bottom = y + height;

		if (recursive)
			sADMHierarchyList->SetNonLeafEntryTextRectRecursive(list, &rt);
		else 
			sADMHierarchyList->SetNonLeafEntryTextRect(list, &rt);
	} EXCEPTION_CONVERT(env)
}

/*
 * com.scriptographer.ai.Rectangle getNonLeafEntryTextRect()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_getNonLeafEntryTextRect(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMRect rt;
		sADMHierarchyList->GetEntryTextRect(list, &rt);
		return gEngine->convertRectangle(env, &rt);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * com.scriptographer.adm.ListEntry getLeafEntry(int x, int y)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_getLeafEntry(JNIEnv *env, jobject obj, jint x, jint y) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		DEFINE_ADM_POINT(pt, x, y);
		ADMListEntryRef ent = sADMHierarchyList->PickLeafEntry(list, &pt);
		return gEngine->getEntryObject(ent);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * com.scriptographer.adm.Entry getActiveLeafEntry()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_getActiveLeafEntry(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMListEntryRef ent = sADMHierarchyList->GetActiveLeafEntry(list);
		return gEngine->getEntryObject(ent);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

#define GET_ENTRIES(GET_NUMBER, INDEX_ENTRY) \
	try { \
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj); \
		int length = sADMHierarchyList->GET_NUMBER(list); \
		jobjectArray res = env->NewObjectArray(length, gEngine->cls_ListEntry, NULL); \
		if (res == NULL) EXCEPTION_CHECK(env) \
		for (int i = 0; i < length; i++) { \
			ADMListEntryRef ent = sADMHierarchyList->INDEX_ENTRY(list, i); \
			env->SetObjectArrayElement(res, i, gEngine->getEntryObject(ent)); \
		} \
		EXCEPTION_CHECK(env) \
		return res; \
	} EXCEPTION_CONVERT(env) \
	return NULL;

/*
 * com.scriptographer.adm.Entry[] getAllSelectedEntries()
 */
JNIEXPORT jobjectArray JNICALL Java_com_scriptographer_adm_HierarchyList_getAllSelectedEntries(JNIEnv *env, jobject obj) {
	GET_ENTRIES(NumberOfAllSelectedEntriesInHierarchy, IndexAllSelectedEntriesInHierarchy)
}

/*
 * com.scriptographer.adm.Entry[] getAllUnnestedSelectedEntries()
 */
JNIEXPORT jobjectArray JNICALL Java_com_scriptographer_adm_HierarchyList_getAllUnnestedSelectedEntries(JNIEnv *env, jobject obj) {
	GET_ENTRIES(NumberOfUnNestedSelectedEntriesInHierarchy, IndexUnNestedSelectedEntriesInHierarchy)
}

/*
 * com.scriptographer.adm.Entry getParentEntry()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_getParentEntry(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMListEntryRef ent = sADMHierarchyList->GetParentEntry(list);
		if (ent != NULL)
			return gEngine->getEntryObject(ent);
		else
			return NULL;
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * com.scriptographer.ai.Rectangle getLocalRect()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_getLocalRect(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMRect rt;
		sADMHierarchyList->GetLocalRect(list, &rt);
		return gEngine->convertRectangle(env, &rt);
	} EXCEPTION_CONVERT(env)
	return NULL;
}


/*
 * java.awt.Point localToScreen(int x, int y)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_localToScreen(JNIEnv *env, jobject obj, jint x, jint y) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		DEFINE_ADM_POINT(pt, x, y);
		sADMHierarchyList->LocalToScreenPoint(list, &pt);
		return gEngine->convertPoint(env, &pt);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * java.awt.Point screenToLocal(int x, int y)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_screenToLocal(JNIEnv *env, jobject obj, jint x, jint y) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		DEFINE_ADM_POINT(pt, x, y);
		sADMHierarchyList->ScreenToLocalPoint(list, &pt);
		return gEngine->convertPoint(env, &pt);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * java.awt.Point localToGlobal(int x, int y)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_localToGlobal__II(JNIEnv *env, jobject obj, jint x, jint y) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		DEFINE_ADM_POINT(pt, x, y);
		sADMHierarchyList->LocalToGlobalPoint(list, &pt);
		return gEngine->convertPoint(env, &pt);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * java.awt.Point globalToLocal(int arg1, int arg2)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_globalToLocal__II(JNIEnv *env, jobject obj, jint x, jint y) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		DEFINE_ADM_POINT(pt, x, y);
		sADMHierarchyList->GlobalToLocalPoint(list, &pt);
		return gEngine->convertPoint(env, &pt);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * java.awt.Rectangle localToGlobal(int x, int y, int width, int height)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_localToGlobal__IIII(JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		DEFINE_ADM_RECT(rt, x, y, width, height);
		sADMHierarchyList->LocalToGlobalRect(list, &rt);
		return gEngine->convertRectangle(env, &rt);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * java.awt.Rectangle globalToLocal(int x, int y, int width, int height)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_globalToLocal__IIII(JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		DEFINE_ADM_RECT(rt, x, y, width, height);
		sADMHierarchyList->GlobalToLocalRect(list, &rt);
		return gEngine->convertRectangle(env, &rt);
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * void setIndentationWidth(int width, boolean recursive)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_setIndentationWidth(JNIEnv *env, jobject obj, jint width, jboolean recursive) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		if (recursive)
			sADMHierarchyList->SetIndentationWidthRecursive(list, width);
		else 
			sADMHierarchyList->SetIndentationWidth(list, width);
	} EXCEPTION_CONVERT(env)
}

/*
 * int getIndentationWidth()
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_HierarchyList_getIndentationWidth(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		return sADMHierarchyList->GetIndentationWidth(list);
	} EXCEPTION_CONVERT(env)
	return 0;
}

/*
 * void setLocalLeftMargin(int width)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_setLocalLeftMargin(JNIEnv *env, jobject obj, jint width) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		return sADMHierarchyList->SetLocalLeftMargin(list, width);
	} EXCEPTION_CONVERT(env)
}

/*
 * int getLocalLeftMargin()
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_HierarchyList_getLocalLeftMargin(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		return sADMHierarchyList->GetLocalLeftMargin(list);
	} EXCEPTION_CONVERT(env)
	return 0;
}

/*
 * int getGlobalLeftMargin()
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_HierarchyList_getGlobalLeftMargin(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		return sADMHierarchyList->GetGlobalLeftMargin(list);
	} EXCEPTION_CONVERT(env)
	return 0;
}

/*
 * void setDivided(boolean divided, boolean recursive)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_setDivided(JNIEnv *env, jobject obj, jboolean divided, jboolean recursive) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		if (recursive)
			sADMHierarchyList->SetDividedRecursive(list, divided);
		else 
			sADMHierarchyList->SetDivided(list, divided);
	} EXCEPTION_CONVERT(env)
}

/*
 * boolean isDivided()
 */
JNIEXPORT jboolean JNICALL Java_com_scriptographer_adm_HierarchyList_isDivided(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		return sADMHierarchyList->GetDivided(list);
	} EXCEPTION_CONVERT(env)
	return JNI_FALSE;
}

/*
 * void setFlags(int flags, boolean recursive)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_setFlags(JNIEnv *env, jobject obj, jint flags, jboolean recursive) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		if (recursive)
			sADMHierarchyList->SetFlagsRecursive(list, flags);
		else 
			sADMHierarchyList->SetFlags(list, flags);
	} EXCEPTION_CONVERT(env)
}

/*
 * int getFlags()
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_HierarchyList_getFlags(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		return sADMHierarchyList->GetFlags(list);
	} EXCEPTION_CONVERT(env)
	return 0;
}

/*
 * void invalidate()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_invalidate(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		sADMHierarchyList->Invalidate(list);
	} EXCEPTION_CONVERT(env)
}

/*
 * com.scriptographer.adm.Entry[] getLeafEntries()
 */
JNIEXPORT jobjectArray JNICALL Java_com_scriptographer_adm_HierarchyList_getLeafEntries(JNIEnv *env, jobject obj) {
	GET_ENTRIES(NumberOfLeafEntries, IndexLeafEntry)
}

/*
 * int getLeafIndex(com.scriptographer.adm.Entry entry)
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_HierarchyList_getLeafIndex(JNIEnv *env, jobject obj, jobject entry) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMListEntryRef ent = gEngine->getHierarchyListEntryRef(env, entry);
		return sADMHierarchyList->GetLeafIndex(list, ent);
	} EXCEPTION_CONVERT(env)
	return 0;
}

/*
 * void swapEntries(int fromIndex, int toIndex)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_swapEntries(JNIEnv *env, jobject obj, jint fromIndex, jint toIndex) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		sADMHierarchyList->SwapEntries(list, fromIndex, toIndex);
	} EXCEPTION_CONVERT(env)
}

/*
 * com.scriptographer.adm.Entry insertEntry(com.scriptographer.adm.Entry entry, int index)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_insertEntry(JNIEnv *env, jobject obj, jobject entry, jint index) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMListEntryRef ent = gEngine->getHierarchyListEntryRef(env, entry);
		ent = sADMHierarchyList->InsertGivenEntry(list, ent, index);
		return gEngine->getEntryObject(ent); 
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * com.scriptographer.adm.Entry unlinkEntry(int index)
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_adm_HierarchyList_unlinkEntry(JNIEnv *env, jobject obj, jint index) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMListEntryRef ent = sADMHierarchyList->UnlinkEntry(list, index);
		return gEngine->getEntryObject(ent); 
	} EXCEPTION_CONVERT(env)
	return NULL;
}

/*
 * void deselectAll()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_HierarchyList_deselectAll(JNIEnv *env, jobject obj) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		sADMHierarchyList->DeselectAll(list);
	} EXCEPTION_CONVERT(env)
}

/*
 * com.scriptographer.adm.Entry[] getExpandedEntries()
 */
JNIEXPORT jobjectArray JNICALL Java_com_scriptographer_adm_HierarchyList_getExpandedEntries(JNIEnv *env, jobject obj) {
	GET_ENTRIES(NumberOfExpandedEntries, IndexExpandedEntry)
}

/*
 * int getExpandedIndex(com.scriptographer.adm.Entry entry)
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_HierarchyList_getExpandedIndex(JNIEnv *env, jobject obj, jobject entry) {
	try {
		ADMHierarchyListRef list = gEngine->getHierarchyListRef(env, obj);
		ADMListEntryRef ent = gEngine->getHierarchyListEntryRef(env, entry);
		return sADMHierarchyList->GetExpandedIndex(list, ent);
	} EXCEPTION_CONVERT(env)
	return 0;
}