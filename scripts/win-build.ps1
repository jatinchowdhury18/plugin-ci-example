# Build for Windows with Cmake

$ErrorActionPreference="Stop"

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    New-Alias -Name cmake -Value "$Env:ProgramFiles\CMake\bin\cmake.exe"
}

cmake -Bbuild
cmake --build build --config Release --parallel 4
