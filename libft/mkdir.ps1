#powershell script
# Set-ExecutionPolicy Bypass -Scope Process
#via chatgpt, script to loop through sources and make a similar directory structure

# Specify source and destination paths
$srcPath = "srcs"
$objPath = "objs"

# Check if srcPath has subdirectories
$subdirectories = Get-ChildItem -Path $srcPath | Where-Object { $_.PSIsContainer }

# Loop through each subdirectory and create the corresponding directory in objPath
foreach ($subdir in $subdirectories) {
    $objSubdir = Join-Path $objPath $subdir.Name
    if (-not (Test-Path -Path $objSubdir)) {
        New-Item -ItemType Directory -Path $objSubdir -Force > $null
        # Write-Host "Created directory: $objSubdir"
    } else {
        # Write-Host "Directory already exists: $objSubdir"
    }
}

# If srcPath has no subdirectories, create a single directory in objPath
if ($subdirectories.Count -eq 0) {
    $objSingleDir = Join-Path $objPath (Get-Item $srcPath).BaseName
    if (-not (Test-Path -Path $objSingleDir)) {
        New-Item -ItemType Directory -Path $objSingleDir -Force > $null
        # Write-Host "Created directory: $objSingleDir"
    } else {
        # Write-Host "Directory already exists: $objSingleDir"
    }
}
