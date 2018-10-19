package Repository;

import Model.IAutomobile;

public class Repo implements IRepo {
    private IAutomobile[] elems;
    private int pos;
    public Repo(int size){
        this.pos = 0;
        this.elems = new IAutomobile[size];
    }

    @Override
    public void add(IAutomobile a) throws RuntimeException {
        if(pos >= elems.length)
            throw new RuntimeException("No more space!");
        elems[pos++] = a;
    }

    @Override
    public void remove(int id) throws RuntimeException {
        if(id < pos)
            if (pos - id >= 0) System.arraycopy(elems, id + 1, elems, id, pos - id);
        else throw new RuntimeException("Invalid position");
    }


    public IAutomobile[] filter(String colour){
        int nr = 0;
        for(IAutomobile e:elems) {


            if (e.getColour().equals(colour))
                nr++;
        }
        IAutomobile[] result = new IAutomobile[nr];
        nr = 0;
        for(IAutomobile e:elems)
            if(e.getColour().equals(colour))
                result[nr++] = e;

        return result;
    }
}
