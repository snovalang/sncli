# sncli — Snovalang Unified CLI

`sncli` is the unified command-line toolchain and orchestrator for the Snovalang programming language. It seamlessly binds the compiler (`snovac`), the runtime (`snovart`), and the standard library (`snova-std`).

## Installation & Build

```bash
make
```

Produces `bin/sncli` (or `bin/sncli.exe` on Windows).

## Usage

```bash
# Run a Snovalang file or project with embedded runtime
sncli run <file.snova|--project>

# Compile to a standalone native binary
sncli build <file.snova|--project> [-o output]

# Verify types, syntax, and strict architectural rules
sncli check <file.snova|--project>

# Manage dependencies
sncli get [url]
sncli tidy

# Check version
sncli --version
```

## License
MIT License
