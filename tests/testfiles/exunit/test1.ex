import ExUnit.CaptureIO

test "capture io" do
  result = capture_io(fn ->
    IO.puts "sup"
  end)

  assert result == "sup\n"
end
