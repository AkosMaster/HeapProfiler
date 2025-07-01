@echo off
echo Attaching to '%1'

inject86 Release/glfw3.dll %1
inject86 Release/HeapProfiler.dll %1