#ifndef UNDOOPERATION_H
#define UNDOOPERATION_H
#include "repo.h"

class undoOperation
{
public:
    undoOperation() {}
    ~undoOperation() {}
    virtual void executeUndo() = 0;
};


class undoAddOperation : public undoOperation
{
private:
    painting p;
    repo& gal;
public:
    undoAddOperation( painting _p, repo& _gal ) : p{ _p }, gal{ _gal } {}
    void executeUndo() override{
        gal.removePainting(p);
    }
};


class undoMoveOperation : public undoOperation
{
private:
    painting p;
    repo &gal, &sp;
public:
    undoMoveOperation( painting _p, repo& _gal, repo& _sp ) : p{ _p }, gal{ _gal }, sp{ _sp } {}
    void executeUndo() override{
        sp.removePainting(p);
        gal.addPainting(p);
    }
};

#endif // UNDOOPERATION_H
