package ro.ubb.catalog.core.serializer.csv;


import ro.ubb.catalog.core.model.Client;

public class ClientSerializer extends CsvSerializer<Integer, Client> {
    public String serialize( Client client ) {
        return "" +
            client.getId() + "," +
            client.getFirstName() + "," +
            client.getLastName() + "," +
            client.getMoney();
    }

    public Client deserialize( String data ) {
        System.err.println("trying to deserialize: " + data);
        String[] fields = data.split( "," );

        if ( fields.length != 4 ) {
            throw new RuntimeException( "Bad client information given: " + data + "." );
        }

        Integer id       = Integer.parseInt(fields[0].split(":")[1]);
        String firstName = fields[1].split(":")[1];
        String lastName  = fields[2].split(":")[1];
        Integer money    = Integer.parseInt( fields[3].split(":")[1] );
        Client client = new Client( firstName, lastName, money );
        client.setId(id);

        return client;
    }
}
