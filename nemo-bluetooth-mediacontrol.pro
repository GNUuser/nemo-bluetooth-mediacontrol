TEMPLATE = subdirs
SUBDIRS += lib plugin test
lib.target = lib-target
plugin.depends = lib-target
test.depends = lib-target
