/**
 * JavaScript Doclet
 * (c) 2005 - 2007, Juerg Lehni, http://www.scratchdisk.com
 *
 * Doclet.js is released under the MIT license
 * http://dev.scriptographer.com/ 
 */

// A js Tag class, to define own tag lists and override tag names with special
// render handlers.

Tag = Object.extend(new function() {
	var tags = {};

	[TagImpl, SeeTagImpl].each(function(impl) {
		impl.inject({
			render_macro: function() {
				var name = this.name();
				var tag = tags[name];
				if (tag) {
					// Call method from pseudo tag implementiation on native tag.
					return tag.render.apply(this, arguments);
				} else {
					// Default
					return this.text();
				}
			}
		});
	});

	return {
		initialize: function(str) {
			this.str = str;
		},

		render_macro: function(param) {
			return this.str;
		},

		statics: {
			extend: function(src) {
				return src._names.split(',').each(function(tag) {
					tags[tag] = new this();
				}, this.base(src));
			}
		}
	}
});

LinkTag = Tag.extend({
	_names: '@link,@see',

	render: function(param) {
		var ref = this.referencedMember() || this.referencedClass();
		if (ref) {
			if (ref.isVisible()) {
				return ref.renderLink({ classDoc: param.classDoc });
			} else {
				error(this.position() + ': warning - ' + this.name() + ' contains reference to invisible object: ' + ref);
				return code_filter(this);
			}
		} else {
			error(this.position() + ': warning - ' + this.name() + ' contains undefined reference: ' + this);
			return code_filter(this);
		}
	}
});

GroupTag = Tag.extend({
	_names: '@grouptitle,@grouptext',

	render: function(param) {
		data.group[this.name().substring(6)] = this.text();
	}
});