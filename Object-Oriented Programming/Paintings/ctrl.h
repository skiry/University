#ifndef CTRL_H
#define CTRL_H
#include "repo.h"
#include "undooperation.h"

class ctrl
{
private:
    repo gallery, storage;
    std::vector< std::shared_ptr< undoOperation > > undo;
public:
    ctrl() {}
    ctrl( const repo& _r, const repo& _r2) : gallery{ _r }, storage{ _r2 } {}
    void addPainting( painting p ) {
        gallery.addPainting(p);
        undo.push_back( std::make_shared<undoAddOperation>( p, gallery ) );
    }
    void movePainting( painting p ) {
            gallery.removePainting(p);
            storage.addPainting(p);
            undo.push_back( std::make_shared<undoMoveOperation>( p, gallery, storage ) );
    }
    std::vector<painting> getG() { return gallery.get(); }
    std::vector<painting> getS() { return storage.get(); }
    void doUndo(){
        if( undo.size() == 0 );
        else{
            undo[undo.size() - 1]->executeUndo();
            undo.pop_back();
        }
    }
};

#endif // CTRL_H
