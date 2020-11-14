@echo on

set "MAIN_WORKSPACE=%~1"
set "THIS_WORKSPACE=%~2"

::ENVCONF_DEVENV 
::ENVCONF_MSBUILD 

::-------------------------------------------------------------------------------------
::compile and run
powershell %MAIN_WORKSPACE%/exec.cmd %THIS_WORKSPACE% python3 /wcore/workspace/nstimer/prj.nstimer-test.py -a vs2019 win32

cd %THIS_WORKSPACE%/nstimer/build/nstimer-test_win32_vs2019

"%ENVCONF_DEVENV%" _this_.sln /Build Debug

"bin/x32/Debug/_nstimer-test.exe"

::-------------------------------------------------------------------------------------
::run RunCodeAnalysis on Release
powershell %MAIN_WORKSPACE%/exec.cmd %THIS_WORKSPACE% python3 /wcore/workspace/nstimer/prj.nstimer.py vs2019 win32

cd %THIS_WORKSPACE%/nstimer/build/nstimer_win32_vs2019

"%ENVCONF_MSBUILD%" _this_.sln /m /p:RunCodeAnalysis=true /p:Configuration=Release /p:Platform=Win32
