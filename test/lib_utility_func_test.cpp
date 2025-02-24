#include <gtest/gtest.h>

#include <bitset>

#include "lib/utility/func.hpp"

/* *** *** *** *** *** Clear - Funtamental Types & STL *** *** *** *** *** */
TEST(Clear, NonPointerNonConst) {
  int x{42};
  clear(x);
  EXPECT_EQ(x, 0);

  double d{std::numbers::pi};
  clear(d);
  EXPECT_EQ(d, 0.0);

  std::string s{"hello"};
  clear(s);
  EXPECT_EQ(s, "");

  bool b{true};
  clear(b);
  EXPECT_FALSE(b);

  char c{'a'};
  clear(c);
  EXPECT_EQ(c, '\0');

  unsigned int u{100};
  clear(u);
  EXPECT_EQ(u, 0U);

  long long ll{-1234567890123456789LL};
  clear(ll);
  EXPECT_EQ(ll, 0LL);

  float f{1.5F};
  clear(f);
  EXPECT_EQ(f, 0.0F);
}

TEST(Clear, NonPointerConst) {
  const int x{42};
  clear(x);
  EXPECT_EQ(x, 0);

  const double d{std::numbers::pi};
  clear(d);
  EXPECT_EQ(d, 0.0);

  const bool cb{true};
  clear(cb);
  EXPECT_EQ(cb, false);
  // EXPECT_FALSE(cb);  // <-- does not work here!

  const char cc{'x'};
  clear(cc);
  EXPECT_EQ(cc, '\0');

  const float cf{1.5F};
  clear(cf);
  EXPECT_EQ(cf, 0);
}

TEST(Clear, PointerNonConst) {
  auto* ptr{new int(5)};
  clear(ptr);
  EXPECT_EQ(*ptr, 0);
  delete ptr;

  auto* arr{new double[3]{1.2, 3.4, 5.6}};
  for (int i = 0; i < 3; ++i) {
    clear(arr[i]);
    EXPECT_EQ(arr[i], 0.0);
  }
  delete[] arr;

  auto* fptr = new float[5]{1.2F, 3.4F, 5.6F, 7.8F, 9.0F};
  for (int i = 0; i < 5; ++i) {
    clear(fptr[i]);
    EXPECT_EQ(fptr[i], 0.0F);
  }
  delete[] fptr;

  int c_type_arr[5] = {1, 2, 3, 4, 5};
  int* c_ptr = c_type_arr;
  clear(c_ptr);
  EXPECT_EQ(*c_ptr, 0);
  EXPECT_EQ(c_ptr, c_type_arr);
}

TEST(Clear, PointerConst) {
  const int* ptr{new int(7)};
  clear(ptr);
  EXPECT_EQ(*ptr, 0);  // Constness is removed for clearing
  delete ptr;

  const double value{1.2345};
  const double* p_value = &value;
  clear(p_value);
  EXPECT_EQ(*p_value, 0);
}

TEST(Clear, Map) {
  std::map<std::string, int> my_map = {{"a", 10}, {"b", 20}};
  clear(my_map);
  EXPECT_TRUE(my_map.empty());  // Empty map
}

TEST(Clear, Bitset) {
  std::bitset<8> bits(0b11010110);
  clear(bits);
  EXPECT_EQ(bits.to_string(), "00000000");  // All bits cleared
}

TEST(Clear, Byte) {
  std::byte b{0xAB};
  clear(b);
  EXPECT_EQ(static_cast<int>(b), 0);  // Byte set to zero
}

TEST(Clear, NestedContainers) {
  std::map<int, std::vector<std::string>> nested_map = {{1, {"a", "b"}},
                                                        {2, {"c"}}};
  clear(nested_map);
  EXPECT_TRUE(nested_map.empty());
  EXPECT_TRUE(nested_map[1].empty());
}

TEST(Clear, Array) {
  int arr[] = {1, 2, 3};
  clear(arr);
  EXPECT_TRUE(std::all_of(std::begin(arr), std::end(arr),
                          [](int x) { return x == 0; }));
}

TEST(Clear, PointerOwnership) {
  struct Data {
    int value{};
  };

  std::unique_ptr<Data, void (*)(Data*)> ptr(new Data{5}, [](Data* data) {
    clear(data);  // Clear data before destruction
    delete data;
  });
}

/* *** *** *** *** *** Clear - Move-constructible Types *** *** *** *** *** */
TEST(Clear, MoveConstructible) {
  std::string str{"Hello"};
  clear(str);
  EXPECT_EQ(str, "");
}

TEST(Clear, NonMoveConstructible) {
  std::vector<int> vec{1, 2, 3};
  clear(vec);
  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.size(), 0);
}

TEST(Clear, ConstMoveConstructible) {
  const std::string str{"Hello"};
  clear(str);
  EXPECT_EQ(str, "");
}

TEST(Clear, PointerToMoveConstructible) {
  auto* str_ptr{new std::string("Hello")};
  clear(str_ptr);
  EXPECT_EQ(*str_ptr, "");
  delete str_ptr;
}

TEST(Clear, PointerToNonMoveConstructible) {
  auto* vec_ptr{new std::vector<int>{1, 2, 3}};
  clear(vec_ptr);
  EXPECT_TRUE(vec_ptr->empty());
  delete vec_ptr;
}

TEST(Clear, ConstPointerToTrivialType) {
  const int* int_ptr{new int(42)};
  clear(int_ptr);
  EXPECT_EQ(*int_ptr, 0);
  delete int_ptr;
}

TEST(Clear, CustomMoveConstructible) {
  struct MoveConstructibleType {
    MoveConstructibleType() = default;
    explicit MoveConstructibleType(int v) : value{std::move(v)} {}
    // MoveConstructibleType(const MoveConstructibleType&) = delete;
    // auto operator=(const MoveConstructibleType&) -> MoveConstructibleType& =
    // delete;
    MoveConstructibleType(MoveConstructibleType&&) = default;
    auto operator=(MoveConstructibleType&&) -> MoveConstructibleType& = default;
    int value{0};
  };

  MoveConstructibleType obj{};
  obj.value = 42;
  EXPECT_EQ(obj.value, 42);
  clear(obj);
  EXPECT_EQ(obj.value, 0);

  MoveConstructibleType o(123);
  EXPECT_EQ(o.value, 123);
  clear(o);
  EXPECT_EQ(o.value, 0);
}

TEST(Clear, CustomMoveConstructibleStruct) {
  struct MoveOnlyStruct {
    MoveOnlyStruct() = default;
    MoveOnlyStruct(MoveOnlyStruct&&) = default;
    auto operator=(MoveOnlyStruct&&) -> MoveOnlyStruct& = default;
    int value{42};
  };

  MoveOnlyStruct s{};
  s.value = 10;
  clear(s);
  EXPECT_EQ(42, s.value);

  std::vector<MoveOnlyStruct> vec(3);
  clear(vec);
  EXPECT_EQ(vec.size(), 0);
}

TEST(Clear, NonTrivialType) {
  class NonTrivialType {
   public:
    NonTrivialType() = default;
    explicit NonTrivialType(int val) : value(val) {}
    int value;
  };
  NonTrivialType obj(5);
  clear(obj);
  EXPECT_EQ(obj.value, 0);
}

/* *** *** *** *** Clear - Non-move-constructible Types *** *** *** *** */
TEST(Clear, NonMoveConstructibleTypes) {
  std::array<int, 3> empty{};
  std::array<int, 3> arr = {1, 2, 3};
  clear(arr);
  EXPECT_EQ(arr, empty);
}

template <typename T>
struct NonMoveConstructible {
  NonMoveConstructible() = default;
  explicit NonMoveConstructible(T t) : value{std::move(t)} {}
  NonMoveConstructible(const NonMoveConstructible&) = default;
  NonMoveConstructible(NonMoveConstructible&&) = delete;
  auto operator=(const NonMoveConstructible&) -> NonMoveConstructible& =
                                                     default;
  auto operator=(NonMoveConstructible&&) -> NonMoveConstructible& = default;

  T value{};
};

TEST(Clear, CustomNonMoveConstructible) {
  NonMoveConstructible<double> obj{};
  obj.value = std::numbers::e;
  clear(obj);
  EXPECT_EQ(obj.value, double{});
}

TEST(Clear, ConstCustomNonMoveConstructible) {
  const NonMoveConstructible<int> obj{42};
  clear(obj);
  EXPECT_EQ(obj.value, int{});
}

TEST(Clear, PointerToCustomNonMoveConstructible) {
  auto* ptr = new NonMoveConstructible<float>(1.23F);
  clear(ptr);
  EXPECT_EQ(ptr->value, float{});
  delete ptr;
}

TEST(Clear, ConstPointerToCustomNonMoveConstructible) {
  auto* ptr = new NonMoveConstructible<std::string>("Test It!");
  clear(ptr);
  EXPECT_EQ(ptr->value, std::string{});
  delete ptr;
}

/* *** *** *** *** Clear - Compound Types *** *** *** *** */
struct Point {
  int x, y;
};

TEST(Clear, Struct) {
  Point p = {10, 20};
  clear(p);
  EXPECT_EQ(p.x, 0);
  EXPECT_EQ(p.y, 0);
}

class Person {
 public:
  std::string name;
  int age;
};

TEST(Clear, Class) {
  Person person{"John", 30};
  clear(person);
  EXPECT_EQ(person.name, "");
  EXPECT_EQ(person.age, 0);
}

struct Employee {
  std::string name;
  int salary;
  Point address;
};

TEST(Clear, NestedCompound) {
  Employee employee{"Alice", 50000, {123, 456}};
  clear(employee);
  EXPECT_EQ(employee.name, "");
  EXPECT_EQ(employee.salary, 0);
  EXPECT_EQ(employee.address.x, 0);  // Verify nested struct is also cleared
  EXPECT_EQ(employee.address.y, 0);
}

TEST(Clear, PointerToStruct) {
  auto* p = new Point{7, 8};
  clear(p);
  EXPECT_EQ(p->x, 0);
  EXPECT_EQ(p->y, 0);
  delete p;
}

TEST(Clear, ArrayOfPointers) {
  int* arr[3] = {new int(10), new int(20), new int(30)};
  for (int i = 0; i < 3; ++i) {
    clear(arr[i]);
    EXPECT_EQ(*arr[i], 0);
    delete arr[i];
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
