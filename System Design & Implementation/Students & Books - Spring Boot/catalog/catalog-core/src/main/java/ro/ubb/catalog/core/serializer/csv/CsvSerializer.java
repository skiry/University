package ro.ubb.catalog.core.serializer.csv;

import ro.ubb.catalog.core.model.BaseEntity;
import ro.ubb.catalog.core.serializer.Serializer;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

public abstract class CsvSerializer<ID, T extends BaseEntity<ID>> extends Serializer<String, T, String> {
    protected String join( List<String> chunks ) {
        return chunks
            .stream()
            .collect( Collectors.joining( "\n" ) );
    }

    protected List<String> split( String data ) {
        return Arrays.asList( data.split( "\n" ) );
    }

    protected void write( String data, String filename ) {
        Path path = Paths.get( filename );

        try ( BufferedWriter writer = Files.newBufferedWriter( path, StandardOpenOption.WRITE, StandardOpenOption.CREATE ) ) {
            writer.write( data );
        }
        catch ( IOException e ) {
            throw new RuntimeException( "Could not save changes to the file: " + e.getMessage() );
        }
    }

    protected Optional<String> read( String filename ) {
        Path path = Paths.get( filename );

        if ( !Files.exists( path ) ) {
            return Optional.empty();
        }

        try {
            return Optional.of( Files.readAllLines( path ).stream().collect( Collectors.joining( "\n" ) ) );
        }
        catch ( IOException e ) {
            throw new RuntimeException( "Error when reading CSV file: " + e.getMessage() );
        }
    }
}
