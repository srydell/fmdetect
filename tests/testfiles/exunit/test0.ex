defmodule MyTest do
  use ExUnit.Case
  use ExUnit.Case, async: true  # for async

  test "the truth" do
    assert 1 + 1 == 2
  end
end
