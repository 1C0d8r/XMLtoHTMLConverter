TARGETS_$(d) := run_tests
TARGETS_$(d) := x64\Release\XMLtoHTML.exe


VAR :="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
export PATH:=$(MSBUILD)

MSUNITTEST=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe

x64\Release\XMLtoHTML.exe: 
	$(VAR) /t:Build /property:OutputPath=..\..\..\Debug /p:Configuration=Release XMLtoHTML.sln
	
run_tests: x64\Release\XMLtoHTML.exe
	$(MSUNITTEST) x64\Release\Tests.dll /platform:x64
	

clean:
	del x64\Release\* XMLtoHTML\x64\Release\* Tests\x64\Release\* 
	