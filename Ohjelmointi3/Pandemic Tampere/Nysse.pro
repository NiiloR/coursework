TEMPLATE = subdirs

SUBDIRS += \
	CourseLib \
        Game \
        Statstest

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib
