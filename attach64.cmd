@echo off
echo Attaching to '%1'

inject64 x64/Release/glfw3.dll %1
inject64 x64/Release/HeapProfiler.dll %1