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
 * $RCSfile: stdHeaders.h,v $
 * $Author: lehni $
 * $Revision: 1.1 $
 * $Date: 2005/02/23 22:00:59 $
 */
 
#if !defined(__STDHEADERS_H_INCLUDED__)
#define __STDHEADERS_H_INCLUDED__

#include "SPConfig.h"

// Derective for Codewarrior to build the pre-compiled header file
#if (defined(__PIMWCWMacPPC__) && !(defined(MakingPreCompiledHeader)))
	#if _DEBUG
		#include "ScriptographerDebug.ch"
	#else
		#include "ScriptographerRelease.ch"
	#endif
#else

// os stuff
#ifdef MAC_ENV
	#include <MacHeadersCarbon.h>
	#include <MacTypes.h>
#endif

#ifdef WIN_ENV
	#include "windows.h"
	#include <time.h>
#endif

#define PI 3.14159265358979323846

// std library 
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;


// sweet pea headers
#include "SPTypes.h"
#include "SPBlocks.h"
#include "SPAccess.h"
#include "SPFiles.h"
#include "SPInterf.h"
#include "SPRuntme.h" 
#include "SPSuites.h" 

// adm headers
#include "ADMBasic.h"
#include "ADMDialog.h"
#include "ADMHost.h"
#include "ADMItem.h"
#include "ADMIcon.h"
#include "ADMImage.h"
#include "ADMList.h"
#include "ADMHierarchyList.h"
#include "ADMDialogGroup.h"
#include "ADMNotifier.h"
#include "ADMEntry.h"
#include "ADMListEntry.h"
#include "ADMTracker.h"
#include "ADMDrawer.h"
#include "ADMResource.h"

// illustrator headers
#include "AITypes.h"                        

#ifdef ILL9OR10
// Compatibility for Illustrator version before CS:
// ASRect, ASPoint, ASRGBColor, etc. have been deprecated in favor of ADM types with the same
// name, ADMRect, ADMPoint, etc. The switch to ADMxxx types is painless and makes for a more
// uniform use of standard Adobe types. If for some reason you cannot switch you can uncomment
// the old ASxxx types in ASTypes.h.
#define ADMRect ASRect
#define ADMPoint ASPoint
#define OLD_TEXT_SUITES 1
#else
// Illustrator 11 and above
#endif // #ifdef ILL9OR10

// System Suites
#include "AIPlugin.h"
#include "AIMDMemory.h"

// General Suites
#include "AIAnnotator.h"
#include "AIArray.h"
#include "AIArt.h"
#include "AIArtSet.h"
#include "AIBlock.h"
#include "AIOverrideColorConversion.h"
#include "AIColorConversion.h"
#include "AIContext.h"
#include "AICursorSnap.h"
#include "AICustomColor.h"
#include "AIDocument.h"
#include "AIDocumentList.h"
#include "AIFileFormat.h"
#include "AIFilter.h"
#include "AIGroup.h"
#include "AIHitTest.h"
#include "AILayer.h"
#include "AILiveEffect.h"
#include "AIMask.h"
#include "AIMatchingArt.h"
#include "AIMenu.h"
#include "AIMenuGroups.h"
#include "AINotifier.h"
#include "AIPaintStyle.h"
#include "AIPath.h"
#include "AIPathStyle.h"
#include "AIPathConstruction.h"
#include "AIPathfinder.h"
#include "AIPathInterpolate.h"
#include "AIPluginGroup.h"
#include "AIRandom.h"
#include "AIRaster.h"
#include "AIRasterize.h"
#include "AIRealMath.h"
#include "AIRuntime.h"
#include "AIShapeConstruction.h"
#include "AITabletData.h"
#include "AITag.h"
#include "AITimer.h"
#include "AITool.h"
#include "AITransformArt.h"
#include "AIUser.h"
#include "AIUndo.h"
#include "AIDocumentView.h"

#include "AIContext.h"
#include "AIPreference.h"

#ifdef OLD_TEXT_SUITES
#include "AIText.h"
#include "AITextFaceStyle.h"
#include "AITextLine.h"
#include "AITextPath.h"
#include "AITextRun.h"
#include "AITextStream.h"
#else
#include "IText.h"
#endif

#include <jni.h>
#include "Suites.h"

#endif // #if (defined(__PIMWCWMacPPC__) && !(defined(MakingPreCompiledHeader)))
#endif //  !defined(__STDHEADERS_H_INCLUDED__)