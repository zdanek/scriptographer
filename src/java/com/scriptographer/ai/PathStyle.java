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
 * File created on 14.02.2005.
 *
 * $RCSfile: PathStyle.java,v $
 * $Author: lehni $
 * $Revision: 1.1 $
 * $Date: 2005/02/23 22:01:00 $
 */

package com.scriptographer.ai;

import com.scriptographer.Commitable;
import com.scriptographer.CommitManager;

public class PathStyle implements Commitable {
	protected FillStyle fill;			/* Fill style, if fillPaint is true */
	protected StrokeStyle stroke;		/* Stroke style, if strokePaint is true */
	protected boolean clip;				/* Whether or not to use this as a clipping path */
	protected boolean lockClip;			/* Whether or not to lock the clipping path */
	protected boolean evenOdd;			/* Whether or not to use the even-odd rule to determine path insideness */
	protected float resolution;			/* Path's resolution */
	protected Art art = null;

	private boolean dirty = false;
	private int version = -1;

	protected PathStyle() {
		fill = new FillStyle(this);
		stroke = new StrokeStyle(this);
	}

	protected PathStyle(Art art) {
		this();
		this.art = art;
		fetch();
	}

	public PathStyle(PathStyle style) {
		this();
		init(
			style.fill.color, style.fill.overprint,
			style.stroke.color, style.stroke.overprint, style.stroke.width, style.stroke.dashOffset, style.stroke.dashArray, style.stroke.cap, style.stroke.join, style.stroke.miterLimit,
			style.clip, style.lockClip, style.evenOdd, style.resolution
		);
	}

	protected PathStyle(PathStyle style, Art art) {
		this(style);
		this.art = art;
		markDirty();
	}

	protected void checkUpdate() {
		if (version != CommitManager.getVersion())
			fetch();
	}

	private native void nativeFetch(int artHandle);
	private native void nativeCommit(int artHandle, float[] fillColor, boolean fillOverprint,
			float[] strokeColor, boolean strokeOverprint, float strokeWidth, float dashOffset, float[] dashArray, short cap, short join, float miterLimit,
			boolean clip, boolean lockClip, boolean evenOdd, float resolution);

	public void fetch() {
		if (!dirty && art != null) {
			nativeFetch(art.artHandle);
			version = CommitManager.getVersion();
			dirty = false;
		}
	}

	public void commit() {
		if (art != null) {
			nativeCommit(art.artHandle,
					fill.color.getComponents(), fill.overprint,
					stroke.color.getComponents(), stroke.overprint, stroke.width, stroke.dashOffset, stroke.dashArray, stroke.cap, stroke.join, stroke.miterLimit,
					clip, lockClip, evenOdd, resolution
			);
			version = CommitManager.getVersion();
			dirty = false;
		}
	}

	protected void markDirty() {
		// only mark it as dirty if it's attached to a path already:
		if (!dirty && art != null) {
			CommitManager.markDirty(this);
			dirty = true;
		}
	}

	public Object clone() {
		return new PathStyle(this);
	}

	protected void init(Color fillColor, boolean fillOverprint,
			Color strokeColor, boolean strokeOverprint, float strokeWidth, float dashOffset, float[] dashArray, short cap, short join, float miterLimit,
			boolean clip, boolean lockClip, boolean evenOdd, float resolution) {
		fill.init(fillColor, fillOverprint);
		stroke.init(strokeColor, strokeOverprint, strokeWidth, dashOffset, dashArray, cap, join, miterLimit);
		this.clip = clip;
		this.lockClip = lockClip;
		this.evenOdd = evenOdd;
		this.resolution = resolution;
	}

	public FillStyle getFill() {
		return fill;
	}

	public void setFill(FillStyle fill) {
		this.fill = new FillStyle(fill, this);
		markDirty();
	}

	public StrokeStyle getStroke() {
		return stroke;
	}

	public void setStroke(StrokeStyle stroke) {
		this.stroke = new StrokeStyle(stroke, this);
		markDirty();
	}

	public boolean getClip() {
		return clip;
	}

	public void setClip(boolean clip) {
		this.clip = clip;
		markDirty();
	}

	public boolean getLockClip() {
		return lockClip;
	}

	public void setLockClip(boolean lockClip) {
		this.lockClip = lockClip;
		markDirty();
	}

	public boolean getEvenOdd() {
		return evenOdd;
	}

	public void setEvenOdd(boolean evenOdd) {
		this.evenOdd = evenOdd;
		markDirty();
	}

	public float getResolution() {
		return resolution;
	}

	public void setResolution(float resolution) {
		this.resolution = resolution;
		markDirty();
	}
}