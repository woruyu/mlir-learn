func.func @test_lower_add(%0 : !poly.poly<10>, %1 : !poly.poly<10>) {
  %2 = poly.add %0, %1: !poly.poly<10>
  return
}