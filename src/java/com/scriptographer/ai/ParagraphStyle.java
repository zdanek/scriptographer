/*
 * Scriptographer
 * 
 * This file is part of Scriptographer, a Plugin for Adobe Illustrator.
 * 
 * Copyright (c) 2002-2008 Juerg Lehni, http://www.scratchdisk.com.
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
 * File created on 04.11.2005.
 * 
 * $Id$
 */

package com.scriptographer.ai;

import com.scratchdisk.script.ArgumentReader;
import com.scratchdisk.util.IntegerEnumUtils;
import com.scriptographer.CommitManager;
import com.scriptographer.Commitable;

/**
 * @author lehni
 */
public class ParagraphStyle extends NativeObject implements Style, Commitable {

	private TextRange range;
	private Object commitKey;
	protected boolean dirty = false;
	protected int version = -1;
	
	private static native int nativeCreate();
	
	private ParagraphStyle(int handle) {
		super(handle);
		version = CommitManager.version;
	}
	
	public ParagraphStyle() {
		this(nativeCreate());
		range = null;
		commitKey = this;
	}

	public ParagraphStyle(ArgumentReader reader) {
		this();
		setJustification(reader.readEnum("justification", ParagraphJustification.class));
		setSingleWordJustification(reader.readEnum("singleWordJustification", ParagraphJustification.class));
		setFirstLineIndent(reader.readFloat("firstLineIndent"));
		setStartIndent(reader.readFloat("startIndent"));
		setEndIndent(reader.readFloat("endIndent"));
		setSpaceBefore(reader.readFloat("spaceBefore"));
		setSpaceAfter(reader.readFloat("spaceAfter"));
		setHyphenation(reader.readBoolean("hyphenation"));
		setHyphenatedWordSize(reader.readInteger("hyphenatedWordSize"));
		setPreHyphenSize(reader.readInteger("preHyphenSize"));
		setPostHyphenSize(reader.readInteger("postHyphenSize"));
		setConsecutiveHyphenLimit(reader.readInteger("consecutiveHyphenLimit"));
		setHyphenationZone(reader.readFloat("hyphenationZone"));
		setHyphenateCapitalized(reader.readBoolean("hyphenateCapitalized"));
		setHyphenationPreference(reader.readFloat("hyphenationPreference"));
		setDesiredWordSpacing(reader.readFloat("desiredWordSpacing"));
		setMaxWordSpacing(reader.readFloat("maxWordSpacing"));
		setMinWordSpacing(reader.readFloat("minWordSpacing"));
		setDesiredLetterSpacing(reader.readFloat("desiredLetterSpacing"));
		setMaxLetterSpacing(reader.readFloat("maxLetterSpacing"));
		setMinLetterSpacing(reader.readFloat("minLetterSpacing"));
		setDesiredGlyphScaling(reader.readFloat("desiredGlyphScaling"));
		setMaxGlyphScaling(reader.readFloat("maxGlyphScaling"));
		setMinGlyphScaling(reader.readFloat("minGlyphSpacing"));
		setAutoLeadingPercentage(reader.readFloat("autoLeadingPercentage"));
		setLeading(reader.readEnum("leading", LeadingType.class));
		// TODO: setTabStops((TabStopList) reader.readObject("tabStop", TabStopList.class));
		setDefaultTabWidth(reader.readFloat("defaultTabWidth"));
	}

	protected ParagraphStyle(int handle, TextRange range) {
		this(handle);
		this.range = range;
		this.commitKey = range != null ?
				(Object) range.getStory() : (Object) this;
	}
	
	protected void changeHandle(int newHandle) {
		nativeRelease(handle); // release old handle
		handle = newHandle;
	}
	
	private native int nativeClone();
	
	public Object clone() {
		if (dirty) // make sur it's not dirty 
			commit();
		return new ParagraphStyle(nativeClone());
	}
	
	protected native void nativeSetStyle(int handle, int rangeHandle);

	public void commit() {
		if (dirty) {
			if (range != null)
				nativeSetStyle(handle, range.handle);
			dirty = false;
		}
	}
	
	/**
	 * markSetStyle is called from the native environemnt. it marks dirty but
	 * doesn't set pathStyleChanged, as it's only used for character style
	 * features
	 */
	protected void markSetStyle() {
		if (!dirty) {
			CommitManager.markDirty(commitKey, this);
			dirty = true;
		}
	}
	
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------

	private native Integer nativeGetJustification();
	private native void nativeSetJustification(Integer justification);
	
	public ParagraphJustification getJustification() {
		return IntegerEnumUtils.get(ParagraphJustification.class, nativeGetJustification());
	}

	public void setJustification(ParagraphJustification type) {
		nativeSetJustification(type != null ? type.value : null);
	}
	
	private native Integer nativeGetSingleWordJustification();
	private native void nativeSetSingleWordJustification(Integer justification);

	public ParagraphJustification getSingleWordJustification() {
		return IntegerEnumUtils.get(ParagraphJustification.class, nativeGetSingleWordJustification());
	}

	public void setSingleWordJustification(ParagraphJustification type) {
		nativeSetSingleWordJustification(type != null ? type.value : null);
	}

	public native Float getFirstLineIndent();
	public native void setFirstLineIndent(Float indent);
	
	public native Float getStartIndent();
	public native void setStartIndent(Float indent);
	
	public native Float getEndIndent();
	public native void setEndIndent(Float indent);
	
	public native Float getSpaceBefore();
	public native void setSpaceBefore(Float space);
	
	public native Float getSpaceAfter();
	public native void setSpaceAfter(Float space);

	// ------------------------------------------------------------------
	// Hyphenation Features
	// ------------------------------------------------------------------
	
	public native Boolean getHyphenation();
	public native void setHyphenation(Boolean hyphenate);
	
	public native Integer getHyphenatedWordSize();
	public native void setHyphenatedWordSize(Integer size);
	
	public native Integer getPreHyphenSize();
	public native void setPreHyphenSize(Integer size);
	
	public native Integer getPostHyphenSize();
	public native void setPostHyphenSize(Integer size);
	
	public native Integer getConsecutiveHyphenLimit();
	public native void setConsecutiveHyphenLimit(Integer limit);
	
	public native Float getHyphenationZone();
	public native void setHyphenationZone(Float zone);
	
	public native Boolean getHyphenateCapitalized();
	public native void setHyphenateCapitalized(Boolean hyphenate);
	
	public native Float getHyphenationPreference();
	public native void setHyphenationPreference(Float preference);

	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	
	public native Float getDesiredWordSpacing();
	public native void setDesiredWordSpacing(Float spacing);
	
	public native Float getMaxWordSpacing();
	public native void setMaxWordSpacing(Float spacing);
	
	public native Float getMinWordSpacing();
	public native void setMinWordSpacing(Float spacing);
	
	public native Float getDesiredLetterSpacing();
	public native void setDesiredLetterSpacing(Float spacing);
	
	public native Float getMaxLetterSpacing();
	public native void setMaxLetterSpacing(Float spacing);
	
	public native Float getMinLetterSpacing();
	public native void setMinLetterSpacing(Float spacing);
	
	public native Float getDesiredGlyphScaling();
	public native void setDesiredGlyphScaling(Float scaling);
	
	public native Float getMaxGlyphScaling();
	public native void setMaxGlyphScaling(Float scaling);
	
	public native Float getMinGlyphScaling();
	public native void setMinGlyphScaling(Float scaling);
	
	public native Float getAutoLeadingPercentage();
	public native void setAutoLeadingPercentage(Float percentage);
	
	private native Integer nativeGetLeading();
	private native void nativeSetLeading(Integer type);
	
	public LeadingType getLeading() {
		return IntegerEnumUtils.get(LeadingType.class, nativeGetLeading());
	}

	public void setLeading(LeadingType type) {
		nativeSetLeading(type != null ? type.value : null);
	}
	
	/* TODO: implement
	public native TabStopList getTabStops();
	public native void setTabStops(TabStopList tabStops);
	*/
	
	public native Float getDefaultTabWidth();
	public native void setDefaultTabWidth(Float width);

	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	/* TODO:
	ATEErr (*GetHangingRoman) ( ParaFeaturesRef parafeatures, bool* isAssigned, bool* ret);
	ATEErr (*GetAutoTCY) ( ParaFeaturesRef parafeatures, bool* isAssigned, ASInt32* ret);
	ATEErr (*GetBunriKinshi) ( ParaFeaturesRef parafeatures, bool* isAssigned, bool* ret);
	ATEErr (*GetBurasagariType) ( ParaFeaturesRef parafeatures, bool* isAssigned, BurasagariType* ret);
	ATEErr (*GetPreferredKinsokuOrder) ( ParaFeaturesRef parafeatures, bool* isAssigned, PreferredKinsokuOrder* ret);
	ATEErr (*GetKurikaeshiMojiShori) ( ParaFeaturesRef parafeatures, bool* isAssigned, bool* ret);
	/// This will return a null object if Kinsoku is not used (ie None set)
	ATEErr (*GetKinsoku) ( ParaFeaturesRef parafeatures, bool* isAssigned, KinsokuRef* ret);
	/// This will return a null object if Mojikumi is not used (ie None set)
	ATEErr (*GetMojiKumi) ( ParaFeaturesRef parafeatures, bool* isAssigned, MojiKumiRef* ret);
	// Other
	ATEErr (*GetEveryLineComposer) ( ParaFeaturesRef parafeatures, bool* isAssigned, bool* ret);
	ATEErr (*GetDefaultCharFeatures) ( ParaFeaturesRef parafeatures, bool* isAssigned, CharFeaturesRef* ret);
	*/
	
	private native void nativeRelease(int handle);
	
	protected void finalize() {
		nativeRelease(handle);
		handle = 0;
	}
}
