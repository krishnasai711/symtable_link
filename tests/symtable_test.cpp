#include <gtest/gtest.h>
#include "SymTable.h"

void sumValues(const char *pcKey, const void *pvValue, void *pvExtra)
{
    (*(int *)pvExtra) += (intptr_t)pvValue;
}

TEST(SymTableTest, Creation)
{
    SymTable table;
    ASSERT_EQ(table.SymTable_getLength(), 0);
}

TEST(SymTableTest, EmptyTableOperations)
{
    SymTable table;
    ASSERT_EQ(table.SymTable_get("nonexistent"), nullptr);
    ASSERT_EQ(table.SymTable_remove("nonexistent"), nullptr);
    ASSERT_EQ(table.SymTable_replace("nonexistent", "value"), nullptr);
    ASSERT_EQ(table.SymTable_contains("nonexistent"), false);
}

TEST(SymTableTest, Put)
{
    SymTable table;
    ASSERT_EQ(table.SymTable_put("key1", "value1"), true);
    ASSERT_EQ(table.SymTable_put("key1", "value2"), false);
    ASSERT_EQ(table.SymTable_getLength(), 1);
    ASSERT_STREQ((char *)table.SymTable_get("key1"), "value1");
}

TEST(SymTableTest, PutMultipleKeys)
{
    SymTable table;
    ASSERT_EQ(table.SymTable_put("key1", "value1"), true);
    ASSERT_EQ(table.SymTable_put("key2", "value2"), true);
    ASSERT_EQ(table.SymTable_put("key3", "value3"), true);
    ASSERT_EQ(table.SymTable_getLength(), 3);
    ASSERT_STREQ((char *)table.SymTable_get("key2"), "value2");
}

TEST(SymTableTest, Replace)
{
    SymTable table;
    table.SymTable_put("key1", "value1");
    const void *oldValue = table.SymTable_replace("key1", "newValue1");
    ASSERT_STREQ((char *)oldValue, "value1");
    ASSERT_STREQ((char *)table.SymTable_get("key1"), "newValue1");
}

TEST(SymTableTest, Contains)
{
    SymTable table;
    table.SymTable_put("key1", "value1");
    ASSERT_EQ(table.SymTable_contains("key1"), true);
    ASSERT_EQ(table.SymTable_contains("key2"), false);
}

TEST(SymTableTest, Get)
{
    SymTable table;
    table.SymTable_put("key1", "value1");
    ASSERT_STREQ((char *)table.SymTable_get("key1"), "value1");
    ASSERT_EQ(table.SymTable_get("key2"), nullptr);
}

TEST(SymTableTest, Remove)
{
    SymTable table;
    table.SymTable_put("key1", "value1");
    const void *removedValue = table.SymTable_remove("key1");
    ASSERT_STREQ((char *)removedValue, "value1");
    ASSERT_EQ(table.SymTable_contains("key1"), false);
    ASSERT_EQ(table.SymTable_getLength(), 0);
}

TEST(SymTableTest, RemoveNonExistent)
{
    SymTable table;
    ASSERT_EQ(table.SymTable_remove("key1"), nullptr);
}

TEST(SymTableTest, NullKeyHandling)
{
    SymTable table;
    ASSERT_EQ(table.SymTable_put(nullptr, "value"), false);
    ASSERT_EQ(table.SymTable_contains(nullptr), false);
    ASSERT_EQ(table.SymTable_get(nullptr), nullptr);
    ASSERT_EQ(table.SymTable_remove(nullptr), nullptr);
}

TEST(SymTableTest, NullValueHandling)
{
    SymTable table;
    ASSERT_EQ(table.SymTable_put("key1", nullptr), true);
    ASSERT_EQ(table.SymTable_contains("key1"), true);
    ASSERT_EQ(table.SymTable_get("key1"), nullptr);
    const void *oldValue = table.SymTable_replace("key1", "newValue");
    ASSERT_EQ(oldValue, nullptr);
}

TEST(SymTableTest, Map)
{
    SymTable table;
    table.SymTable_put("key1", (void *)10);
    table.SymTable_put("key2", (void *)20);
    table.SymTable_put("key3", (void *)30);

    int sum = 0;
    table.SymTable_map(sumValues, &sum);

    ASSERT_EQ(sum, 60);
}

TEST(SymTableTest, MapEmptyTable)
{
    SymTable table;
    int count = 0;
    table.SymTable_map(sumValues, &count);
    ASSERT_EQ(count, 0);
}

TEST(SymTableTest, MultipleOperations)
{
    SymTable table;
    ASSERT_EQ(table.SymTable_put("A", "1"), true);
    ASSERT_EQ(table.SymTable_put("B", "2"), true);
    ASSERT_EQ(table.SymTable_put("C", "3"), true);
    ASSERT_EQ(table.SymTable_getLength(), 3);

    ASSERT_EQ(table.SymTable_contains("A"), true);
    ASSERT_STREQ((char *)table.SymTable_get("A"), "1");

    ASSERT_EQ(table.SymTable_remove("B"), (void *)"2");
    ASSERT_EQ(table.SymTable_contains("B"), false);
    ASSERT_EQ(table.SymTable_getLength(), 2);

    ASSERT_EQ(table.SymTable_replace("C", "NewC"), (void *)"3");
    ASSERT_STREQ((char *)table.SymTable_get("C"), "NewC");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
