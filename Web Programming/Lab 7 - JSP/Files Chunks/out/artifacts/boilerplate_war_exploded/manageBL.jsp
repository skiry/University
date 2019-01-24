<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 6/17/2019
  Time: 4:47 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Black List</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.0/jquery.min.js"></script>
    <script>
        $(document).ready(function() {
            $("#blbtn").click(function () {
                var xhttp2;

                xhttp2 = new XMLHttpRequest();
                xhttp2.onreadystatechange = function () {
                    if (this.readyState === 4 && this.status === 200) {
                        $("#myList")
                            .empty()
                            .append("Black listed users")
                            .append("<ul>")
                            .append(this.responseText)
                            .append("</ul");
                    }
                };
                xhttp2.open("GET", "GetBLServlet", true);
                xhttp2.send();
            });
        });
    </script>
</head>
<body>
<form action="AddBLServlet" method="post">
    Name:<input type="text" name="username"/><br/><br/>
    <input type="submit" value="Add to black list"/>
</form>
<form action="DeleteBLServlet" method="post">
    Name:<input type="text" name="username"/><br/><br/>
    <input type="submit" value="Delete from black list"/>
</form>

<a href="index.jsp">Home</a>
<button id="blbtn">View black list</button>

<div id="myList"></div>

</body>
</html>
