var item = new MenuItem("test", "Testing", MenuGroup.GROUP_OPEN);
var group = item.createSubGroup(MenuGroup.OPTION_SORTED_ALPHABETICALLY);

var subIem = new MenuItem("test3", "Hmmm", group);
subIem.onExecute = function() {
	print("Scho!")
}

var subIem = new MenuItem("test4", "Ammm", group);

var subIem = new MenuItem("test5", "Jmmm", group);
