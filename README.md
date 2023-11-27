# perconf

A small utility to work with percentage configuration (volume, brightness etc.).

It can be used to create some system UI, based on scripts and outputs of other programs.

## Compilation Requirements
```
make clang 
```

## Build & Install
```sh
# run:
make build
sudo make install
```

## Help
```sh
Usage: perconf [flags]
Flags:
    --help        - display help
    -m <number>   - minimum (including)
    -M <number>   - maximum (including)
    -c <number>   - current value
    -i <number>   - number to add (in %). Can be positive or negative
    -s <number>   - number to set (in %)

        FILE CONFIG
    -FM <file>    - file to read maximum from
    -Fm <file>    - file to read minimum from
    -Fc <file>    - file to read actual value from
    -Fi <file>    - file to read increase from (in %). Can be positive or negative
    -Fs <file>    - file to set number from (in %)
    -Fo <file>    - file to write output to. If not specified - use stdout

        OUTPUT FORMAT
    -f <template> - printf template. Requires one number type (default: "%.lf")

If there is no -[F]<i | s>, then the percentage will be printed out or written to -Fo.

```
