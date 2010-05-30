/*
 * Scriptographer
 *
 * This file is part of Scriptographer, a Plugin for Adobe Illustrator.
 *
 * Copyright (c) 2002-2010 Juerg Lehni, http://www.scratchdisk.com.
 * All rights reserved.
 *
 * Please visit http://scriptographer.org/ for updates and contact.
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
 */

var repositoriesDialog = new ModalDialog(function() {
	var that = this;
	// Set font now as all best-size calculations depend on it (e.g. setting
	// only width on edits).
	this.font = 'palette';

	var cancelButton = new Button(this) {
		text: 'Cancel'
	};

	var okButton = new Button(this) {
		text: '  OK  '
	};

	var nameEdit = new TextEdit(this) {
		onChange: changeEntry
	};

	var pathEdit = new TextEdit(this) {
		onChange: changeEntry
	};

	var chooseButton = new Button(this) {
		text: 'Choose',
		onClick: chooseDirectory
	}

	var addButton = new Button(this) {
		text: 'Add',
		onClick: function() {
			addEntry('', '', true);
			chooseDirectory();
			nameEdit.active = true;
		}
	}

	var removeButton = new Button(this) {
		text: 'Remove',
		onClick: removeEntry
	}

	var upButton = new Button(this) {
		text: 'Up',
		onClick: function() {
			moveEntry(-1);
		}
	}

	var downButton = new Button(this) {
		text: 'Down',
		onClick: function() {
			moveEntry(2);
		}
	}

	var examplesCheckbox = new CheckBox(this) {
		text: 'Show Examples'
	}

	var selectedEntry = null;
	var previousEntry = {}; // To force a change when setting to null.
	var separator = ' -> ';

	function getEntryText(name, directory) {
		var parts = [];
		if (name)
			parts.push(name);
		if (directory)
			parts.push(directory);
		return parts.join(separator);
	}

	function addEntry(name, directory, select) {
		var entry = new ListEntry(repositoriesList) {
			text: getEntryText(name, directory),
			image: folderImage,
			name: name,
			directory: directory
		}
		if (select)
			selectEntry(entry);
		return entry;
	}

	function changeEntry() {
		if (selectedEntry) {
			selectedEntry.name = nameEdit.text;
			selectedEntry.directory = new File(pathEdit.text);
			selectedEntry.text = getEntryText(
					selectedEntry.name, selectedEntry.directory);
		}
	}

	function removeEntry() {
		if (selectedEntry) {
			var index = selectedEntry.index;
			selectedEntry.remove();
			var entry;
			do {
				entry = repositoriesList[index];
			} while (!entry && --index >= 0)
			selectEntry(entry);
		}
	}

	function selectEntry(entry) {
		if (previousEntry != entry) {
			if (previousEntry && previousEntry.isValid && previousEntry.isValid())
				previousEntry.selected = false;
			previousEntry = entry
			if (entry)
				entry.selected = true;
			nameEdit.enabled = pathEdit.enabled = !!entry;
			nameEdit.text = entry && entry.name || '';
			pathEdit.text = entry && entry.directory || '';
			selectedEntry = entry;
		}
	}

	function moveEntry(dir) {
		if (selectedEntry) {
			// There's no way to move, we need to duplicate and remove.
			var entry = repositoriesList.add(selectedEntry.index + dir, selectedEntry);
			entry.name = selectedEntry.name;
			entry.directory = selectedEntry.directory;
			selectedEntry.remove();
			selectEntry(entry);
		}
	}

	function chooseDirectory() {
		if (selectedEntry) {
			var dir = Dialog.chooseDirectory(
					'Choose a Scriptographer Script Repository Folder.',
					selectedEntry.directory || userDirectory);
			if (dir) {
				selectedEntry.directory = dir;
				pathEdit.text = dir;
				changeEntry();
			}
		}
	}

	var width = 400;
	var repositoriesList = new ListBox(this) {
		size: [width, 10 * lineHeight],
		minimumSize: [width, 8 * lineHeight],
		entryTextRect: [0, 0, width, lineHeight],
		// onChange does not fire for key events, so abuse onTrack
		onTrackEntry: function(tracker, entry) {
			// This might change entry.expanded state
			entry.defaultTrack(tracker);
			selectEntry(this.selected.first);
		},
		onChange: function() {
			selectEntry(this.selected.first);
		}
	};

	var folderImage = getImage('folder.png');

	return {
		title: 'Manage Scriptographer Repositories',
		defaultItem: okButton,
		cancelItem: cancelButton,
		margin: 8,
		layout: [
			'preferred preferred fill preferred',
			'preferred preferred fill',
			2, 2
		],
		content: {
			'0, 0, 3, 0': repositoriesList,
			'0, 1': new ItemGroup(this) {
				layout: [ 'left' ],
				content: [
					addButton,
					removeButton,
					upButton,
					downButton
				]
			},
			'1, 1, left, center': nameEdit,
			'2, 1, full, center': pathEdit,
			'3, 1': chooseButton,
			'0, 2': examplesCheckbox,
			'1, 2, 3, 2': new ItemGroup(this) {
				layout: [ 'right' ],
				content: [
					cancelButton,
					okButton
				]
			}
		},

		choose: function(repositories) {
			repositoriesList.removeAll();
			if (repositories) {
				repositories.each(function(repository) {
					var dir = new File(repository.path);
					if (dir.equals(examplesDirectory)) {
						examplesCheckbox.checked = true;
					} else {
						addEntry(repository.name, dir);
					}
				})
			}
			selectEntry();
			if (this.doModal() == okButton) {
				repositories = [];
				if (examplesCheckbox.checked)
					repositories.push({ name: 'Examples', path: examplesDirectory.path });
				return repositoriesList.each(function(entry) {
				 	var repository = { path: entry.directory.path };
					if (entry.name)
						repository.name = entry.name;
					this.push(repository);
				}, repositories);
			}
			return null;
		}
	};
});