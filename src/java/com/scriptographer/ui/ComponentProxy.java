/*
 * Scriptographer
 *
 * This file is part of Scriptographer, a Scripting Plugin for Adobe Illustrator
 * http://scriptographer.org/
 *
 * Copyright (c) 2002-2010, Juerg Lehni
 * http://scratchdisk.com/
 *
 * All rights reserved. See LICENSE file for details.
 * 
 * File created on Jun 2, 2010.
 */

package com.scriptographer.ui;


/**
 * @author lehni
 *
 * @jshide
 */
public abstract class ComponentProxy {

	protected Component component;

	public ComponentProxy(Component component) {
		this.component = component;
		component.proxy = this;
	}

	/*
	 * Two methods to simply pass on protected method calls to Component, so the
	 * methods do not need to be exposed and can be used from subclasses of
	 * ComponentProx in other packages as well, e.g. adm.
	 */

	protected void initialize() {
		component.initialize();
	}

	protected void onSizeChanged() {
		component.onSizeChanged();
	}

	protected void onChange(boolean callback) {
		component.onChange(callback);
	}

	protected void onClick() {
		component.onClick();
	}

	protected void onSelect() {
		component.onSelect();
	}

	public abstract void updateSize();

	public abstract Object getValue();

	public abstract boolean setValue(Object value);

	public abstract Integer getSelectedIndex();

	public abstract boolean setSelectedIndex(Integer index, boolean callback);

	public abstract boolean setRange(Double min, Double max);

	public abstract void setIncrement(double increment);

	public abstract void setFractionDigits(Integer fractionDigits);

	public abstract void setUnits(TextUnits units);

	public abstract void setSteppers(Boolean steppers);

	public abstract void setVisible(boolean visible);

	public abstract void setEnabled(boolean enabled);

	public abstract void setMaxLength(Integer maxLength);

	public abstract void setOptions(Object[] options, Object current);
}
