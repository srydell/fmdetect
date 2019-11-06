defmodule KVTest do
  use ExUnit.Case

  setup do
    {:ok, pid} = KV.start_link()
    {:ok, pid: pid}
  end

  test "stores key-value pairs", context do
    assert KV.put(context[:pid], :hello, :world) == :ok
    assert KV.get(context[:pid], :hello) == :world
  end
end
