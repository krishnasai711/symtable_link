#pragma once

class SymTable
{
private:
    struct Node
    {
        const char *key;
        const void *value;
        Node *next;
        Node(const char *k, const void *v, Node *n) : key(k), value(v), next(n) {}
    };

    Node *root;
    int len;
    int mystrcmp(const char *s1, const char *s2) const;

public:
    SymTable() : root(nullptr), len(0) {}

    ~SymTable()
    {
        Node *current = root;
        while (current)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
        root = nullptr;
        len = 0;
    }

    int SymTable_getLength() const;
    bool SymTable_put(const char *key, const void *value);
    const void *SymTable_replace(const char *key, const void *value);
    bool SymTable_contains(const char *key) const;
    const void *SymTable_get(const char *key) const;
    const void *SymTable_remove(const char *key);
    void SymTable_map(void (*func)(const char *, const void *, void *), void *extra);
};
