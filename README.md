# snl — Snovalang command

`snl` is the command that drives the Snovalang compiler (`snovac`), the runtime (`snovart`), and the standard library (`snova-std`). This repository builds that wrapper. The installed command name is `snl`.

## Install and update

Install and update `snl` from the [snovac](https://github.com/snovalang/snovac) repository. `install.sh` is a POSIX `sh` script for Linux and macOS. `install.ps1` is the PowerShell script for Windows. With no extra arguments, each script installs `snl` when it is missing and updates it when it is already installed.

### macOS and Linux

```sh
curl -fsSL https://raw.githubusercontent.com/snovalang/snovac/master/install.sh | sh
```

Update explicitly:

```sh
curl -fsSL https://raw.githubusercontent.com/snovalang/snovac/master/install.sh | sh -s -- --update
```

### Windows (PowerShell)

```powershell
irm https://raw.githubusercontent.com/snovalang/snovac/master/install.ps1 | iex
```

Update explicitly:

```powershell
$env:SNOVA_UPDATE = '1'; irm https://raw.githubusercontent.com/snovalang/snovac/master/install.ps1 | iex
```

From a clone, the same scripts accept `sh install.sh --update` and `powershell -ExecutionPolicy Bypass -File install.ps1 -Update`. `snovac` also installs `snl` with `make install`.

## Build

This repository builds the `snl` wrapper:

```bash
make
```

That writes `bin/snl` (or `bin/snl.exe` on Windows).

## Usage

```bash
# Run a Snovalang file or project with embedded runtime
snl run <file.snl|file.sns|--project>

# Compile to a standalone native binary
snl build <file.snl|file.sns|--project> [-o output]

# Verify types, syntax, and strict architectural rules
snl check <file.snl|file.sns|--project>

# Manage dependencies
snl get [url]
snl tidy

# Check version
snl --version
```

## License

This project is licensed under the [Apache License, Version 2.0](LICENSE).
Copyright 2026 Snovalang contributors. See [NOTICE](NOTICE).
