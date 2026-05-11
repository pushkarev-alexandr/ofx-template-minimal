@echo off

set "OFX_PLUGIN_PATH=%~dp0OFXTemplatePlugin"

if exist "C:\Users\pushk\AppData\Local\Temp\nuke\ofxplugincache" (
    rmdir /S /Q "C:\Users\pushk\AppData\Local\Temp\nuke\ofxplugincache"
)

"C:\Program Files\Nuke16.0v7\Nuke16.0.exe" --nukex
