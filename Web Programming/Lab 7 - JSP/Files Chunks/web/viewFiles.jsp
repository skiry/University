<%@ page import="database.DBHelper" %>
<%@ page import="java.util.HashMap" %><%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 6/17/2019
  Time: 6:02 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>View files</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.0/jquery.min.js"></script>
    <script>
        $(document).ready(function() {
            $("#selbtn").click(function () {
                var xhttp2;

                xhttp2 = new XMLHttpRequest();
                xhttp2.onreadystatechange = function () {
                    if (this.readyState === 4 && this.status === 200) {
                        $("#chunks")
                            .empty()
                            .append("Chunks")
                            .append(this.responseText);
                    }
                };
                xhttp2.open("GET", "GetChunksServlet?q=" + $("#filelist").val(), true);
                xhttp2.send();
            });
        });

        function asschk() {
            var selects = document.getElementsByTagName("select").length - 1;

            var myString = "t=" + selects;
            for(var i = 0; i < selects; ++i) {
                myString += "&s" + i + "=" + document.getElementsByTagName("select").item(i + 1).value;
            }
            var xhttp2;

            xhttp2 = new XMLHttpRequest();
            xhttp2.onreadystatechange = function () {
                if (this.readyState === 4 && this.status === 200) {
                    $("#finalList")
                        .empty()
                        .append("Peers that will download chunks")
                        .append(this.responseText);
                }
            };
            xhttp2.open("POST", "GetPeersServlet", true);
            xhttp2.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            xhttp2.send(myString);
        }
    </script>
</head>
<body>
<a href=index.jsp>Home</a>

<select id="filelist">
    <option value=""></option>
    <%
        DBHelper.connect();
        HashMap<String, Integer> files = DBHelper.getFiles(request.getParameterValues("file[]"));
        for(String file : files.keySet()) {
            System.err.println(file);
    %>
    <option value = <%= files.get(file) %> ><%  out.print  (file); %></option>
    <% } %>
</select>

<button id="selbtn">View chunks</button>
<div id="chunks"></div>
<div id="finalList"></div>

</body>
</html>
