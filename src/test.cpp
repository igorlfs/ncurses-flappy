#include "logic.hpp"
#include <curses.h>
#include <gtest/gtest.h>

Logic l;

TEST(Logic, moveUpBasic) {
    const matrix M = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 1}};
    l.setPositions(M);

    l.move(KEY_UP);

    const matrix EXPECTED = {
        {1, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveDownBasic) {
    const matrix M = {{1, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_DOWN);

    const matrix EXPECTED = {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 1}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveRightBasic) {
    const matrix M = {{1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_RIGHT);

    const matrix EXPECTED = {
        {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveLeftBasic) {
    const matrix M = {{0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_LEFT);

    const matrix EXPECTED = {
        {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveUpMerge) {
    const matrix M = {{1, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_UP);

    const matrix EXPECTED = {
        {2, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveDownMerge) {
    const matrix M = {{0, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_DOWN);

    const matrix EXPECTED = {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {2, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveUpEdge) {
    const matrix M = {{0, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_UP);

    const matrix EXPECTED = {
        {2, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveDownEdge) {
    const matrix M = {{1, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_DOWN);

    const matrix EXPECTED = {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {2, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveRightMerge) {
    const matrix M = {{0, 1, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_RIGHT);

    const matrix EXPECTED = {
        {0, 0, 0, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveLeftMerge) {
    const matrix M = {{1, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_LEFT);

    const matrix EXPECTED = {
        {2, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveRightEdge) {
    const matrix M = {{1, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_RIGHT);

    const matrix EXPECTED = {
        {0, 0, 0, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(Logic, moveLeftEdge) {
    const matrix M = {{0, 1, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    l.setPositions(M);

    l.move(KEY_LEFT);

    const matrix EXPECTED = {
        {2, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    const matrix ACTUAL = l.getPositions();

    EXPECT_EQ(ACTUAL, EXPECTED);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
