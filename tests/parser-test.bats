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

@test "test parser with example.go has expected results" {
  result="$(bin/parser < tests/samples/example.go | sed 's/0x[0-9a-f]*/id/g')"
  expected_result="$(cat tests/samples/parser_output_samples/example.txt)"
  [ "$result" = "$expected_result" ]
}

@test "test parser with sigma.go has expected results" {
  result="$(bin/parser < tests/samples/sigma.go | sed 's/0x[0-9a-f]*/id/g')"
  expected_result="$(cat tests/samples/parser_output_samples/sigma.txt)"
  [ "$result" = "$expected_result" ]
}

@test "test parser return status with syntax error" {
  run bin/parser < tests/samples/syntax_error.go
  [ "$status" -eq 1 ]
}
