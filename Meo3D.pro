
TEMPLATE = subdirs

SUBDIRS = engine editor


# where to find the sub projects - give the folders
engine.subdir = engine
editor.subdir = editor

# what subproject depends on others
editor.depends = engine
