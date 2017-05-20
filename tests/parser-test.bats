#!/usr/bin/env bats

setup() {
  cd "$BATS_TEST_DIRNAME"
  cd ..
}

@test "test parser with hello_world.go has expected results" {
  result="$(bin/parser < tests/samples/hello_world.go | sed 's/0x[0-9a-f]*/id/g')"
  expected_result="$(cat tests/samples/parser_output_samples/hello_world.txt)"
  [ "$result" = "$expected_result" ]
}

@test "test scanner return status with syntax error" {
  run bin/parser < tests/samples/syntax_error.go
  [ "$status" -eq 1 ]
}
