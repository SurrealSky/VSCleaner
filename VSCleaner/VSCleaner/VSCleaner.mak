# Microsoft Developer Studio Generated NMAKE File, Based on VSCleaner.dsp
!IF "$(CFG)" == ""
CFG=VSCleaner - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VSCleaner - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VSCleaner - Win32 Release" && "$(CFG)" != "VSCleaner - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VSCleaner.mak" CFG="VSCleaner - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VSCleaner - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VSCleaner - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VSCleaner - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\Bin\Release\VSCleaner.exe"


CLEAN :
	-@erase "$(INTDIR)\AddFileTypeDialog.obj"
	-@erase "$(INTDIR)\DirDialog.obj"
	-@erase "$(INTDIR)\DirTreeCtrl.obj"
	-@erase "$(INTDIR)\FileManager.obj"
	-@erase "$(INTDIR)\FileTypeDialog.obj"
	-@erase "$(INTDIR)\HookFileManager.obj"
	-@erase "$(INTDIR)\ResizeCtrl.obj"
	-@erase "$(INTDIR)\ResultDialog.obj"
	-@erase "$(INTDIR)\SortStringArray.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VSCleaner.obj"
	-@erase "$(INTDIR)\VSCleaner.pch"
	-@erase "$(INTDIR)\VSCleaner.res"
	-@erase "$(INTDIR)\VSCleanerDlg.obj"
	-@erase "..\Bin\Release\VSCleaner.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VSCleaner.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\VSCleaner.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VSCleaner.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\VSCleaner.pdb" /machine:I386 /out:"../Bin/Release/VSCleaner.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DirDialog.obj" \
	"$(INTDIR)\DirTreeCtrl.obj" \
	"$(INTDIR)\FileManager.obj" \
	"$(INTDIR)\FileTypeDialog.obj" \
	"$(INTDIR)\ResizeCtrl.obj" \
	"$(INTDIR)\ResultDialog.obj" \
	"$(INTDIR)\SortStringArray.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VSCleaner.obj" \
	"$(INTDIR)\VSCleanerDlg.obj" \
	"$(INTDIR)\VSCleaner.res" \
	"$(INTDIR)\HookFileManager.obj" \
	"$(INTDIR)\AddFileTypeDialog.obj"

"..\Bin\Release\VSCleaner.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VSCleaner - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\Bin\Debug\VSCleanerD.exe"


CLEAN :
	-@erase "$(INTDIR)\AddFileTypeDialog.obj"
	-@erase "$(INTDIR)\DirDialog.obj"
	-@erase "$(INTDIR)\DirTreeCtrl.obj"
	-@erase "$(INTDIR)\FileManager.obj"
	-@erase "$(INTDIR)\FileTypeDialog.obj"
	-@erase "$(INTDIR)\HookFileManager.obj"
	-@erase "$(INTDIR)\ResizeCtrl.obj"
	-@erase "$(INTDIR)\ResultDialog.obj"
	-@erase "$(INTDIR)\SortStringArray.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VSCleaner.obj"
	-@erase "$(INTDIR)\VSCleaner.pch"
	-@erase "$(INTDIR)\VSCleaner.res"
	-@erase "$(INTDIR)\VSCleanerDlg.obj"
	-@erase "$(OUTDIR)\VSCleanerD.pdb"
	-@erase "..\Bin\Debug\VSCleanerD.exe"
	-@erase "..\Bin\Debug\VSCleanerD.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VSCleaner.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\VSCleaner.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VSCleaner.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\VSCleanerD.pdb" /debug /machine:I386 /out:"../Bin/Debug/VSCleanerD.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\DirDialog.obj" \
	"$(INTDIR)\DirTreeCtrl.obj" \
	"$(INTDIR)\FileManager.obj" \
	"$(INTDIR)\FileTypeDialog.obj" \
	"$(INTDIR)\ResizeCtrl.obj" \
	"$(INTDIR)\ResultDialog.obj" \
	"$(INTDIR)\SortStringArray.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VSCleaner.obj" \
	"$(INTDIR)\VSCleanerDlg.obj" \
	"$(INTDIR)\VSCleaner.res" \
	"$(INTDIR)\HookFileManager.obj" \
	"$(INTDIR)\AddFileTypeDialog.obj"

"..\Bin\Debug\VSCleanerD.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("VSCleaner.dep")
!INCLUDE "VSCleaner.dep"
!ELSE 
!MESSAGE Warning: cannot find "VSCleaner.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VSCleaner - Win32 Release" || "$(CFG)" == "VSCleaner - Win32 Debug"
SOURCE=.\AddFileTypeDialog.cpp

"$(INTDIR)\AddFileTypeDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\DirDialog.cpp

"$(INTDIR)\DirDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\DirTreeCtrl.cpp

"$(INTDIR)\DirTreeCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\FileManager.cpp

"$(INTDIR)\FileManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\FileTypeDialog.cpp

"$(INTDIR)\FileTypeDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\HookFileManager.cpp

"$(INTDIR)\HookFileManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\ResizeCtrl.cpp

"$(INTDIR)\ResizeCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\ResultDialog.cpp

"$(INTDIR)\ResultDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\SortStringArray.cxx

"$(INTDIR)\SortStringArray.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "VSCleaner - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VSCleaner.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VSCleaner.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VSCleaner - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VSCleaner.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VSCleaner.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\VSCleaner.cpp

"$(INTDIR)\VSCleaner.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"


SOURCE=.\VSCleaner.rc

"$(INTDIR)\VSCleaner.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\VSCleanerDlg.cpp

"$(INTDIR)\VSCleanerDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSCleaner.pch"



!ENDIF 

