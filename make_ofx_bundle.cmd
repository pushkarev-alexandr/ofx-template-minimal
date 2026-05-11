@echo off

set "PLUGIN_NAME=OFXTemplatePlugin"

set "SRC_DLL=%~dp0build\Release\%PLUGIN_NAME%.dll"

set "BUNDLE_DIR=%~dp0%PLUGIN_NAME%\%PLUGIN_NAME%.ofx.bundle\Contents\Win64"
mkdir "%BUNDLE_DIR%" 2>nul

copy /Y "%SRC_DLL%" "%BUNDLE_DIR%\%PLUGIN_NAME%.ofx"

pause
