# Karlsen Ledger Integration

This is the code for the Karlsen embedded app.

## Prerequisite

### With the docker image builder

The app-builder docker image [from this repository](https://github.com/karlsen-network/ledger-app-builder) contains all needed tools and library to build and load an application.
You can download it from the ghcr.io docker repository:

```shell
docker pull ghcr.io/karlsen-network/ledger-app-builder/ledger-app-builder-legacy:latest
```

You can then enter this development environment by executing the following command from the directory of the application `git` repository:

```shell
cd app-karlsen
docker run --rm -ti -v "$(realpath .):/app" --user root ghcr.io/karlsen-network/ledger-app-builder/ledger-app-builder-legacy:latest
```

The application's code will be available from inside the docker container, you can proceed to the following compilation steps to build your app.

## Compilation and load

```shell
make DEBUG=1  # compile optionally with PRINTF
make load     # load the app on the Nano using ledgerblue
```

## Documentation

High level documentation such as [APDU](doc/APDU.md), [commands](doc/COMMANDS.md) and [transaction serialization](doc/TRANSACTION.md) are included in developer documentation which can be generated with [doxygen](https://www.doxygen.nl)

```shell
doxygen .doxygen/Doxyfile
```

the process outputs HTML and LaTeX documentations in `doc/html` and `doc/latex` folders.

## Tests & Continuous Integration

The flow processed in [GitHub Actions](https://github.com/features/actions) is the following:

- Code formatting with [clang-format](http://clang.llvm.org/docs/ClangFormat.html)
- Compilation of the application for Ledger Nano S in [ledger-app-builder](https://github.com/gonner22/ledger-app-builder)
- Unit tests of C functions with [cmocka](https://cmocka.org/) (see [unit-tests/](unit-tests/))
- End-to-end tests with [Speculos](https://github.com/LedgerHQ/speculos) emulator (see [tests/](tests/))
- Code coverage with [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html)/[lcov](http://ltp.sourceforge.net/coverage/lcov.php) and upload to [codecov.io](https://about.codecov.io)
- Documentation generation with [doxygen](https://www.doxygen.nl)

It outputs 3 artifacts:

- `speculos-log` within APDU command/response when executing end-to-end tests
- `code-coverage` within HTML details of code coverage
- `documentation` within HTML auto-generated documentation
