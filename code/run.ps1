param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$CppFile
)

$ErrorActionPreference = 'Stop'

if (-not (Test-Path -LiteralPath $CppFile -PathType Leaf)) {
    Write-Error "File not found: $CppFile"
    exit 1
}

$cpp = Get-Item -LiteralPath $CppFile
$dir = $cpp.DirectoryName
$base = [System.IO.Path]::GetFileNameWithoutExtension($cpp.Name)
$exeName = "$base.exe"
$exePath = Join-Path $dir $exeName
$inputTxt = Join-Path $dir "$base.txt"

Push-Location $dir
try {
    Write-Host "g++ $($cpp.Name) -o $exeName -std=c++20"
    & g++ $cpp.Name -o $exeName -std=c++20
    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }

    if (Test-Path -LiteralPath $inputTxt -PathType Leaf) {
        Write-Host "cat $base.txt | $exeName"
        Get-Content -LiteralPath $inputTxt | & $exePath
    }
    else {
        Write-Host "./$exeName"
        & $exePath
    }
    exit $LASTEXITCODE
}
finally {
    Pop-Location
}
