param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$SourceFile,
    [switch]$Paste
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path -LiteralPath $SourceFile -PathType Leaf)) {
    Write-Error "File not found: $SourceFile"
    exit 1
}

$src = Get-Item -LiteralPath $SourceFile
$dir = $src.DirectoryName
$base = [System.IO.Path]::GetFileNameWithoutExtension($src.Name)
$ext = $src.Extension.ToLower()
$inputFile = Join-Path $dir "$base.in"

if ($ext -ne ".cpp" -and $ext -ne ".py") {
    Write-Error "Unsupported file type: $ext (expected .cpp or .py)"
    exit 1
}

Push-Location $dir
try {
    if ($Paste) {
        Write-Host "gcb > $base.in"
        Get-Clipboard | Set-Content -LiteralPath $inputFile
    }

    if ($ext -eq ".cpp") {
        $exeName = "$base.exe"
        $exePath = Join-Path $dir $exeName

        Write-Host "g++ $($src.Name) -o $exeName -std=c++20"
        & g++ $src.Name -o $exeName -std=c++20
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
    }
    else {
        if (Test-Path -LiteralPath $inputFile -PathType Leaf) {
            Write-Host "cat $base.in | python $($src.Name)"
            Get-Content -LiteralPath $inputFile | & python $src.Name
        }
        else {
            Write-Host "python $($src.Name)"
            & python $src.Name
        }
    }
    $runExit = $LASTEXITCODE

    if ($runExit -eq 0) {
        Write-Host "$($src.Name) > clipboard"
        Get-Content -LiteralPath $src.FullName -Raw | Set-Clipboard
    }

    exit $runExit
}
finally {
    Pop-Location
}
