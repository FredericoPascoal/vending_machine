# Vending Machine

![CI](https://github.com/FredericoPascoal/vending_machine/actions/workflows/ci.yml/badge.svg)

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
| REQ-001 | The system shall represent product prices exactly, with a precision of one cent, so that arithmetic on prices introduces no rounding error. | A |
| REQ-002 | The system shall create a product when all its attributes are valid, and shall make its identifier, name, price and type-specific attribute (volume for a drink, calories for a snack) available unchanged. | A |
| REQ-003 | The system shall reject the creation of a product whose identifier is empty or consists only of whitespace, reporting that the identifier is invalid. | A |
| REQ-004 | The system shall reject the creation of a product whose name is empty or consists only of whitespace, reporting that the name is invalid. | A |
| REQ-005 | The system shall reject the creation of a product with a price outside the range [0.01, 100.00] EUR, reporting that the price is invalid. | A |
| REQ-006 | The system shall reject the creation of a drink with a volume outside the range [1, 1500] ml, reporting that the volume is invalid. | A |
| REQ-007 | The system shall reject the creation of a snack with calories outside the range [1, 500] kcal, reporting that the calories are invalid. | A |
| REQ-008 | When more than one attribute is invalid, the system shall report only the first invalid one, in the order: identifier, name, price, volume/calories. | A |
| REQ-009 | The description of a drink shall contain its name, its price in euros with two decimal places (e.g. 1.05 EUR) and its volume in ml (e.g. 330 ml). | A |
| REQ-010 | The description of a snack shall contain its name, its price in euros with two decimal places (e.g. 0.95 EUR) and its calories in kcal (e.g. 250 kcal). | A |

## Traceability

<!-- Every requirement must be covered by at least one test, and every test
     must reference a requirement. -->

| Requirement | Test(s) | Status |
|-------------|---------|--------|
| REQ-001     | _TBD_   | —      |
| REQ-002     | _TBD_   | —      |
| REQ-003     | _TBD_   | —      |
| REQ-004     | _TBD_   | —      |
| REQ-005     | _TBD_   | —      |
| REQ-006     | _TBD_   | —      |
| REQ-007     | _TBD_   | —      |
| REQ-008     | _TBD_   | —      |
| REQ-009     | _TBD_   | —      |
| REQ-010     | _TBD_   | —      |

## Design notes

### Dynamic memory allocation

<!-- Where the program allocates on the heap and why (rule 7). -->

_TBD_

### Error handling

<!-- Why core logic returns `enum class` results instead of throwing. -->

_TBD_

### Price representation

### Architectural Decision: Currency and Price Representation

* **Decision**: We chose to represent all monetary values and prices as standard fixed-width signed 64-bit integers (`std::int64_t`) counting the total amount in cents (e.g., 1.00 EUR is stored as 100).
* **Alternatives considered**: We evaluated using floating-point numbers (`double`) for direct decimal representation, as well as unsigned integers (`unsigned int`) since prices are inherently non-negative.
* **Rationale**: Floating-point numbers fail due to binary precision limitations, incorrectly rendering 10 accumulated dimes as `0.99999999999999989` instead of a solid 1.00. Unsigned integers are also dangerous because any negative transaction or calculation (such as a math mistake calculating change: `50 - 100`) triggers an underflow, wrapping the value around to a catastrophic number like `4294967246`.
* **Consequences**: By choosing cents as integers, we guarantee absolute mathematical precision and cross-platform type safety, but we now require a custom formatting function to divide the internal value by 100 and properly print it to conform with REQ-009/010 (e.g., displaying `105` as `1.05 EUR`).


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
