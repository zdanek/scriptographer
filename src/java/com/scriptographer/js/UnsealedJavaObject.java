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
 * $RCSfile: UnsealedJavaObject.java,v $
 * $Author: lehni $
 * $Revision: 1.1 $
 * $Date: 2005/02/23 22:00:58 $
 */

package com.scriptographer.js;

import java.util.*;

import org.mozilla.javascript.*;

public class UnsealedJavaObject extends NativeJavaObject {
	HashMap properties = new HashMap();
	
	/**
	 * @param scope
	 * @param javaObject
	 * @param staticType
	 */
	public UnsealedJavaObject(Scriptable scope, Object javaObject,
		Class staticType) {
		super(scope, javaObject, staticType);
	}
	public void delete(String name) {
		super.delete(name);
		properties.remove(name);
	}
	
	/* (non-Javadoc)
	 * @see org.mozilla.javascript.Scriptable#get(java.lang.String, org.mozilla.javascript.Scriptable)
	 */
	public Object get(String name, Scriptable start) {
		Object obj = super.get(name, start);
		if (obj == Scriptable.NOT_FOUND) {
			// see wether this object defines the property.
			obj = properties.get(name);
			if (obj == null) {
				// if not, see wether the prototype maybe defines it.
				// NativeJavaObject misses to do so:
				if (prototype != null) {
					obj = prototype.get(name, start);
				} else {
					obj = Scriptable.NOT_FOUND;
				}
			}
		}
		return obj;
	}
	
	/* (non-Javadoc)
	 * @see org.mozilla.javascript.Scriptable#getIds()
	 */
	public Object[] getIds() {
		// concatenate the super classes ids array with the keySet from properties HashMap:
		Object[] javaIds = super.getIds();
		int numProps = properties.size();
		if (numProps == 0)
			return javaIds;
		Object[] ids = new Object[javaIds.length + numProps];
		Collection propIds = properties.keySet();
		propIds.toArray(ids);
		System.arraycopy(javaIds, 0, ids, numProps, javaIds.length);
		return ids;
	}
	
	/* (non-Javadoc)
	 * @see org.mozilla.javascript.Scriptable#has(java.lang.String, org.mozilla.javascript.Scriptable)
	 */
	public boolean has(String name, Scriptable start) {
		boolean has = super.has(name, start);
		if (!has)
			has = properties.get(name) != null;
		return has;
	}
	
	/* (non-Javadoc)
	 * @see org.mozilla.javascript.Scriptable#put(java.lang.String, org.mozilla.javascript.Scriptable, java.lang.Object)
	 */
	public void put(String name, Scriptable start, Object value) {
		if (super.has(name, start))
			super.put(name, start, value);
		else 
			properties.put(name, value);
	}
}