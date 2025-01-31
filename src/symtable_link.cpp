#include "SymTable.h"

int SymTable::mystrcmp(const char *s1, const char *s2) const
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int SymTable::SymTable_getLength() const
{
    return len;
}

bool SymTable::SymTable_put(const char *key, const void *value)
{
    if (!key)
        return false;

    Node *current = root;
    while (current)
    {
        if (mystrcmp(current->key, key) == 0)
            return false;
        current = current->next;
    }
    root = new Node(key, value, root);
    len++;
    return true;
}

const void *SymTable::SymTable_replace(const char *key, const void *value)
{
    if (!key)
        return nullptr;

    Node *current = root;
    while (current)
    {
        if (mystrcmp(current->key, key) == 0)
        {
            const void *oldValue = current->value;
            current->value = value;
            return oldValue;
        }
        current = current->next;
    }
    return nullptr;
}

bool SymTable::SymTable_contains(const char *key) const
{
    if (!key)
        return false;

    Node *current = root;
    while (current)
    {
        if (mystrcmp(current->key, key) == 0)
            return true;
        current = current->next;
    }
    return false;
}

const void *SymTable::SymTable_get(const char *key) const
{
    if (!key)
        return nullptr;

    Node *current = root;
    while (current)
    {
        if (mystrcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return nullptr;
}

const void *SymTable::SymTable_remove(const char *key)
{
    if (!key)
        return nullptr;

    Node *current = root;
    Node *prev = nullptr;

    while (current)
    {
        if (mystrcmp(current->key, key) == 0)
        {
            const void *oldValue = current->value;

            if (prev)
                prev->next = current->next;
            else
                root = current->next;
            delete current;
            len--;
            return oldValue;
        }
        prev = current;
        current = current->next;
    }
    return nullptr;
}

void SymTable::SymTable_map(void (*func)(const char *, const void *, void *), void *extra)
{
    if (!func)
        return;

    Node *current = root;
    while (current)
    {
        func(current->key, current->value, extra);
        current = current->next;
    }
}
