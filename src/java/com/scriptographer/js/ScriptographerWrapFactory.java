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
 * File created on 02.01.2005.
 *
 * $RCSfile: ScriptographerWrapFactory.java,v $
 * $Author: lehni $
 * $Revision: 1.1 $
 * $Date: 2005/02/23 22:00:58 $
 */

package com.scriptographer.js;

import java.util.WeakHashMap;
import java.util.Map;

import org.mozilla.javascript.*;

import com.scriptographer.ai.*;
import com.scriptographer.util.List;

public class ScriptographerWrapFactory extends WrapFactory {
	private WeakHashMap wrappers = new WeakHashMap();
	
	public Object wrap(Context cx, Scriptable scope, Object obj,
		Class staticType) {
		try {
			// these are not wrappers, the java return types are simply converted to these
			// scriptographer types and wrapped afterwards:
			if (obj instanceof java.awt.geom.Rectangle2D && !(obj instanceof Rectangle)) {
				obj = new Rectangle((java.awt.geom.Rectangle2D) obj);
			} else if (obj instanceof java.awt.geom.Point2D && !(obj instanceof Point)) {
				obj = new Point((java.awt.geom.Point2D) obj);
			} else if (obj instanceof java.awt.geom.AffineTransform && !(obj instanceof Matrix)) {
				obj = new Matrix((java.awt.geom.AffineTransform) obj);
			} else if (obj instanceof java.awt.Dimension) {
				obj = new Point((java.awt.Dimension) obj);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return super.wrap(cx, scope, obj, staticType);
	}

	public Scriptable wrapAsJavaObject(Context cx, Scriptable scope,
		Object javaObj, Class staticType) {
		Scriptable obj;
		// Wrappables know about their wrapper, so ask them:
		if (javaObj instanceof Wrappable) {
			obj = ((Wrappable) javaObj).getWrapper();
			if (obj == null) { // object is not yet wrapped, do it now:
				obj = createJavaObject(scope, javaObj, staticType);
				// let the object know about its newly created wrapper:
				((Wrappable) javaObj).setWrapper(obj);
			}
		} else {
			// keep track of wrappers so that if a given object needs to be
			// wrapped again, take the wrapper from the pool...
			// TODO: see wether this really makes sense or wether rewrapping every time is the way to go
			obj = (Scriptable) wrappers.get(javaObj);
			if (obj == null) {
				obj = createJavaObject(scope, javaObj, staticType);
				wrappers.put(javaObj, obj);
			}
		}
		return obj;
	}
	
	private Scriptable createJavaObject(Scriptable scope, Object javaObj,
		Class staticType) {
		// If the java object wants to stay unsealed, use UnsealedJavaObject
		// instead of the default class:
		if (javaObj instanceof Unsealed) {
			return new UnsealedJavaObject(scope, javaObj, staticType);
		} else if (javaObj instanceof List) {
			return new ListObject(scope, (List) javaObj, staticType);
		} else if (javaObj instanceof Map) {
			return new MapObject(scope, (Map) javaObj, staticType);
		} else {
			return new NativeJavaObject(scope, javaObj, staticType);
		}
	}
}