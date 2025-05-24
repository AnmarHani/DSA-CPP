Macro	Purpose
REQUIRE	Fails and stops test if condition is false
CHECK	Fails but continues test
REQUIRE_THROWS	Fails unless expression throws exception
REQUIRE_NOTHROW	Fails if expression throws
REQUIRE_EQ(a, b)	Fails if a != b (Catch2 v3+)

Macro/Function	Purpose
#define CATCH_CONFIG_MAIN	Generates main() for your test binary
TEST_CASE	Defines a test case (group of related tests)
SECTION	Subdivides a test case into scenarios
REQUIRE	Asserts a condition must be true (like assert)
REQUIRE_FALSE	Asserts a condition must be false

```
#include <catch2/generators/catch_generators.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("square function") {
    int input = GENERATE(1, 2, 3, 4);
    REQUIRE(square(input) == input * input);
}
```

```
#define CATCH_CONFIG_RUNNER
#include <catch2/catch_session.hpp>

int main(int argc, char* argv[]) {
    // Optional setup
    Catch::Session session;

    int returnCode = session.run(argc, argv);

    // Optional teardown
    return returnCode;
}
```

```
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/catch_test_macros.hpp>
using Catch::Matchers::Contains;

TEST_CASE("String test") {
    std::string name = "Anmar";
    REQUIRE_THAT(name, Contains("Anm"));
}
```