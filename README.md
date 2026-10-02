# sncli — Snovalang Unified CLI

`snl` is the command that drives the Snovalang compiler (`snovac`), the runtime (`snovart`), and the standard library (`snova-std`). This repository builds that wrapper. The installed command name is `snl`.

## Build

This repository has no separate install script. Build the wrapper with:

```bash
make
```

That writes `bin/snl` (or `bin/snl.exe` on Windows). The `snovac` repository installs the same command as `snl` via `install.sh`, `install.ps1`, or `make install`.

## Usage

```bash
# Run a Snovalang file or project with embedded runtime
snl run <file.snova|--project>

# Compile to a standalone native binary
snl build <file.snova|--project> [-o output]

# Verify types, syntax, and strict architectural rules
snl check <file.snova|--project>

# Manage dependencies
snl get [url]
snl tidy

# Check version
snl --version
```

## License
MIT License
