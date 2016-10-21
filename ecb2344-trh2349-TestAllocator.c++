
// -------------------------------------
// projects/allocator/TestAllocator1.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------------

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

// --------------
// TestAllocator1
// --------------

template <typename A>
struct TestAllocator1 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A             allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::size_type  size_type;
    typedef typename A::pointer    pointer;};

typedef testing::Types<
            std::allocator<int>,
            std::allocator<double>,
            my_allocator<int,    100>,
            my_allocator<double, 100>>
        my_types_1;

TYPED_TEST_CASE(TestAllocator1, my_types_1);

TYPED_TEST(TestAllocator1, test_1) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 1;
    const value_type     v = 2;
    const pointer        p = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator1, test_10) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type  x;
    const size_type       s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

// --------------
// TestAllocator2
// --------------

TEST(TestAllocator2, const_index) {
    const my_allocator<int, 100> x;
    ASSERT_EQ(x[0], 92);}

TEST(TestAllocator2, index) {
    my_allocator<int, 100> x;
    ASSERT_EQ(x[96], 92);}

// -----------------------------
// Edward and Tyler's Test Cases
// -----------------------------

TEST(TestAllocator7, constructor_1){
    try{
        my_allocator<int, 2> x;
    }catch(bad_alloc e){
        ASSERT_TRUE(true);}}

TEST(TestAllocator8, constructor_2){
    my_allocator<int, 50> x;
    ASSERT_EQ(x[0], 42);}

TEST(TestAllocator4, valid_1){
    my_allocator<int, 100> x;
    x[0] = -92;
    ASSERT_FALSE(x.valid());}

TEST(TestAllocator5, valid_2){
    my_allocator<int, 100> x;
    x[0] = -30;
    x[34] = -30;
    x[38] = 500;
    ASSERT_FALSE(x.valid());}

TEST(TestAllocator6, valid_3){
    my_allocator<int, 100> x;
    x[0] = 50;
    x[96] = 50;
    ASSERT_FALSE(x.valid());}

TEST(TestAllocator9, allocate_1){
    my_allocator<int, 100> x;
    int* p = x.allocate(3);
    x.construct(p, 4);
    ASSERT_TRUE(x[0] == -12 && x[16] == -12 && x[20] == 72 && x[96] == 72);}

TEST(TestAllocator10, allocate_2){
    try{
        my_allocator<int, 20> x;
        int* p = x.allocate(15);
        x.construct(p, 5);
    }catch(bad_alloc e){
        ASSERT_TRUE(true);}}

TEST(TestAllocator11, allocate_3){
    my_allocator<int, 100> x;
    int* p = x.allocate(0);
    x.construct(p, 4);
    ASSERT_TRUE(x.valid());}

TEST(TestAllocator12, deallocate_1){
    my_allocator<int, 100> x;
    int* p = x.allocate(3);
    x.deallocate(p, 3);
    ASSERT_TRUE(x[0] == 92 && x[96] == 92);
}

TEST(TestAllocator12, deallocate_2){
    try{
        my_allocator<int, 100> x;
        int* p = x.allocate(3);
        x.construct(p, 1);
        x.deallocate(0, 3);
    }catch(invalid_argument e){
        ASSERT_TRUE(true);
    }
}

TEST(TestAllocator13, deallocate_3){
    my_allocator<int, 100> x;
    int* p1 = x.allocate(3);
    int* p2 = x.allocate(3);
    int* p3 = x.allocate(3);
    x.deallocate(p2, 3);
    x.deallocate(p3, 3);
    x.deallocate(p1, 3);
    ASSERT_TRUE(x[0] == 92 && x[96] == 92);
}

// --------------
// TestAllocator3
// --------------

template <typename A>
struct TestAllocator3 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A             allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::size_type  size_type;
    typedef typename A::pointer    pointer;};

typedef testing::Types<
            my_allocator<int,    100>,
            my_allocator<double, 100>>
        my_types_2;

TYPED_TEST_CASE(TestAllocator3, my_types_2);

TYPED_TEST(TestAllocator3, test_1) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 1;
    const value_type     v = 2;
    const pointer        p = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator3, test_10) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 10;
    const value_type     v = 2;
    const pointer        b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}
