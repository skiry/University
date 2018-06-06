#ifndef UNDOOPERATION_H
#define UNDOOPERATION_H

#include "repository.h"
#include "fileplaylist.h"

class undoOperation
{
public:
    undoOperation() {}
    ~undoOperation() {}
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};


class undoAddRepo : public undoOperation
{
private:
    Tutorial t;
    Repository& r;
public:
    undoAddRepo( Tutorial _t, Repository& _r ) : t{ _t }, r{ _r } {}

    void executeUndo() override
    {
        r.rmTut(t.getTitle());
    }

    void executeRedo() override
    {
        r.addTut(t);
    }
};


class undoDelRepo : public undoOperation
{
private:
    Tutorial t;
    Repository& r;
public:
    undoDelRepo( Tutorial _t, Repository& _r ) : t{ _t }, r{ _r } {}

    void executeUndo() override
    {
        r.addTut(t);
    }

    void executeRedo() override
    {
        r.rmTut(t.getTitle());
    }
};

class undoUpdRepo : public undoOperation
{
private:
    Tutorial t, t2;
    std::string lastTitle;
    Repository& r;
public:
    undoUpdRepo( Tutorial _t, Repository& _r, std::string tit, Tutorial _t2) : t{ _t }, r{ _r }, lastTitle{ tit }, t2{ _t2 } {}

    void executeUndo() override
    {
        r.updTut(lastTitle, t);
    }

    void executeRedo() override
    {
        r.updTut(t.getTitle(), t2);
    }
};

class undoAddWL : public undoOperation
{
private:
    Tutorial t;
    Repository& r;
public:
    undoAddWL( Tutorial _t, Repository& _r) : t{ _t }, r{ _r } {}

    void executeUndo() override
    {
        r.rmFromPL(t.getTitle());
    }

    void executeRedo() override
    {
        r.addToPL(t);
    }
};

class undoDelWL: public undoOperation
{
private:
    Tutorial t;
    Repository& r;
public:
    undoDelWL( Tutorial _t, Repository& _r ) : t{ _t }, r{ _r } {}

    void executeUndo() override
    {
        r.addToPL(t);
    }

    void executeRedo() override
    {
        r.rmFromPL(t.getTitle());
    }
};
#endif // UNDOOPERATION_H
