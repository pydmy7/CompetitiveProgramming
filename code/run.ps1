param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$CppFile,
    [switch]$Paste
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path -LiteralPath $CppFile -PathType Leaf)) {
    Write-Error "File not found: $CppFile"
    exit 1
}

$cpp = Get-Item -LiteralPath $CppFile
$dir = $cpp.DirectoryName
$base = [System.IO.Path]::GetFileNameWithoutExtension($cpp.Name)
$exeName = "$base.exe"
$exePath = Join-Path $dir $exeName
$inputFile = Join-Path $dir "$base.in"

Push-Location $dir
try {
    if ($Paste) {
        Write-Host "gcb > $base.in"
        Get-Clipboard | Set-Content -LiteralPath $inputFile
    }

    Write-Host "g++ $($cpp.Name) -o $exeName -std=c++20"
    & g++ $cpp.Name -o $exeName -std=c++20
    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }

    if (Test-Path -LiteralPath $inputFile -PathType Leaf) {
        Write-Host "cat $base.in | ./$exeName"
        Get-Content -LiteralPath $inputFile | & $exePath
    }
    else {
        Write-Host "./$exeName"
        & $exePath
    }
    $runExit = $LASTEXITCODE

    Write-Host "$($cpp.Name) > clipboard"
    Get-Content -LiteralPath $cpp.FullName -Raw | Set-Clipboard

    exit $runExit
}
finally {
    Pop-Location
}
