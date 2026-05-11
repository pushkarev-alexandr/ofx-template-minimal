Минимальный шаблон **ImageEffect** плагина для OpenFX — отправная точка, поверх которой можно добавлять свой код. В проекте есть скрипты для сборки, создания OFX bundle и запуска Nuke с собранным плагином.

## Подготовка. Для работы текущего проекта нужно:
- чтобы был установлен и была произведена первичная настройка **Git**
- должен быть установлен **CMake**
- должен быть установлен **vcpkg** и произведён [bootstrap](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell#1---set-up-vcpkg)
- должна быть установлена **Visual Studio** с компилятором **MSVC** (скрипты ожидают стандартный путь до `vcvars64.bat`).

> **Важно:** скрипты [build.cmd](build.cmd), [configure.cmd](configure.cmd) и [start_nuke.cmd](start_nuke.cmd) содержат абсолютные пути, характерные для конкретной машины (путь к Visual Studio, к Nuke, к кэшу плагинов). Перед использованием откройте эти файлы и подправьте пути под свою систему.

## Содержимое проекта:
Первые скрипты перечислены **в порядке их типичного запуска** при работе с проектом.
- [setup_openfx_include.cmd](setup_openfx_include.cmd) - скачает папку `include` с заголовочными файлами для сборки `OpenFX` плагинов
- [configure.cmd](configure.cmd) - инициализирует среду **MSVC** и запускает `cmake -B build -S .` для генерации файлов сборки в папке `build`
- [build.cmd](build.cmd) - инициализирует среду **MSVC** и выполняет `cmake --build build --config Release` для сборки проекта
- [make_ofx_bundle.cmd](make_ofx_bundle.cmd) - после успешной сборки копирует `build\Release\OFXTemplatePlugin.dll` в структуру бандла `OFXTemplatePlugin\OFXTemplatePlugin.ofx.bundle\Contents\Win64\OFXTemplatePlugin.ofx`
- [start_nuke.cmd](start_nuke.cmd) - очищает кэш OFX‑плагинов Nuke и запускает Nuke с нашим собранным плагином
- [include/](include/) - непосредственно сама папка с заголовочными файлами для **OFX** плагинов
- [src/temaplate.cpp](src/temaplate.cpp) - минимальный вариант **OFX** плагина
- [compile_flags.txt](compile_flags.txt) - минимальная настройка для `clangd`, чтобы он правильно понимал код: стандарт C++17 (`-std=c++17`) и include‑путь к заголовкам OFX (`-Iinclude`). Используется вместо стандартного `CMAKE_EXPORT_COMPILE_COMMANDS`, который здесь не подходит, потому что проект собирается под **MSVC** с генератором **Visual Studio**, и **CMake** не создаёт `compile_commands.json`.

