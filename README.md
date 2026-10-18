# Vending Machine

![CI](https://github.com/<username>/vending-machine/actions/workflows/ci.yml/badge.svg)

A vending machine simulator written in modern C++ (C++20), developed with
safety-critical engineering practices in mind: numbered requirements,
requirement-to-test traceability, strict compiler warnings, static analysis,
sanitizers and continuous integration.

## Building

Requirements: CMake ≥ 3.25, Ninja, a C++20 compiler (GCC 13 / Clang 18).

```bash
cmake --preset debug            # configure (downloads GoogleTest)
cmake --build --preset debug    # build
ctest --preset debug            # run all tests
```

| Preset    | Purpose                                           |
|-----------|---------------------------------------------------|
| `debug`   | Day-to-day development, debugging with gdb        |
| `asan`    | Debug build with AddressSanitizer + UBSan         |
| `release` | Optimised build                                   |

Static analysis (same commands as CI):

```bash
run-clang-tidy -p build/debug -quiet "$(pwd)/(src|include|tests)/"
cppcheck --project=build/debug/compile_commands.json --enable=warning,style,performance,portability \
         --std=c++20 --inline-suppr --suppress='*:*/_deps/*' --suppress=missingIncludeSystem -i build/debug/_deps
```

## Requirements

<!-- One line per requirement. A requirement must be atomic, verifiable and
     unambiguous ("shall"). Never renumber: retired IDs stay retired. -->

| ID      | Requirement | Phase |
|---------|-------------|-------|
| REQ-001 | _TBD_       | A     |

## Traceability

<!-- Every requirement must be covered by at least one test, and every test
     must reference a requirement. -->

| Requirement | Test(s) | Status |
|-------------|---------|--------|
| REQ-001     | _TBD_   | —      |

## Design notes

### Dynamic memory allocation

<!-- Where the program allocates on the heap and why (rule 7). -->

_TBD_

### Error handling

<!-- Why core logic returns `enum class` results instead of throwing. -->

_TBD_

## Bug log

<!-- A real bug found with gdb / valgrind / sanitizers: symptom, how it was
     found, root cause, fix, and the regression test that now covers it. -->

_TBD_

## Workflow

- Backlog in GitHub Issues; one branch per issue (`feature/<n>-<short-name>`).
- [Conventional Commits](https://www.conventionalcommits.org/) (`feat:`, `fix:`, `test:`, `docs:`, `build:`, `ci:` …).
- Pull request per branch; CI must be green; `main` is protected.

**Definition of Done:** builds without warnings · tests pass and reference a
requirement · clang-tidy clean · traceability table updated · PR reviewed and merged.
