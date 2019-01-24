<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 6/16/2019
  Time: 11:30 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Add Content</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.0/jquery.min.js"></script>
    <script>
        var clicked = 0;
        $(document).ready(function(){
        $("#addContent").click(function() {
            console.log("cllicked");
            if (!clicked) {
                var butt = "<input type=\"submit\" value='Submit contents'/><br/><br/>";
                $("#contents").append(butt);
                clicked = 1;
            }
            var contentInput = "Title: <input type=\"text\" value=\"\" name=\"title[]\"/>" +
                "Description <input type=\"text\" value=\"\" name=\"description[]\"/>" +
                "URL <input type=\"text\" value=\"\" name=\"url[]\"/><br/>";
            $("#contents").append(contentInput);
        });
        });
    </script>
</head>
<body>
Welcome <% request.getSession().getAttribute("currentUser"); %>!
<br/>
<button id="addContent">Add one more content</button>
<button><a href="deleteContent.jsp">Delete contents</a></button>

<form id="contents" action="AddContentsServlet" method="POST">
</form>

</body>
</html>
