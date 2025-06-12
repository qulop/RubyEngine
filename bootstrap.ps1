function Get-Confirmation() {
    param (
        [string]$prompt
    )

    Write-Host -NoNewline ($prompt + " [y/n]: ")
    while ($true) {
        $res = Read-Host
        $res.ToLower()

        if ($res -eq "no" -or $res -eq "n") {
            return $false
        }
        elseif ($res -eq "yes" -or $res -eq "y") {
            return $true
        }

        Write-Output "Incorrect input. Please, try again: "
    }
}

function Enter-Venv() {
    if (-not (Test-Path -Path "venv" -PathType Container)) {
        python3 -m venv venv
    }

    .\venv\Scripts\Activate.ps1
}

function Invoke-Setup() {
    Set-Location -Path "scripts/"
    Write-Output "Trying to create virtual enviroment..."

    try {
        Enter-Venv
    }
    catch  {
        if (-not (Get-Confirmation "venv package does not found. Would you like to install?")) {
            Write-Output "Failed to process bootstrap for setup script. Leaving..."
            exit 0
        }

        python3 -m pip install --user virtualenv
        Enter-Venv
    }

    Write-Output "Installing the required libraries from requirements.txt..."
    .\venv\Scripts\pip3.exe install -r requirements.txt

    .\venv\Scripts\python.exe main.py
    deactivate
    Set-Location -Path "../"
}



$is_python = Get-Command python3 -ErrorAction SilentlyContinue
if ($is_python) {
    Invoke-Setup
    exit 0
}

Write-Host -NoNewline "Python does not found. "
if (-not (Get-Confirmation "To continue setup you must install python. Would you like to continue?")) {
    exit 0
}

if (-not (Get-Command (winget search python -ErrorAction SilentlyContinue))) {
    Write-Output "Failed to find python package via WinGet. Install it manually and try again."
    exit 0
}

Write-Output "Ok"
exit 0

if (-not (Get-Command (winget install python -ErrorAction SilentlyContinue))) {
    Write-Output "Failed to install python package. Install it manually and try again."
    exit 0
}

Write-Output "Python has been successfully installed. Let's continue with the setup..."
Invoke-Setup
