package ro.ubb.catalog.core.serializer;

import java.util.List;
import java.util.ArrayList;
import java.util.Optional;

import java.util.stream.Collectors;

public abstract class Serializer<T1, T2, T3> {
    protected abstract List<T3> split( T3 data );
    protected abstract T1 join( List<T1> data );
    protected abstract Optional<T3> read( String filename );
    protected abstract void write( T1 data, String filename );

    public abstract T1 serialize( T2 target );
    public abstract T2 deserialize( T3 source );

    public List<T2> readAll( String filename ) {
        Optional<T3> optData = read( filename );

        if ( !optData.isPresent() ) {
            return new ArrayList<>();
        }

        T3 data = optData.get();
        List<T3> chunks = split( data );
        List<T2> entities = chunks
            .stream()
            .map( e -> deserialize( e ) )
            .collect( Collectors.toList() );
        return entities;
    }

    public void writeAll( List<T2> entities, String filename ) {
        List<T1> chunks = entities
            .stream()
            .map( e -> serialize( e ) )
            .collect( Collectors.toList() );
        T1 data = join( chunks );
        write( data, filename );
    }
}

