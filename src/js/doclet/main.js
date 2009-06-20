/**
 * JavaScript Doclet
 * (c) 2005 - 2009, Juerg Lehni, http://www.scratchdisk.com
 *
 * Doclet.js is released under the MIT license
 * http://dev.scriptographer.com/ 
 */

importPackage(Packages.com.sun.javadoc);
importPackage(Packages.com.sun.tools.javadoc);
importPackage(Packages.com.scriptographer.script);

include('lib/bootstrap.js');
include('lib/Template.js');
include('Type.js');
include('Tag.js');
include('Member.js');
include('Method.js');
include('SyntheticMember.js');
include('ReferenceMember.js');
include('BeanProperty.js');
include('Operator.js');
include('MemberGroup.js');
include('MemberGroupList.js');
include('ClassObject.js');
include('Document.js');
include('macros.js');
include('filters.js');

// Helper functions to print to out / err

function print() {
	java.lang.System.out.println($A(arguments).join(' '));
}

function error() {
	java.lang.System.err.println($A(arguments).join(' '));
}

// Change error handling here to just throw errors. This allows us to catch
// then on execution time, not as error text in the rendered output
Template.inject({
	reportMacroError: function(error, command, out) {
		throw error;
	},

	// Template.directory points to the place where the templates are found.
	// The value options.directory is set by the RhinoDoclet
	statics: {
		directory: options.directory + '/templates/'
	}
});

// Add renderTemplate function with caching to all objects
Object.inject(Template.methods, true);

// A global template writer
var out = new TemplateWriter();

// Define settings from passed options:
var settings = {
	basePackage:  options.basepackage || '',
	destDir: (options.d + (options.d && !/\/^/.test(options.d) ? '/' : '')) || '',
	docTitle: options.doctitle || '',
	bottom: options.bottom || '',
	author: options.author || '',
	methodFilter: (options.methodfilter || '').trim().split(/\s+/),
	classFilter: (options.classfilter || '').trim().split(/\s+/),
	classMatch: options.classmatch ? new RegExp('(' + options.classmatch.replace(/\s/g, '|') + ')$', 'g') : null,
	packageSequence: (options.packagesequence || '').trim().split(/\s+/),
	classOrder: (function() {
		var classOrder = new Hash();
		if (options.classorder) {
			var file = new java.io.BufferedReader(new java.io.FileReader(options.classorder));
			var line, count = 1;
			while ((line = file.readLine()) != null) {
				line = line.trim();
				if (line.length)
					classOrder[line.trim()] = count++;
			}
		}
		return classOrder;
	})(),
	sortMembers: options.sortmembers == 'true',
	templates: options.templates == 'true',
	inherited: options.noinherited != 'true',
	summaries: options.nosummaries != 'true',
	fieldSummary: options.nofieldsummary != 'true',
	constructorSummary: options.noconstructorsummary != 'true',
	hyperref: options.nohyperref != 'true',
	versionInfo: options.version == 'true',
	debug: options.shortinherited == 'true',
	headings: {}
};

// Section headings
for (var i = 1; i <= 4; i++) {
	settings.headings[i] = { 
		open: options['heading' + i + 'open'] || '<h' + i + '>',
		close: options['heading' + i + 'close'] || '</h' + i + '>'
	}
}

// A global data object to store global stuff from templates / macros:

var data = {
};

// Enhance String a bit:
String.inject({
	endsWith: function(end) {
		return this.length >= end.length && this.substring(this.length - end.length) == end;
	},

	startsWith: function(start) {
		return this.length >= start.length && this.substring(0, start.length) == start;
	},

	isLowerCase: function() {
		return this.toLowerCase() == this;
	},

	isUpperCase: function() {
		return this.toUpperCase() == this;
	}
});


// Enhance some of the javatool classes with usefull methods:

// Class helpers

// We're injecting Type.prototype into ClassDocImpl, to enhance all ClassDocs
// automatically. It's ok to do so since Rhino doesn't allow to override
// native methods, so e.g. qualifiedName won't loop endlessly.
ClassDocImpl.inject(Type.prototype);

// Parameter helpers

ParameterImpl.inject({
	paramType: function() {
		return new Type(this.type());
	}
});

// Member helpers

MemberDocImpl.inject({
	isVisible: function() {
		return Member.get(this) != null;
	},

	renderLink: function(param) {
		param = param || {};
		var mem = Member.get(this);
		return mem
			? mem.renderLink(param)
			// Invisible members do not get wrapped in Member objects, so they
			// need to at least render something that gives a hint which function
			// they would be. (e.g. when linking to invisible methods using @link)
			: code_filter((this.containingClass() != param.classDoc
				? this.containingClass().name() + (this.isStatic() ? '.' : '#')
				: '') + this.name() + (this.signature ? this.signature() : ''));
	}
});

/**
 * Produces a table-of-contents for classes and calls layoutClass on each class.
 */
function processClasses(classes) {
	var root = new ClassObject();

	// Loop twice, as in the second loop, superclasses are picked from nodes
	// which is filled in the firs loop
	classes.each(function(cd) {
		var cls = ClassObject.get(cd);
		if (cls) {
			cd.classObj = cls;
			root.addChild(cls);
		}
	});
	classes.each(function(cd) {
		var superclass = cd.getSuperclass();
		if (cd.classObj && superclass && superclass.classObj) {
			root.removeChild(cd.classObj);
			superclass.classObj.addChild(cd.classObj);
		}
	});
	root.renderHierarchy('');
}

function getRelativeIdentifier(str) {
	return str.startsWith(settings.basePackage + '.') ?
			str.substring(settings.basePackage.length + 1) : str;
}

function renderLink(param) {
	if (settings.hyperref) {
		var str = '<a href="';
		if (param.path) {
			var path = getRelativeIdentifier(param.path).replace('.', '/');
			// Link to the index file for packages
			var name = Type.getSimpleName(param.path);
			if (name.charAt(0).isLowerCase() && name != 'global')
				path += '/index';
			if (settings.templates)
				path = '/reference/' + path.toLowerCase() + '/';
			else
				path = Document.getBasePath() + path + '.html';
			str += path;
		}
		if (param.anchor) {
			str += '#' + param.anchor;
			if (param.toggle)
				str += '" onClick="return toggleMember(\'' + param.anchor + '\', true);';
		}
		return str + '">' + param.title + '</a>';
	} else {
	 	return param.title;
	}
}

function encodeJs(str) {
	return str ? (str = uneval(str)).substring(1, str.length - 1) : str;
}

function encodeHtml(str) {
	// Encode everything
	var Translate = Packages.org.htmlparser.util.Translate;
	str = Translate.encode(str);
	var tags = {
		code: true, br: true, p: true, b: true, a: true, i: true,
		ol: true, li: true, ul: true, tt: true, pre: true
	};
	// Now replace allowed tags again.
	return str.replace(/&lt;(\/?)(\w*)(.*?)(\s*\/?)&gt;/g, function(match, open, tag, content, close) {
		tag = tag.toLowerCase();
		return tags[tag] ? '<' + open + tag + Translate.decode(content) + close + '>' : match;
	});
}

function encodeAll(str) {
	return Packages.org.htmlparser.util.Translate.encode(str);
}

/**
 * Prints a sequence of tags obtained from e.g. com.sun.javadoc.Doc.tags().
 */
function renderTags(param) {
	return renderTemplate('tags', param);
}

function main() {
	ClassObject.scan(root);

	var packages = new Hash();
	var packageSequence = settings.packageSequence;
	var createSequence = !packageSequence;
	if (createSequence)
		packageSequence = [];

	// Create lookup for packages
	root.specifiedPackages().each(function(pkg) {
		var name = pkg.name();
		packages[name] = pkg;
		if (createSequence)
			packageSequence[i] = name;
	});

	// Now start rendering:
	var doc = new Document('', settings.templates ? 'packages.js'
			: 'packages.html', 'packages');

	packageSequence.each(function(name) {
		var pkg = packages[name];
		if (pkg) {
			var path = getRelativeIdentifier(name);
			var text = renderTags({ tags: pkg.inlineTags() });
			var first = renderTags({ tags: pkg.firstSentenceTags() });
			// Remove the first sentence from the main text, and use it as a title
			if (first && text.startsWith(first)) {
				text = text.substring(first.length);
				first = first.substring(0, first.length - 1); // cut away dot
			}

			out.push();
			processClasses(pkg.interfaces());
			processClasses(pkg.allClasses(true));
			processClasses(pkg.exceptions());
			processClasses(pkg.errors());

			renderTemplate('packages#package', {
				content: out.pop(), name: name, path: path, text: text
			}, out);

			if (!settings.templates) {
				// Write package file:
				var index = new Document(path, 'index', 'document');
				renderTemplate('package', { title: first, text: text }, out);
				index.close();
			}
		}
	});
	doc.close();
}

main();
