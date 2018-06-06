#include "tutorialvalidator.h"
#include "controller.h"
#include "undooperation.h"

int Controller::add(const Tutorial& tut, int cond)
{
    if ( this -> ctrl.find(tut.getTitle()) ) {
		return 1;
	}

	try {
		this -> ctrl.addTut(tut);
        this -> ctrl.writeRepo();

        if ( !cond ) {
            this -> undo.push_back( std::make_shared < undoAddRepo > (tut, ctrl));
            this -> undoCnt++;
        }

        //this -> sqlR -> addTut(tut);
        //this -> sqlR -> saveToFile();

	} catch (...) {
		throw;
	}

	this -> length++;
	return 0;
}

int Controller::rm(std::string title, int cond)
{
	if ( this -> ctrl.find(title) ) {
		this -> length--;

        if ( !cond ) {
            this -> undo.push_back( std::make_shared < undoDelRepo > (ctrl.getTut(title), ctrl));
            this -> undoCnt++;
        }

		this -> ctrl.rmTut(title);
        this -> ctrl.writeRepo();
		//this -> sqlR -> rmTut(title);
		//this -> sqlR -> saveToFile();
		return 1;
	}

	return 0;
}

int Controller::rmW(std::string title, int cond)
{
	if ( this -> ctrl.findW(title) ) {
        if ( !cond ) {
            this -> undo.push_back( std::make_shared < undoDelWL > (ctrl.getTut(title), ctrl));
            this -> undoCnt++;
        }

		this -> ctrl.rmFromPL(title);
        this -> playList -> rmFromPL(title);
		//this -> sqlR -> rmFromPL(title);
		return 1;
	}

	return 0;
}

int Controller::upd(std::string title, const Tutorial& tut, int cond)
{
	if ( this -> ctrl.find(title) && this -> ctrl.find(tut.getTitle()) == 0 ) {
        try {
            if ( !cond ) {
                this -> undo.push_back( std::make_shared < undoUpdRepo > (ctrl.getTut(title), ctrl, tut.getTitle(), tut));
                this -> undoCnt++;
            }

            this -> ctrl.updTut(title, tut);
            this -> ctrl.writeRepo();
            //this -> sqlR -> updTut(title, tut);
			//this -> sqlR -> saveToFile();

		} catch (...) {
			throw;
		}

		return 1;
	}

	return 0;
}



bool Controller::addToPL(const Tutorial& tut, int cond)
{
	bool doo = ctrl.addToPL(tut);

	if ( doo ) {
        this -> playList -> addToPL(tut);

        if ( !cond ) {
            this -> undo.push_back( std::make_shared < undoAddWL > (tut, ctrl));
            this -> undoCnt++;
        }

		// this -> sqlR -> addToPL(tut);
	}

	return doo;
}

bool Controller::doUndo()
{
    if ( undoCnt == 0 ) {
        return false;
    }

    else {
        this -> undo [ --undoCnt ] -> executeUndo();
        return true;
    }
}

bool Controller::doRedo()
{
    if ( undoCnt == undo.size() ) {
        return false;
    }

    else {
        this -> undo [ undoCnt++ ] -> executeRedo();
        return true;
    }
}
