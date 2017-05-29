#!/usr/bin/env bats

setup() {
  cd "$BATS_TEST_DIRNAME"
  cd ..
}

@test "test compiler with example.go has compiled an executable expected execution results" {
  bin/compiler tests/samples/example.go -o /tmp/__a.out

  run /tmp/__a.out
  expected_result="$(cat tests/samples/compiler_output_samples/example_execution_results.txt)"
  [ "$output" = "$expected_result" ]
}
