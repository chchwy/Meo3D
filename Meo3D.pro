
TEMPLATE = subdirs

SUBDIRS = \
  editor \
  engine

# build the project sequentially as listed in SUBDIRS!
CONFIG += ordered

# where to find the sub projects - give the folders
engine.subdir = engine
editor.subdir = editor

# what subproject depends on others
editor.depends = engine
