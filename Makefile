#############################################################################
# Makefile for building: ImBel
# Generated by qmake (3.0) (Qt 5.0.1) on: Sat Apr 6 04:17:28 2013
# Project:  ImBel.pro
# Template: app
# Command: D:\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\bin\qmake.exe -spec win32-msvc2010 CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug -o Makefile ImBel.pro
#############################################################################

MAKEFILE      = Makefile

first: debug
install: debug-install
uninstall: debug-uninstall
QMAKE         = D:\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = del
SYMLINK       = 
DEL_DIR       = rmdir
MOVE          = move
SUBTARGETS    =  \
		debug \
		release


debug: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug uninstall
release: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release uninstall

Makefile: ImBel.pro ..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\win32-msvc2010\qmake.conf ..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\spec_pre.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\common\shell-win32.conf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\qconfig.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_axbase.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_axcontainer.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_axserver.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_bootstrap.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_clucene.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_concurrent.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_core.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_declarative.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_designer.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_designercomponents.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_gui.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_help.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_multimedia.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_multimediawidgets.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_network.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_opengl.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_platformsupport.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_printsupport.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_qml.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_qmldevtools.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_qmltest.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_qtmultimediaquicktools.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_quick.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_quickparticles.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_script.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_scripttools.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_sql.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_svg.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_testlib.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_uitools.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_v8.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_webkit.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_webkitwidgets.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_widgets.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_xml.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_xmlpatterns.pri \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\qt_functions.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\qt_config.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\win32-msvc2010\qmake.conf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\spec_post.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\exclusive_builds.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\default_pre.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\win32\default_pre.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\debug.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\debug_and_release.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\default_post.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\shared.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\qml_debug.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\declarative_debug.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\win32\rtti.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\warn_on.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\qt.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\resources.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\moc.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\win32\opengl.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\uic.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\win32\windows.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\testcase_targets.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\exceptions.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\yacc.prf \
		..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\lex.prf \
		ImBel.pro \
		D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/Qt5Widgets.prl \
		D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/Qt5Gui.prl \
		D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/Qt5Core.prl \
		D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/libEGLd.prl \
		D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/libGLESv2d.prl
	$(QMAKE) -spec win32-msvc2010 CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug -o Makefile ImBel.pro
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\spec_pre.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\common\shell-win32.conf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\qconfig.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_axbase.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_axcontainer.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_axserver.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_bootstrap.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_clucene.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_concurrent.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_core.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_declarative.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_designer.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_designercomponents.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_gui.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_help.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_multimedia.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_multimediawidgets.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_network.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_opengl.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_platformsupport.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_printsupport.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_qml.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_qmldevtools.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_qmltest.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_qtmultimediaquicktools.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_quick.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_quickparticles.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_script.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_scripttools.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_sql.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_svg.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_testlib.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_uitools.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_v8.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_webkit.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_webkitwidgets.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_widgets.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_xml.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\modules\qt_lib_xmlpatterns.pri:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\qt_functions.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\qt_config.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\win32-msvc2010\qmake.conf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\spec_post.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\exclusive_builds.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\default_pre.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\win32\default_pre.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\debug.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\debug_and_release.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\default_post.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\shared.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\qml_debug.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\declarative_debug.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\win32\rtti.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\warn_on.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\qt.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\resources.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\moc.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\win32\opengl.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\uic.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\win32\windows.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\testcase_targets.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\exceptions.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\yacc.prf:
..\..\..\Programs\Qt\Qt5.0.1\5.0.1\msvc2010\mkspecs\features\lex.prf:
ImBel.pro:
D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/Qt5Widgets.prl:
D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/Qt5Gui.prl:
D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/Qt5Core.prl:
D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/libEGLd.prl:
D:/Programs/Qt/Qt5.0.1/5.0.1/msvc2010/lib/libGLESv2d.prl:
qmake: FORCE
	@$(QMAKE) -spec win32-msvc2010 CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug -o Makefile ImBel.pro

qmake_all: FORCE

make_first: debug-make_first release-make_first FORCE
all: debug-all release-all FORCE
clean: debug-clean release-clean FORCE
	-$(DEL_FILE) ImBel.exp
	-$(DEL_FILE) ImBel.ilk
	-$(DEL_FILE) vc*.pdb
	-$(DEL_FILE) vc*.idb
distclean: debug-distclean release-distclean FORCE
	-$(DEL_FILE) Makefile
	-$(DEL_FILE) ImBel.pdb

debug-mocclean:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocclean
release-mocclean:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocclean
mocclean: debug-mocclean release-mocclean

debug-mocables:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocables
release-mocables:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocables
mocables: debug-mocables release-mocables

check: first
FORCE:

$(MAKEFILE).Debug: Makefile
$(MAKEFILE).Release: Makefile
