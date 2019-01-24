<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 6/17/2019
  Time: 3:47 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Delete contents</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.0/jquery.min.js"></script>
    <script>
        $(document).ready(function() {
            var xhttp;

            xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState === 4 && this.status === 200) {
                    $("#contents").append(this.responseText);
                }
            };
            xhttp.open("GET", "GetContentsServlet", true);
            xhttp.send();

            $("#delete").click(function() {
                var xhttp;

                xhttp = new XMLHttpRequest();
                xhttp.open("GET", "DeleteContentServlet?id=" + $("#contents").val(), true);
                xhttp.send();

                var xhttp2;

                xhttp2 = new XMLHttpRequest();
                xhttp2.onreadystatechange = function() {
                    if (this.readyState === 4 && this.status === 200) {
                        $("#contents")
                            .empty()
                            .append("<option value=\"\"></option>")
                            .append(this.responseText);
                    }
                };
                xhttp2.open("GET", "GetContentsServlet", true);
                xhttp2.send();
            });
        });

    </script>
</head>
<body>

<select id="contents">
    <option value=""></option>
</select>

<button id="delete">Delete content</button>

</body>
</html>
