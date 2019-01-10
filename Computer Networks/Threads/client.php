<?php

$HOST = '127.0.0.1';
$PORT = 8080;
$BUCKET_SIZE = 1024;

$socket_client=socket_create(AF_INET,SOCK_STREAM,0);
$connection =  socket_connect($socket_client,$HOST,$PORT);



if ($connection === false) {
    echo "socket_connect() failed.\nReason: ($connectiont) " . socket_strerror(socket_last_error($socket_client)) . "\n";
} else {
    echo "OK.\n";
}

$command = readline("Command: ");
socket_write($socket_client, $command, strlen($command));

$out = '';

echo "Reading response:\n\n";
while ($out = socket_read($socket_client, $BUCKET_SIZE)) {
    echo $out;
}

echo "Closing socket...";
socket_close($socket_client);
echo "OK.\n\n";

exit()
?>

